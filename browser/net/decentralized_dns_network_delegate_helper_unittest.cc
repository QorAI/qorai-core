/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/decentralized_dns_network_delegate_helper.h"

#include <memory>

#include "base/functional/callback_helpers.h"
#include "base/run_loop.h"
#include "base/test/scoped_feature_list.h"
#include "base/values.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/net/url_context.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_prefs.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service_test_utils.h"
#include "qorai/components/qorai_wallet/browser/network_manager.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/eth_abi_utils.h"
#include "qorai/components/qorai_wallet/common/hex_utils.h"
#include "qorai/components/qorai_wallet/common/pref_names.h"
#include "qorai/components/decentralized_dns/core/constants.h"
#include "qorai/components/decentralized_dns/core/pref_names.h"
#include "qorai/components/decentralized_dns/core/utils.h"
#include "build/build_config.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "components/prefs/testing_pref_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/test/browser_task_environment.h"
#include "net/base/net_errors.h"
#include "services/data_decoder/public/cpp/test_support/in_process_data_decoder.h"
#include "services/network/public/cpp/weak_wrapper_shared_url_loader_factory.h"
#include "services/network/test/test_url_loader_factory.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using qorai::ResponseCallback;

namespace decentralized_dns {

class DecentralizedDnsNetworkDelegateHelperTest : public testing::Test {
 public:
  DecentralizedDnsNetworkDelegateHelperTest() = default;

  ~DecentralizedDnsNetworkDelegateHelperTest() override = default;

  void SetUp() override {
    profile_ = std::make_unique<TestingProfile>();

    shared_url_loader_factory_ =
        base::MakeRefCounted<network::WeakWrapperSharedURLLoaderFactory>(
            &test_url_loader_factory_);
    json_rpc_service_ =
        qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(
            browser_context())
            ->json_rpc_service();
    json_rpc_service_->SetAPIRequestHelperForTesting(
        shared_url_loader_factory_);
  }

  void TearDown() override {
    json_rpc_service_ = nullptr;
    profile_.reset();
  }

  content::BrowserContext* browser_context() { return profile_.get(); }
  TestingProfile* profile() { return profile_.get(); }
  PrefService* local_state() {
    return TestingBrowserProcess::GetGlobal()->GetTestingLocalState();
  }
  network::TestURLLoaderFactory& test_url_loader_factory() {
    return test_url_loader_factory_;
  }

  content::BrowserTaskEnvironment task_environment_;

 private:
  std::unique_ptr<TestingProfile> profile_;
  network::TestURLLoaderFactory test_url_loader_factory_;
  scoped_refptr<network::SharedURLLoaderFactory> shared_url_loader_factory_;
  raw_ptr<qorai_wallet::JsonRpcService> json_rpc_service_ = nullptr;
  data_decoder::test::InProcessDataDecoder in_process_data_decoder_;
};

TEST_F(DecentralizedDnsNetworkDelegateHelperTest,
       DecentralizedDnsPreRedirectWork) {
  GURL url("http://qorai.crypto");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);
  qorai_request_info->browser_context = profile();

