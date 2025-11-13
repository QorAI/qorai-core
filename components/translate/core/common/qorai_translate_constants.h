/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_TRANSLATE_CORE_COMMON_QORAI_TRANSLATE_CONSTANTS_H_
#define QORAI_COMPONENTS_TRANSLATE_CORE_COMMON_QORAI_TRANSLATE_CONSTANTS_H_

namespace translate {

inline constexpr char kQorAITranslateOrigin[] = "https://translate.qorai.com";
inline constexpr char kQorAITranslateScriptURL[] =
    "https://translate.qorai.com/static/v1/element.js";

// The used version of translate static resources (js/css files).
// Used in qorai_translate.js as a replacement to /translate_static/ part in
// original script URLs.
inline constexpr char kQorAITranslateStaticPath[] = "/static/v1/";

}  // namespace translate

#endif  // QORAI_COMPONENTS_TRANSLATE_CORE_COMMON_QORAI_TRANSLATE_CONSTANTS_H_
