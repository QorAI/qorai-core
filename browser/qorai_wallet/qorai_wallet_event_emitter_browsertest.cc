/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <memory>
#include <optional>

#include "base/test/scoped_feature_list.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/qorai_wallet/browser/test_utils.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/network_session_configurator/common/network_switches.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "content/public/test/content_mock_cert_verifier.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "net/dns/mock_host_resolver.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"
#include "url/gurl.h"
#include "url/origin.h"

namespace {

std::string CheckForEventScript(const std::string& event_var) {
  return absl::StrFormat(R"(
      new Promise(resolve => {
        const timer = setInterval(function () {
          if (%s) {
            clearInterval(timer);
            resolve(true);
          }
        }, 100);
      });
    )",
                         event_var);
}

}  // namespace

namespace qorai_wallet {

class QoraiWalletEventEmitterTest : public InProcessBrowserTest {
 public:
  QoraiWalletEventEmitterTest() {
    feature_list_.InitAndEnableFeature(
        qorai_wallet::features::kNativeQoraiWalletFeature);
  }

  void SetUpInProcessBrowserTestFixture() override {
    InProcessBrowserTest::SetUpInProcessBrowserTestFixture();
    mock_cert_verifier_.SetUpInProcessBrowserTestFixture();
  }

  void TearDownInProcessBrowserTestFixture() override {
    InProcessBrowserTest::TearDownInProcessBrowserTestFixture();
    mock_cert_verifier_.TearDownInProcessBrowserTestFixture();
  }

  void SetUpOnMainThread() override {
    qorai_wallet::SetDefaultEthereumWallet(
        browser()->profile()->GetPrefs(),
        qorai_wallet::mojom::DefaultWallet::QoraiWallet);
    InProcessBrowserTest::SetUpOnMainThread();
    mock_cert_verifier_.mock_cert_verifier()->set_default_result(net::OK);
    host_resolver()->AddRule("*", "127.0.0.1");

    https_server_ = std::make_unique<net::EmbeddedTestServer>(
        net::test_server::EmbeddedTestServer::TYPE_HTTPS);
    https_server_->SetSSLConfig(net::EmbeddedTestServer::CERT_OK);

    https_server_->ServeFilesFromDirectory(QoraiWalletTestDataFolder());

    ASSERT_TRUE(https_server_->Start());
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    InProcessBrowserTest::SetUpCommandLine(command_line);
    mock_cert_verifier_.SetUpCommandLine(command_line);
  }

  net::EmbeddedTestServer* https_server() { return https_server_.get(); }

  mojo::Remote<qorai_wallet::mojom::JsonRpcService> GetJsonRpcService() {
    if (!json_rpc_service_) {
      mojo::PendingRemote<qorai_wallet::mojom::JsonRpcService> remote;
      qorai_wallet_service()->json_rpc_service()->Bind(
          remote.InitWithNewPipeAndPassReceiver());
      json_rpc_service_.Bind(std::move(remote));
    }
    return std::move(json_rpc_service_);
  }

  HostContentSettingsMap* host_content_settings_map() {
    return HostContentSettingsMapFactory::GetForProfile(browser()->profile());
  }

  content::WebContents* web_contents() {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

  QoraiWalletService* qorai_wallet_service() {
    return QoraiWalletServiceFactory::GetServiceForContext(
        browser()->profile());
  }

  KeyringService* keyring_service() {
    return qorai_wallet_service()->keyring_service();
  }

  url::Origin GetLastCommitedOrigin() {
    return url::Origin::Create(web_contents()->GetLastCommittedURL());
  }

  AccountUtils GetAccountUtils() { return AccountUtils(keyring_service()); }

  void RestoreWallet() {
    ASSERT_TRUE(keyring_service()->RestoreWalletSync(
        kMnemonicDripCaution, kTestWalletPassword, false));
  }

  void SetSelectedAccount(const mojom::AccountIdPtr& account_id) {
    ASSERT_TRUE(keyring_service()->SetSelectedAccountSync(account_id.Clone()));
  }

 private:
  content::ContentMockCertVerifier mock_cert_verifier_;
  mojo::Remote<qorai_wallet::mojom::JsonRpcService> json_rpc_service_;
  std::unique_ptr<net::EmbeddedTestServer> https_server_;
  base::test::ScopedFeatureList feature_list_;
};

IN_PROC_BROWSER_TEST_F(QoraiWalletEventEmitterTest, CheckForAConnectEvent) {
  GURL url =
      https_server()->GetURL("a.com", "/qorai_wallet_event_emitter.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();

  auto result_first =
      EvalJs(contents, CheckForEventScript("received_connect_event"));
  EXPECT_EQ(base::Value(true), result_first);
}

IN_PROC_BROWSER_TEST_F(QoraiWalletEventEmitterTest,
                       CheckForAChainChangedEvent) {
  GURL url =
      https_server()->GetURL("a.com", "/qorai_wallet_event_emitter.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  auto service = GetJsonRpcService();
  service->SetNetwork(qorai_wallet::mojom::kSepoliaChainId,
                      qorai_wallet::mojom::CoinType::ETH, std::nullopt,
                      base::DoNothing());

  auto result_first =
      EvalJs(contents, CheckForEventScript("received_chain_changed_event"));
  EXPECT_EQ(base::Value(true), result_first);
}

IN_PROC_BROWSER_TEST_F(QoraiWalletEventEmitterTest,
                       CheckForAnAccountChangedEvent) {
  RestoreWallet();
  auto eth_account = GetAccountUtils().EnsureEthAccount(0);
  GURL url =
      https_server()->GetURL("a.com", "/qorai_wallet_event_emitter.html");
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();

  auto sub_request_origin = qorai_wallet::GetSubRequestOrigin(
      permissions::RequestType::kQoraiEthereum, GetLastCommitedOrigin(),
      eth_account->address);
  ASSERT_TRUE(sub_request_origin);
  host_content_settings_map()->SetContentSettingDefaultScope(
      sub_request_origin->GetURL(), GetLastCommitedOrigin().GetURL(),
      ContentSettingsType::QORAI_ETHEREUM,
      ContentSetting::CONTENT_SETTING_ALLOW);
  SetSelectedAccount(eth_account->account_id);

  auto result_first =
      EvalJs(contents, CheckForEventScript("received_account_changed_event"));
  EXPECT_EQ(base::Value(true), result_first);
}

}  // namespace qorai_wallet
