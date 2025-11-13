// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/content/browser/qorai_farbling_service.h"

#include "base/check.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "url/gurl.h"

namespace qorai {

QoraiFarblingService::QoraiFarblingService(
    HostContentSettingsMap* host_content_settings_map)
    : host_content_settings_map_(host_content_settings_map) {
  DCHECK(host_content_settings_map_);
}

QoraiFarblingService::~QoraiFarblingService() = default;

bool QoraiFarblingService::MakePseudoRandomGeneratorForURL(const GURL& url,
                                                           FarblingPRNG* prng) {
  if (qorai_shields::GetFarblingLevel(host_content_settings_map_, url) ==
      qorai_shields::mojom::FarblingLevel::OFF) {
    return false;
  }
  const base::Token farbling_token =
      qorai_shields::GetFarblingToken(host_content_settings_map_, url);
  if (farbling_token.is_zero()) {
    return false;
  }
  *prng = FarblingPRNG(farbling_token.high() ^ farbling_token.low());
  return true;
}

// static
void QoraiFarblingService::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(qorai_shields::prefs::kReduceLanguageEnabled,
                                true);
}

}  // namespace qorai
