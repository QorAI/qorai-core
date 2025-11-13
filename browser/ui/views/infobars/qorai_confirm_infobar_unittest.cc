/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/infobars/qorai_confirm_infobar.h"

#include "qorai/components/infobars/core/qorai_confirm_infobar_delegate.h"
#include "chrome/test/views/chrome_views_test_base.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "ui/views/view.h"

using QoraiConfirmInfoBarTest = ChromeViewsTestBase;

namespace {

class TestInfoBarDelegate : public QoraiConfirmInfoBarDelegate {
 public:
  TestInfoBarDelegate() = default;
  ~TestInfoBarDelegate() override = default;

  // QoraiConfirmInfoBarDelegate:
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override {
    return TEST_INFOBAR;
  }

  int GetButtons() const override { return BUTTON_NONE; }

  std::u16string GetMessageText() const override { return u""; }
};

}  // namespace

// Check close button is always the last children.
TEST_F(QoraiConfirmInfoBarTest, CloseButtonOrderTest) {
  auto infobar = std::make_unique<QoraiConfirmInfoBar>(
      (std::make_unique<TestInfoBarDelegate>()));
  auto* close_button = infobar->close_button_for_testing();
  ASSERT_TRUE(close_button);
  EXPECT_EQ(close_button, infobar->children().back());
}