  // No redirect if resolve method is not set to Ethereum.
  EXPECT_FALSE(IsUnstoppableDomainsResolveMethodEnabled(local_state()));
  int rc = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
      base::DoNothing(), qorai_request_info);
  EXPECT_EQ(rc, net::OK);
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  local_state()->SetInteger(kUnstoppableDomainsResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));
  EXPECT_TRUE(IsUnstoppableDomainsResolveMethodEnabled(local_state()));

  // No redirect for OTR context.
  qorai_request_info->browser_context =
      profile()->GetPrimaryOTRProfile(/*create_if_needed=*/true);
  rc = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(base::DoNothing(),
                                                          qorai_request_info);
  EXPECT_EQ(rc, net::OK);
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());
  qorai_request_info->browser_context = profile();

  // TLD is not .crypto
  qorai_request_info->request_url = GURL("http://test.com");
  rc = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(base::DoNothing(),
                                                          qorai_request_info);
  EXPECT_EQ(rc, net::OK);
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());
  qorai_request_info->request_url = url;

  rc = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(base::DoNothing(),
                                                          qorai_request_info);
  EXPECT_EQ(rc, net::ERR_IO_PENDING);

  // No redirect if ENS resolve method is not set to Ethereum.
  EXPECT_FALSE(IsENSResolveMethodEnabled(local_state()));
  qorai_request_info->request_url = GURL("http://qorai.eth");
  rc = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(base::DoNothing(),
                                                          qorai_request_info);
  EXPECT_EQ(rc, net::OK);
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  local_state()->SetInteger(kENSResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));
  EXPECT_TRUE(IsENSResolveMethodEnabled(local_state()));
  qorai_request_info->request_url = GURL("http://qorai.eth");
  rc = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(base::DoNothing(),
                                                          qorai_request_info);
  EXPECT_EQ(rc, net::ERR_IO_PENDING);
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());
}

TEST_F(DecentralizedDnsNetworkDelegateHelperTest,
       DecentralizedDnsPreRedirectTLDs) {
  local_state()->SetInteger(kUnstoppableDomainsResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));
  struct TestCase {
    const char* url;
    bool is_valid;
  } test_cases[] = {
      {"https://qorai.888", false},
      {"https://qorai.altimist", true},
      {"https://qorai.anime", true},
      {"https://qorai.ask", true},
      {"https://qorai.austin", true},
      {"https://qorai.bald", true},
      {"https://qorai.basenji", true},
      {"https://qorai.bay", true},
      {"https://qorai.benji", true},
      {"https://qorai.binanceus", true},
      {"https://qorai.bitcoin", true},
      {"https://qorai.bitget", true},
      {"https://qorai.bitscrunch", true},
      {"https://qorai.blockchain", true},
      {"https://qorai.boomer", true},
      {"https://qorai.qorai", true},
      {"https://qorai.calicoin", true},
      {"https://qorai.caw", true},
      {"https://qorai.chomp", true},
      {"https://qorai.clay", true},
      {"https://qorai.coin", false},
      {"https://qorai.crypto", true},
      {"https://qorai.dao", true},
      {"https://qorai.dfz", true},
      {"https://qorai.doga", true},
      {"https://qorai.donut", true},
      {"https://qorai.dream", true},
      {"https://qorai.emir", true},
      {"https://qorai.ethermail", true},
      {"https://qorai.farms", true},
      {"https://qorai.grow", true},
      {"https://qorai.her", true},
      {"https://qorai.kingdom", true},
      {"https://qorai.klever", true},
      {"https://qorai.kresus", true},
      {"https://qorai.kryptic", true},
      {"https://qorai.lfg", true},
      {"https://qorai.ltc", true},
      {"https://qorai.manga", true},
      {"https://qorai.metropolis", true},
      {"https://qorai.miku", true},
      {"https://qorai.ministry", true},
      {"https://qorai.moon", true},
      {"https://qorai.mumu", true},
      {"https://qorai.nft", true},
      {"https://qorai.nibi", true},
      {"https://qorai.npc", true},
      {"https://qorai.onchain", true},
      {"https://qorai.pastor", true},
      {"https://qorai.podcast", true},
      {"https://qorai.pog", true},
      {"https://qorai.polygon", true},
      {"https://qorai.privacy", true},
      {"https://qorai.propykeys", true},
      {"https://qorai.pudgy", true},
      {"https://qorai.quantum", true},
      {"https://qorai.rad", true},
      {"https://qorai.raiin", true},
      {"https://qorai.secret", true},
      {"https://qorai.smobler", true},
      {"https://qorai.south", true},
      {"https://qorai.stepn", true},
      {"https://qorai.tball", true},
      {"https://qorai.tea", true},
      {"https://qorai.tribe", true},
      {"https://qorai.u", true},
      {"https://qorai.ubu", true},
      {"https://qorai.unstoppable", true},
      {"https://qorai.wallet", true},
      {"https://qorai.wifi", true},
      {"https://qorai.witg", true},
      {"https://qorai.wrkx", true},
      {"https://qorai.x", true},
      {"https://qorai.xec", true},
      {"https://qorai.xmr", true},
      {"https://qorai.zil", true},
      {"https://qorai", false},
      {"https://qorai.com", false},
      {"", false},
  };

  for (const auto& test_case : test_cases) {
    auto qorai_request_info =
        std::make_shared<qorai::QoraiRequestInfo>(GURL(test_case.url));
    qorai_request_info->browser_context = profile();
    EXPECT_EQ(test_case.is_valid ? net::ERR_IO_PENDING : net::OK,
              OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
                  base::DoNothing(), qorai_request_info));
  }
}

