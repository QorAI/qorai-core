/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE_H_
#define QORAI_BROWSER_QORAI_ADS_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE_H_

#include <string>
#include <vector>

#include "qorai/components/infobars/core/qorai_confirm_infobar_delegate.h"
#include "components/infobars/core/infobar_delegate.h"

class PrefService;
class GURL;
enum class WindowOpenDisposition;

namespace content {
class WebContents;
}  // namespace content

namespace ui {
class ImageModel;
}  // namespace ui

namespace qorai_ads {

class CreativeSearchResultAdClickedInfoBarDelegate
    : public QoraiConfirmInfoBarDelegate {
 public:
  CreativeSearchResultAdClickedInfoBarDelegate();

  CreativeSearchResultAdClickedInfoBarDelegate(
      const CreativeSearchResultAdClickedInfoBarDelegate&) = delete;
  CreativeSearchResultAdClickedInfoBarDelegate& operator=(
      const CreativeSearchResultAdClickedInfoBarDelegate&) = delete;

  ~CreativeSearchResultAdClickedInfoBarDelegate() override;

  static void Create(content::WebContents* web_contents, PrefService* prefs);

 private:
  // ConfirmInfoBarDelegate:
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  ui::ImageModel GetIcon() const override;
  std::u16string GetMessageText() const override;
  int GetButtons() const override;
  std::u16string GetLinkText() const override;
  GURL GetLinkURL() const override;
  bool LinkClicked(WindowOpenDisposition disposition) override;

  // QoraiConfirmInfoBarDelegate:
  std::vector<int> GetButtonsOrder() const override;
  bool ShouldSupportMultiLine() const override;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE_H_
