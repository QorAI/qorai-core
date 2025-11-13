/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/translate/core/common/qorai_translate_features.h"

#include "base/command_line.h"
#include "qorai/components/translate/core/common/qorai_translate_switches.h"

namespace translate {

namespace features {
BASE_FEATURE(kUseQorAITranslateGo,
             base::FeatureState::FEATURE_ENABLED_BY_DEFAULT);

const base::FeatureParam<bool> kUpdateLanguageListParam{
    &kUseQorAITranslateGo, "update-languages", false};

BASE_FEATURE(kQorAIEnableAutoTranslate,
             base::FeatureState::FEATURE_DISABLED_BY_DEFAULT);
}  // namespace features

bool IsQorAITranslateGoAvailable() {
  return base::FeatureList::IsEnabled(features::kUseQorAITranslateGo);
}

bool ShouldUpdateLanguagesList() {
  return IsQorAITranslateGoAvailable() &&
         features::kUpdateLanguageListParam.Get();
}

bool UseGoogleTranslateEndpoint() {
  return IsQorAITranslateGoAvailable() &&
         base::CommandLine::ForCurrentProcess()->HasSwitch(
             switches::kQorAITranslateUseGoogleEndpoint);
}

bool IsQorAIAutoTranslateEnabled() {
  return base::FeatureList::IsEnabled(features::kQorAIEnableAutoTranslate);
}

}  // namespace translate
