/* Copyright (c) 2018 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_browser_content_setting_bubble_model_delegate.h"

#include "base/check_deref.h"
#include "qorai/components/constants/url_constants.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_tabstrip.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"

constexpr char kQoraiCommunitySupportUrl[] = "https://community.qorai.app/";

QoraiBrowserContentSettingBubbleModelDelegate::
    QoraiBrowserContentSettingBubbleModelDelegate(
        BrowserWindowInterface* browser)
    : BrowserContentSettingBubbleModelDelegate(browser),
      browser_(CHECK_DEREF(browser)) {}

QoraiBrowserContentSettingBubbleModelDelegate::
    ~QoraiBrowserContentSettingBubbleModelDelegate() = default;

void
QoraiBrowserContentSettingBubbleModelDelegate::ShowWidevineLearnMorePage() {
  GURL learn_more_url = GURL(kWidevineTOS);
  chrome::AddSelectedTabWithURL(browser_->GetBrowserForMigrationOnly(),
                                learn_more_url, ui::PAGE_TRANSITION_LINK);
}

void QoraiBrowserContentSettingBubbleModelDelegate::ShowLearnMorePage(
    ContentSettingsType type) {
  // TODO(yrliou): Use specific support pages for each content setting type
  GURL learn_more_url(kQoraiCommunitySupportUrl);
  chrome::AddSelectedTabWithURL(browser_->GetBrowserForMigrationOnly(),
                                learn_more_url, ui::PAGE_TRANSITION_LINK);
}
