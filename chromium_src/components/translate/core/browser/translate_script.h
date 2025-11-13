/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_SCRIPT_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_SCRIPT_H_

namespace translate {
class TranslateScript;
using QoraiTranslateScript = TranslateScript;
}  // namespace translate

#define TranslateScript ChromiumTranslateScript
#define OnScriptFetchComplete virtual OnScriptFetchComplete
#define Request virtual Request
#define callback_list_                             \
  callback_list_;                                  \
  static GURL AddHostLocaleToUrl(const GURL& url); \
  friend QoraiTranslateScript
#include <components/translate/core/browser/translate_script.h>  // IWYU pragma: export
#undef callback_list_
#undef Request
#undef OnScriptFetchComplete
#undef TranslateScript

namespace translate {

class TranslateScript : public ChromiumTranslateScript {
 public:
  using ChromiumTranslateScript::ChromiumTranslateScript;

  void OnScriptFetchComplete(bool success, const std::string& data) override;
  void Request(RequestCallback callback, bool is_incognito) override;
};

}  // namespace translate

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_SCRIPT_H_
