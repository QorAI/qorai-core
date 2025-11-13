/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_attributes.h"
#include "qorai/browser/ui/views/qorai_tooltips/qorai_tooltip_popup.h"
#include "chrome/test/views/chrome_views_test_base.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "ui/events/base_event_utils.h"
#include "ui/views/controls/button/button.h"

class MockQoraiTooltipDelegate : public qorai_tooltips::QoraiTooltipDelegate {
 public:
  MockQoraiTooltipDelegate() {
    ON_CALL(*this, OnTooltipWidgetDestroyed).WillByDefault([this] {
      run_loop_.Quit();
    });
  }

  MOCK_METHOD1(OnTooltipShow, void(const std::string&));
  MOCK_METHOD1(OnTooltipClose, void(const std::string&));
  MOCK_METHOD1(OnTooltipWidgetDestroyed, void(const std::string&));
  MOCK_METHOD1(OnTooltipOkButtonPressed, void(const std::string&));
  MOCK_METHOD1(OnTooltipCancelButtonPressed, void(const std::string&));

  void WaitForWidgetDestroyedNotification() { run_loop_.Run(); }

  base::WeakPtr<QoraiTooltipDelegate> AsWeakPtr() override {
    return weak_ptr_factory_.GetWeakPtr();
  }

 private:
  base::RunLoop run_loop_;
  base::WeakPtrFactory<QoraiTooltipDelegate> weak_ptr_factory_{this};
};

class QoraiTooltipsTest : public ChromeViewsTestBase {
 public:
  QoraiTooltipsTest() = default;

 protected:
  std::unique_ptr<qorai_tooltips::QoraiTooltipPopup> CreateTooltipPopup(
      const std::string& id,
      const qorai_tooltips::QoraiTooltipAttributes& attributes) {
    auto tooltip = std::make_unique<qorai_tooltips::QoraiTooltip>(
        id, attributes, mock_tooltip_delegate_.AsWeakPtr());
    return std::make_unique<qorai_tooltips::QoraiTooltipPopup>(
        std::move(tooltip));
  }

  void ClickButton(views::Button* button) const {
    ui::MouseEvent press_event(ui::EventType::kMousePressed, gfx::Point(1, 1),
                               gfx::Point(), ui::EventTimeForNow(),
                               ui::EF_LEFT_MOUSE_BUTTON, 0);
    button->OnMousePressed(press_event);
    ui::MouseEvent release_event(
        ui::EventType::kMouseReleased, gfx::Point(1, 1), gfx::Point(),
        ui::EventTimeForNow(), ui::EF_LEFT_MOUSE_BUTTON, 0);
    button->OnMouseReleased(release_event);
  }

  testing::NiceMock<MockQoraiTooltipDelegate> mock_tooltip_delegate_;
};

TEST_F(QoraiTooltipsTest, OkButtonPressed) {
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipShow(testing::_));
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipOkButtonPressed(testing::_));
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipClose(testing::_));
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipWidgetDestroyed(testing::_));

  auto tooltip_popup = CreateTooltipPopup(
      "id", qorai_tooltips::QoraiTooltipAttributes(u"Title", u"Body", u"OK"));
  ASSERT_TRUE(tooltip_popup);

  tooltip_popup->Show();

  ClickButton(tooltip_popup->ok_button_for_testing());

  mock_tooltip_delegate_.WaitForWidgetDestroyedNotification();

  // Reset the widget so that no UX objects leak. This will also delete the
  // popup, so we need to release the pointer.
  tooltip_popup->widget_.reset();
  tooltip_popup.release();
}

TEST_F(QoraiTooltipsTest, CancelButtonPressed) {
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipShow(testing::_));
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipCancelButtonPressed(testing::_));
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipClose(testing::_));
  EXPECT_CALL(mock_tooltip_delegate_, OnTooltipWidgetDestroyed(testing::_));

  auto tooltip_popup =
      CreateTooltipPopup("id", qorai_tooltips::QoraiTooltipAttributes(
                                   u"Title", u"Body", u"OK", u"Cancel"));
  ASSERT_TRUE(tooltip_popup);

  tooltip_popup->Show();

  ClickButton(tooltip_popup->cancel_button_for_testing());

  mock_tooltip_delegate_.WaitForWidgetDestroyedNotification();

  // Reset the widget so that no UX objects leak. This will also delete the
  // popup, so we need to release the pointer.
  tooltip_popup->widget_.reset();
  tooltip_popup.release();
}
