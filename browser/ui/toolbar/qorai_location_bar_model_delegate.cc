/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/toolbar/qorai_location_bar_model_delegate.h"

#include "base/check.h"
#include "base/feature_list.h"
#include "qorai/browser/ui/qorai_scheme_utils.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/components/constants/url_constants.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/browser/web_contents.h"
#include "extensions/buildflags/buildflags.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"
#include "qorai/browser/ui/tabs/shared_pinned_tab_service.h"
#include "qorai/browser/ui/tabs/shared_pinned_tab_service_factory.h"
#endif

QoraiLocationBarModelDelegate::QoraiLocationBarModelDelegate(
    TabStripModel* tab_strip_model)
    : BrowserLocationBarModelDelegate(tab_strip_model),
      tab_strip_model_(tab_strip_model) {}

QoraiLocationBarModelDelegate::~QoraiLocationBarModelDelegate() = default;

// static
void QoraiLocationBarModelDelegate::FormattedStringFromURL(
    const GURL& url,
    std::u16string* new_formatted_url) {
  // Replace chrome:// with qorai://
  qorai_utils::ReplaceChromeToQoraiScheme(*new_formatted_url);
}

std::u16string
QoraiLocationBarModelDelegate::FormattedStringWithEquivalentMeaning(
    const GURL& url,
    const std::u16string& formatted_url) const {
  std::u16string new_formatted_url =
      BrowserLocationBarModelDelegate::FormattedStringWithEquivalentMeaning(
          url, formatted_url);
  QoraiLocationBarModelDelegate::FormattedStringFromURL(url,
                                                        &new_formatted_url);
  return new_formatted_url;
}

bool QoraiLocationBarModelDelegate::GetURL(GURL* url) const {
#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(tabs::features::kQoraiSharedPinnedTabs) &&
      tab_strip_model_->profile()->GetPrefs()->GetBoolean(
          qorai_tabs::kSharedPinnedTab)) {
    content::NavigationEntry* entry = GetNavigationEntry();
    if (entry && entry->IsInitialEntry()) {
      auto* active_web_contents = GetActiveWebContents();
      auto* shared_pinned_tab_service =
          SharedPinnedTabServiceFactory::GetForProfile(
              Profile::FromBrowserContext(
                  GetActiveWebContents()->GetBrowserContext()));
      DCHECK(shared_pinned_tab_service);
      if (shared_pinned_tab_service->IsDummyContents(active_web_contents)) {
        // Override visible url for dummy contents so that about:blank is not
        // shown in the location bar.
        // In case of new tab, we don't want it to be shown. But other
        // chrome:// scheme should be visible.
        *url = entry->GetVirtualURL().spec() == "chrome://newtab/"
                   ? GURL()
                   : entry->GetVirtualURL();
        return true;
      }
    }
  }
#endif  // !BUILDFLAG(IS_ANDROID)

  return ChromeLocationBarModelDelegate::GetURL(url);
}
