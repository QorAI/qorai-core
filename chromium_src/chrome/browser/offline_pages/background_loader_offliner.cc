/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/offline_pages/background_loader_offliner.h"

#include "qorai/browser/qorai_shields/qorai_shields_web_contents_observer.h"
#include "chrome/browser/content_settings/page_specific_content_settings_delegate.h"
#include "components/content_settings/browser/page_specific_content_settings.h"

#define PageSpecificContentSettings                                     \
  PageSpecificContentSettings* unused_pscs [[maybe_unused]];            \
  qorai_shields::QoraiShieldsWebContentsObserver::CreateForWebContents( \
      loader_->web_contents());                                         \
  content_settings::PageSpecificContentSettings

#include <chrome/browser/offline_pages/background_loader_offliner.cc>

#undef PageSpecificContentSettings