TEST_F(DecentralizedDnsNetworkDelegateHelperTest,
       UnstoppableDomainsRedirectWork) {
  local_state()->SetInteger(kUnstoppableDomainsResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));

  GURL url("http://qorai.crypto");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);
  qorai_request_info->browser_context = profile();

  auto polygon_spec = qorai_wallet::NetworkManager::GetUnstoppableDomainsRpcUrl(
                          qorai_wallet::mojom::kPolygonMainnetChainId)
                          .spec();
  auto eth_spec = qorai_wallet::NetworkManager::GetUnstoppableDomainsRpcUrl(
                      qorai_wallet::mojom::kMainnetChainId)
                      .spec();
  auto base_spec = qorai_wallet::NetworkManager::GetUnstoppableDomainsRpcUrl(
                       qorai_wallet::mojom::kBaseMainnetChainId)
                       .spec();

  // No redirect for failed requests.
  EXPECT_EQ(net::ERR_IO_PENDING,
            OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
                base::DoNothing(), qorai_request_info));
  test_url_loader_factory().SimulateResponseForPendingRequest(
      polygon_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"", "", "", "", "", "https://qorai.com"}),
      net::HTTP_REQUEST_TIMEOUT);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      eth_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"", "", "", "", "", "https://qorai.com"}),
      net::HTTP_REQUEST_TIMEOUT);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      base_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"", "", "", "", "", "https://qorai.com"}),
      net::HTTP_REQUEST_TIMEOUT);
  task_environment_.RunUntilIdle();
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  // Polygon result.
  EXPECT_EQ(net::ERR_IO_PENDING,
            OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
                base::DoNothing(), qorai_request_info));
  test_url_loader_factory().SimulateResponseForPendingRequest(
      polygon_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"", "", "", "", "", "https://qorai.com"}),
      net::HTTP_OK);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      base_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"", "", "", "", "", "https://qorai.com/base"}),
      net::HTTP_OK);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      eth_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"QmbWqxBEKC3P8tqsKc98xmWNzrzDtRLMiMPL8wBuTGsMnR", "", "", "", "",
           ""}),
      net::HTTP_OK);
  task_environment_.RunUntilIdle();
  EXPECT_EQ(qorai_request_info->new_url_spec, "https://qorai.com/");

  // Base result.
  EXPECT_EQ(net::ERR_IO_PENDING,
            OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
                base::DoNothing(), qorai_request_info));
  test_url_loader_factory().SimulateResponseForPendingRequest(
      polygon_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse({"", "", "", "", "", ""}),
      net::HTTP_OK);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      base_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"", "", "", "", "", "https://qorai.com/base"}),
      net::HTTP_OK);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      eth_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"QmbWqxBEKC3P8tqsKc98xmWNzrzDtRLMiMPL8wBuTGsMnR", "", "", "", "",
           ""}),
      net::HTTP_OK);
  task_environment_.RunUntilIdle();
  EXPECT_EQ(qorai_request_info->new_url_spec, "https://qorai.com/base");

  // Eth result.
  EXPECT_EQ(net::ERR_IO_PENDING,
            OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
                base::DoNothing(), qorai_request_info));
  test_url_loader_factory().SimulateResponseForPendingRequest(
      polygon_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse({"", "", "", "", "", ""}),
      net::HTTP_OK);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      base_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse({"", "", "", "", "", ""}),
      net::HTTP_OK);
  test_url_loader_factory().SimulateResponseForPendingRequest(
      eth_spec,
      qorai_wallet::MakeJsonRpcStringArrayResponse(
          {"QmbWqxBEKC3P8tqsKc98xmWNzrzDtRLMiMPL8wBuTGsMnR", "", "", "", "",
           ""}),
      net::HTTP_OK);
  task_environment_.RunUntilIdle();
  EXPECT_EQ(
      qorai_request_info->new_url_spec,
      "https://ipfs.io/ipfs/QmbWqxBEKC3P8tqsKc98xmWNzrzDtRLMiMPL8wBuTGsMnR");
}

