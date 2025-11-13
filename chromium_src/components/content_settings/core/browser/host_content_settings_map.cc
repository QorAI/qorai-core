/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/content_settings/core/browser/host_content_settings_map.h"

#include "qorai/components/content_settings/core/browser/remote_list_provider.h"
#include "build/build_config.h"

#if !BUILDFLAG(IS_IOS)
#include "qorai/components/content_settings/core/browser/qorai_content_settings_pref_provider.h"
#define PrefProvider QoraiPrefProvider
#endif

#include <components/content_settings/core/browser/host_content_settings_map.cc>

#if !BUILDFLAG(IS_IOS)
#undef PrefProvider
#undef PolicyProvider
#endif
