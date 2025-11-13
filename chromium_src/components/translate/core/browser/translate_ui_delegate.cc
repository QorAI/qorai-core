/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/translate/core/browser/translate_ui_delegate.h"

#include "qorai/components/translate/core/common/qorai_translate_features.h"

#define TranslateUIDelegate TranslateUIDelegate_ChromiumImpl
#include <components/translate/core/browser/translate_ui_delegate.cc>
#undef TranslateUIDelegate

namespace translate {

bool TranslateUIDelegate::ShouldShowAlwaysTranslateShortcut() const {
  if (!IsQoraiAutoTranslateEnabled())
    return false;

  return TranslateUIDelegate_ChromiumImpl::ShouldShowAlwaysTranslateShortcut();
}

#if BUILDFLAG(IS_ANDROID) || BUILDFLAG(IS_IOS)
bool TranslateUIDelegate::ShouldAutoAlwaysTranslate() {
  if (!IsQoraiAutoTranslateEnabled())
    return false;

  return TranslateUIDelegate_ChromiumImpl::ShouldAutoAlwaysTranslate();
}
#endif  // BUILDFLAG(IS_ANDROID) || BUILDFLAG(IS_IOS)

}  // namespace translate