TEST_F(DecentralizedDnsNetworkDelegateHelperTest, EnsRedirectWork) {
  GURL url("http://brantly.eth");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);

  // No redirect for failed requests.
  OnBeforeURLRequest_EnsRedirectWork(
      base::DoNothing(), qorai_request_info, {}, false,
      qorai_wallet::mojom::ProviderError::kInternalError, "todo");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  OnBeforeURLRequest_EnsRedirectWork(
      base::DoNothing(), qorai_request_info, {}, false,
      qorai_wallet::mojom::ProviderError::kSuccess, "");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  // No redirect for invalid content hash.
  std::string content_hash_encoded_string =
      "0x0000000000000000000000000000000000000000000000000000000000000020000000"
      "000000000000000000000000000000000000000000000000000000002655010170122023"
      "e0160eec32d7875c19c5ac7c03bc1f306dc260080d621454bc5f631e7310a70000000000"
      "000000000000000000000000000000000000000000";

  auto content_hash = *qorai_wallet::eth_abi::ExtractBytesFromTuple(
      *qorai_wallet::PrefixedHexStringToBytes(content_hash_encoded_string), 0);
  OnBeforeURLRequest_EnsRedirectWork(
      base::DoNothing(), qorai_request_info, content_hash, false,
      qorai_wallet::mojom::ProviderError::kSuccess, "");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  // Redirect for valid content hash.
  content_hash_encoded_string =
      "0x0000000000000000000000000000000000000000000000000000000000000020000000"
      "0000000000000000000000000000000000000000000000000000000026e3010170122023"
      "e0160eec32d7875c19c5ac7c03bc1f306dc260080d621454bc5f631e7310a70000000000"
      "000000000000000000000000000000000000000000";

  content_hash = *qorai_wallet::eth_abi::ExtractBytesFromTuple(
      *qorai_wallet::PrefixedHexStringToBytes(content_hash_encoded_string), 0);
  OnBeforeURLRequest_EnsRedirectWork(
      base::DoNothing(), qorai_request_info, content_hash, false,
      qorai_wallet::mojom::ProviderError::kSuccess, "");
  EXPECT_EQ(qorai_request_info->new_url_spec,
            "https://ipfs.io/ipfs/"
            "bafybeibd4ala53bs26dvygofvr6ahpa7gbw4eyaibvrbivf4l5rr44yqu4");

  EXPECT_FALSE(qorai_request_info->pending_error.has_value());
}

TEST_F(DecentralizedDnsNetworkDelegateHelperTest,
       EnsRedirect_OffchainLookupRequired) {
  GURL url("http://brantly.eth");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);

  // Offchain lookup required.
  OnBeforeURLRequest_EnsRedirectWork(
      base::DoNothing(), qorai_request_info, {}, true,
      qorai_wallet::mojom::ProviderError::kSuccess, "");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());
  EXPECT_EQ(qorai_request_info->pending_error,
            net::ERR_ENS_OFFCHAIN_LOOKUP_NOT_SELECTED);
}

