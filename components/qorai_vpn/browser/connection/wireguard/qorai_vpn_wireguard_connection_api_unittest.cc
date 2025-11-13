/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <memory>

#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_connection_manager.h"
#include "qorai/components/qorai_vpn/browser/connection/wireguard/wireguard_connection_api_impl_base.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_data_types.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "services/network/public/cpp/weak_wrapper_shared_url_loader_factory.h"
#include "services/network/test/test_url_loader_factory.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_vpn {

namespace {
class WireguardConnectionAPISim : public WireguardConnectionAPIImplBase {
 public:
  WireguardConnectionAPISim(
      QoraiVPNConnectionManager* manager,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory)
      : WireguardConnectionAPIImplBase(manager, url_loader_factory) {}
  ~WireguardConnectionAPISim() override {}

  void Disconnect() override {}
  void CheckConnection() override {}
  void PlatformConnectImpl(
      const wireguard::WireguardProfileCredentials& credentials) override {}
};
}  // namespace

class QoraiVPNWireguardConnectionAPIUnitTest : public testing::Test {
 public:
  QoraiVPNWireguardConnectionAPIUnitTest()
      : task_environment_(base::test::TaskEnvironment::TimeSource::MOCK_TIME) {}

  void SetUp() override {
    qorai_vpn::RegisterLocalStatePrefs(local_pref_service_.registry());
    shared_url_loader_factory_ =
        base::MakeRefCounted<network::WeakWrapperSharedURLLoaderFactory>(
            &url_loader_factory_);
    connection_manager_ = std::make_unique<QoraiVPNConnectionManager>(
        shared_url_loader_factory_, &local_pref_service_, base::NullCallback());
    connection_manager_->SetConnectionAPIImplForTesting(
        std::make_unique<WireguardConnectionAPISim>(
            connection_manager_.get(), shared_url_loader_factory_));
  }

  WireguardConnectionAPISim* GetConnectionAPI() {
    return static_cast<WireguardConnectionAPISim*>(
        connection_manager_->connection_api_impl_.get());
  }
  PrefService* local_state() { return &local_pref_service_; }

 protected:
  TestingPrefServiceSimple local_pref_service_;
  network::TestURLLoaderFactory url_loader_factory_;
  scoped_refptr<network::SharedURLLoaderFactory> shared_url_loader_factory_;
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<QoraiVPNConnectionManager> connection_manager_;
};

TEST_F(QoraiVPNWireguardConnectionAPIUnitTest, SetSelectedRegion) {
  local_state()->SetString(prefs::kQoraiVPNWireguardProfileCredentials,
                           "region-a");
  GetConnectionAPI()->hostname_ = std::make_unique<Hostname>();
  GetConnectionAPI()->hostname_->hostname = "test";
  GetConnectionAPI()->SetSelectedRegion("region-b");
  EXPECT_TRUE(local_state()
                  ->GetString(prefs::kQoraiVPNWireguardProfileCredentials)
                  .empty());
  EXPECT_EQ(GetConnectionAPI()->hostname_.get(), nullptr);
}

}  // namespace qorai_vpn
