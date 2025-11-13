/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_TRANSLATE_CORE_COMMON_QORAI_TRANSLATE_SWITCHES_H_
#define QORAI_COMPONENTS_TRANSLATE_CORE_COMMON_QORAI_TRANSLATE_SWITCHES_H_

namespace translate {
namespace switches {

// A test switch to disable the redirection for the translation requests to
// translate.qorai.com.
inline constexpr char kQorAITranslateUseGoogleEndpoint[] =
    "use-google-translate-endpoint";

}  // namespace switches
}  // namespace translate

#endif  // QORAI_COMPONENTS_TRANSLATE_CORE_COMMON_QORAI_TRANSLATE_SWITCHES_H_
