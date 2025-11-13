/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"

#include "base/memory/raw_ptr.h"
#include "base/path_service.h"
#include "base/test/bind.h"
#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_observer_base.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/constants/qorai_paths.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "net/dns/mock_host_resolver.h"
#include "url/origin.h"

namespace qorai_wallet {

namespace {

void OnGetActiveOrigin(bool* callback_called,
                       mojom::OriginInfoPtr expected_active_origin,
                       mojom::OriginInfoPtr active_origin) {
  EXPECT_EQ(expected_active_origin, active_origin);
  *callback_called = true;
}

}  // namespace

class TestQorAIWalletServiceObserver
    : public qorai_wallet::QorAIWalletServiceObserverBase {
 public:
  TestQorAIWalletServiceObserver() = default;

  void OnActiveOriginChanged(mojom::OriginInfoPtr origin_info) override {
    active_origin_info_ = origin_info->Clone();
  }

  const mojom::OriginInfoPtr& active_origin_info() const {
    return active_origin_info_;
  }

  mojo::PendingRemote<qorai_wallet::mojom::QorAIWalletServiceObserver>
  GetReceiver() {
    return observer_receiver_.BindNewPipeAndPassRemote();
  }

  void Reset() { active_origin_info_ = {}; }

 private:
  mojom::OriginInfoPtr active_origin_info_;
  mojo::Receiver<qorai_wallet::mojom::QorAIWalletServiceObserver>
      observer_receiver_{this};
};

class QorAIWalletServiceTest : public InProcessBrowserTest {
 public:
  QorAIWalletServiceTest()
      : https_server_(net::EmbeddedTestServer::TYPE_HTTPS) {}

  void SetUp() override {
    InProcessBrowserTest::SetUp();
    feature_list_.InitAndEnableFeature(
        qorai_wallet::features::kNativeQorAIWalletFeature);
  }

  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
    base::FilePath test_data_dir;
    base::PathService::Get(qorai::DIR_TEST_DATA, &test_data_dir);
    https_server_.SetSSLConfig(net::EmbeddedTestServer::CERT_TEST_NAMES);
    https_server_.ServeFilesFromDirectory(test_data_dir);
    EXPECT_TRUE(https_server_.Start());
    host_resolver()->AddRule("*", "127.0.0.1");
  }

  void TestIsPrivateWindow(QorAIWalletService* wallet_service,
                           bool expected_result) {
    base::MockCallback<base::OnceCallback<void(bool)>> callback;
    EXPECT_CALL(callback, Run(expected_result)).Times(1);

    wallet_service->IsPrivateWindow(callback.Get());
  }

  QorAIWalletService* wallet_service() {
    return QorAIWalletServiceFactory::GetServiceForContext(
        browser()->profile());
  }

  QorAIWalletService* incognito_wallet_service() {
    return qorai_wallet::QorAIWalletServiceFactory::GetInstance()
        ->GetServiceForContext(
            CreateIncognitoBrowser(browser()->profile())->profile());
  }
  const net::EmbeddedTestServer* https_server() const { return &https_server_; }

 private:
  net::EmbeddedTestServer https_server_;
  base::test::ScopedFeatureList feature_list_;
};

IN_PROC_BROWSER_TEST_F(QorAIWalletServiceTest, ActiveOrigin) {
  GURL url = https_server()->GetURL("a.test", "/simple.html");
  auto expected_origin_info = MakeOriginInfo(url::Origin::Create(url));
  TestQorAIWalletServiceObserver observer;
  wallet_service()->AddObserver(observer.GetReceiver());
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));

  bool callback_called = false;
  wallet_service()->GetActiveOrigin(base::BindOnce(
      &OnGetActiveOrigin, &callback_called, expected_origin_info->Clone()));
  base::RunLoop().RunUntilIdle();
  EXPECT_TRUE(callback_called);
  EXPECT_EQ(observer.active_origin_info(), expected_origin_info);

  url = https_server()->GetURL("b.test", "/simple.html");
  expected_origin_info = MakeOriginInfo(url::Origin::Create(url));
  callback_called = false;
  observer.Reset();
  ASSERT_TRUE(ui_test_utils::NavigateToURL(browser(), url));
  wallet_service()->GetActiveOrigin(base::BindOnce(
      &OnGetActiveOrigin, &callback_called, expected_origin_info->Clone()));
  base::RunLoop().RunUntilIdle();
  EXPECT_TRUE(callback_called);
  EXPECT_EQ(observer.active_origin_info(), expected_origin_info);

  url = https_server()->GetURL("c.test", "/simple.html");
  expected_origin_info = MakeOriginInfo(url::Origin::Create(url));
  observer.Reset();
  ui_test_utils::NavigateToURLWithDisposition(
      browser(), url, WindowOpenDisposition::NEW_FOREGROUND_TAB,
      ui_test_utils::BROWSER_TEST_WAIT_FOR_LOAD_STOP);
  wallet_service()->GetActiveOrigin(base::BindOnce(
      &OnGetActiveOrigin, &callback_called, expected_origin_info->Clone()));
  base::RunLoop().RunUntilIdle();
  EXPECT_TRUE(callback_called);
  EXPECT_EQ(observer.active_origin_info(), expected_origin_info);

  url = https_server()->GetURL("d.test", "/simple.html");
  expected_origin_info = MakeOriginInfo(url::Origin::Create(url));
  observer.Reset();
  ui_test_utils::NavigateToURLWithDisposition(
      browser(), url, WindowOpenDisposition::NEW_WINDOW,
      ui_test_utils::BROWSER_TEST_WAIT_FOR_LOAD_STOP);
  wallet_service()->GetActiveOrigin(base::BindOnce(
      &OnGetActiveOrigin, &callback_called, expected_origin_info->Clone()));
  base::RunLoop().RunUntilIdle();
  EXPECT_TRUE(callback_called);
  EXPECT_EQ(observer.active_origin_info(), expected_origin_info);
}

IN_PROC_BROWSER_TEST_F(QorAIWalletServiceTest, IsPrivateWindow) {
  TestIsPrivateWindow(wallet_service(), false);
  wallet_service()->SetPrivateWindowsEnabled(true);
  TestIsPrivateWindow(incognito_wallet_service(), true);
  TestIsPrivateWindow(wallet_service(), false);
}

}  // namespace qorai_wallet
