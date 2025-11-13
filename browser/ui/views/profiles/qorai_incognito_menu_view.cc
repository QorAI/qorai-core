/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/profiles/qorai_incognito_menu_view.h"

#include <memory>
#include <optional>
#include <utility>

#include "base/check.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/app/vector_icons/vector_icons.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/profiles/profile_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/grit/generated_resources.h"
#include "components/vector_icons/vector_icons.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/image_model.h"

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/tor/tor_profile_manager.h"
#include "qorai/browser/tor/tor_profile_service_factory.h"
#endif

namespace {

#if BUILDFLAG(ENABLE_TOR)
bool ShouldShowTorProfileButton(Profile* profile) {
  DCHECK(profile);
  return !TorProfileServiceFactory::IsTorDisabled(profile) && !profile->IsTor();
}
#endif

int GetProfileMenuTitleId(Profile& profile) {
  return profile.IsTor() ? IDS_TOR_PROFILE_NAME : IDS_PRIVATE_PROFILE_NAME;
}

int GetProfileMenuCloseButtonTextId(Profile& profile) {
  return profile.IsTor() ? IDS_PROFILES_EXIT_TOR : IDS_PROFILES_EXIT_PRIVATE;
}

}  // namespace

void QoraiIncognitoMenuView::BuildMenu() {
#if BUILDFLAG(ENABLE_TOR)
  AddTorButton();
#endif

  AddFeatureButton(
      l10n_util::GetStringUTF16(GetProfileMenuCloseButtonTextId(profile())),
      base::BindRepeating(&QoraiIncognitoMenuView::OnExitButtonClicked,
                          base::Unretained(this)),
      vector_icons::kCloseIcon);
}

void QoraiIncognitoMenuView::AddedToWidget() {
  IncognitoMenuView::AddedToWidget();

  ChromeLayoutProvider* provider = ChromeLayoutProvider::Get();
  // The icon color is set to match the menu text, which guarantees sufficient
  // contrast and a consistent visual appearance.
  const ui::ColorId icon_color = provider->GetTypographyProvider().GetColorId(
      views::style::CONTEXT_LABEL, views::style::STYLE_PRIMARY);

  IdentitySectionParams params;
  params.title = l10n_util::GetStringUTF16(GetProfileMenuTitleId(profile()));
  params.profile_image_padding = std::nearbyint(kIdentityInfoImageSize * 0.25f);
  params.profile_image =
      ui::ImageModel::FromVectorIcon(kIncognitoProfileIcon, icon_color);
  SetProfileIdentityWithCallToAction(std::move(params));
  AddBottomMargin();
}

#if BUILDFLAG(ENABLE_TOR)
void QoraiIncognitoMenuView::AddTorButton() {
  if (ShouldShowTorProfileButton(&profile())) {
    AddFeatureButton(
        l10n_util::GetStringUTF16(IDS_PROFILES_OPEN_TOR_PROFILE_BUTTON),
        base::BindRepeating(&QoraiIncognitoMenuView::OnTorProfileButtonClicked,
                            base::Unretained(this)),
        vector_icons::kLaunchIcon);
  }
}

void QoraiIncognitoMenuView::OnTorProfileButtonClicked() {
  TorProfileManager::SwitchToTorProfile(&profile());
}
#endif

std::u16string QoraiIncognitoMenuView::GetAccessibleWindowTitle() const {
  return profile().IsTor() ? l10n_util::GetStringUTF16(IDS_TOR_PROFILE_NAME)
                           : IncognitoMenuView::GetAccessibleWindowTitle();
}

void QoraiIncognitoMenuView::OnExitButtonClicked() {
  if (profile().IsTor()) {
    OnActionableItemClicked(ActionableItem::kExitProfileButton);
#if BUILDFLAG(ENABLE_TOR)
    TorProfileManager::CloseTorProfileWindows(&profile());
#endif
  } else {
    IncognitoMenuView::OnExitButtonClicked();
  }
}
