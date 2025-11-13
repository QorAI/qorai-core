// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/android/qorai_tab_features.h"

#include "qorai/browser/ai_chat/ai_chat_utils.h"
#include "qorai/browser/ai_chat/tab_data_web_contents_observer.h"
#include "chrome/browser/android/tab_android.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"

namespace tabs {

QoraiTabFeatures::QoraiTabFeatures(content::WebContents* web_contents,
                                   Profile* profile)
    : TabFeatures_Chromium(web_contents, profile) {
  if (ai_chat::IsAllowedForContext(profile)) {
    tab_data_observer_ = std::make_unique<ai_chat::TabDataWebContentsObserver>(
        TabAndroid::FromWebContents(web_contents)->GetAndroidId(),
        web_contents);
  }
}

QoraiTabFeatures::~QoraiTabFeatures() = default;

TabFeatures::TabFeatures(content::WebContents* web_contents, Profile* profile)
    : qorai_tab_features_(
          std::make_unique<QoraiTabFeatures>(web_contents, profile)) {}

TabFeatures::~TabFeatures() = default;

// static
QoraiTabFeatures* QoraiTabFeatures::FromTabFeatures(TabFeatures* tab_features) {
  return static_cast<QoraiTabFeatures*>(
      tab_features->qorai_tab_features_.get());
}

}  // namespace tabs
