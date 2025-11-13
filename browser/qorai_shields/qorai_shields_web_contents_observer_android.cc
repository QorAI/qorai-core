/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_shields/qorai_shields_web_contents_observer.h"

#include <string>

#include "qorai/browser/android/qorai_shields_content_settings.h"
#include "chrome/browser/android/tab_android.h"
#include "content/public/browser/web_contents.h"

using content::WebContents;

namespace qorai_shields {
// static
void QorAIShieldsWebContentsObserver::DispatchBlockedEventForWebContents(
    const std::string& block_type,
    const std::string& subresource,
    WebContents* web_contents) {
  if (!web_contents) {
    return;
  }

  int tabId = 0;
  TabAndroid* tab = TabAndroid::FromWebContents(web_contents);
  if (tab) {
    tabId = tab->GetAndroidId();
  }
  chrome::android::QorAIShieldsContentSettings::DispatchBlockedEvent(
      tabId, block_type, subresource);
}

}  // namespace qorai_shields