TEST_F(DecentralizedDnsNetworkDelegateHelperTest, SnsRedirectWork) {
  GURL url("http://test.sol");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);

  // No redirect for failed requests.
  OnBeforeURLRequest_SnsRedirectWork(
      base::DoNothing(), qorai_request_info, {},
      qorai_wallet::mojom::SolanaProviderError::kInternalError, "todo");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  OnBeforeURLRequest_SnsRedirectWork(
      base::DoNothing(), qorai_request_info, {},
      qorai_wallet::mojom::SolanaProviderError::kSuccess, "");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  // No redirect for invalid url.
  OnBeforeURLRequest_SnsRedirectWork(
      base::DoNothing(), qorai_request_info, GURL("invalid"),
      qorai_wallet::mojom::SolanaProviderError::kSuccess, "");
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());

  // Redirect for valid url.
  OnBeforeURLRequest_SnsRedirectWork(
      base::DoNothing(), qorai_request_info, GURL("https://qorai.com"),
      qorai_wallet::mojom::SolanaProviderError::kSuccess, "");
  EXPECT_EQ(qorai_request_info->new_url_spec, GURL("https://qorai.com"));

  EXPECT_FALSE(qorai_request_info->pending_error.has_value());
}

// Test that decentralized DNS is disabled when QoraiWalletDisabled policy is
// true
TEST_F(DecentralizedDnsNetworkDelegateHelperTest,
       DisabledWhenQoraiWalletDisabledByPolicy) {
  // Set up the preferences to enable decentralized DNS methods
  local_state()->SetInteger(kUnstoppableDomainsResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));
  local_state()->SetInteger(kENSResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));
  local_state()->SetInteger(kSnsResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));

  // Disable Qorai Wallet by policy
  auto* prefs = profile()->GetTestingPrefService();
  prefs->SetManagedPref(qorai_wallet::prefs::kDisabledByPolicy,
                        base::Value(true));

  // Create test request for an unstoppable domain
  GURL url("http://test.crypto");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);
  qorai_request_info->browser_context = browser_context();

  // Call the decentralized DNS helper
  int result = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
      base::DoNothing(), qorai_request_info);

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  // On desktop platforms, policy is enforced, so wallet is disabled
  // Should return OK immediately (not pending) because wallet is disabled
  EXPECT_EQ(net::OK, result);
  EXPECT_TRUE(qorai_request_info->new_url_spec.empty());
#else
  // On mobile platforms, policy is not enforced, so wallet is always enabled
  // Should return ERR_IO_PENDING because it will try to resolve the domain
  EXPECT_EQ(net::ERR_IO_PENDING, result);
#endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
}

// Test that decentralized DNS works when QoraiWalletDisabled policy is false
TEST_F(DecentralizedDnsNetworkDelegateHelperTest,
       EnabledWhenQoraiWalletEnabledByPolicy) {
  // Set up the preferences to enable decentralized DNS methods
  local_state()->SetInteger(kUnstoppableDomainsResolveMethod,
                            static_cast<int>(ResolveMethodTypes::ENABLED));

  // Enable Qorai Wallet by policy (this is the default)
  auto* prefs = profile()->GetTestingPrefService();
  prefs->SetManagedPref(qorai_wallet::prefs::kDisabledByPolicy,
                        base::Value(false));

  // Create test request for an unstoppable domain
  GURL url("http://test.crypto");
  auto qorai_request_info = std::make_shared<qorai::QoraiRequestInfo>(url);
  qorai_request_info->browser_context = browser_context();

  // Call the decentralized DNS helper
  int result = OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
      base::DoNothing(), qorai_request_info);

  // Should return ERR_IO_PENDING because it will try to resolve the domain
  EXPECT_EQ(net::ERR_IO_PENDING, result);
}

}  // namespace decentralized_dns
