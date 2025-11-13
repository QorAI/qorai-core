/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_TRANSLATE_QORAI_TRANSLATE_UTILS_H_
#define QORAI_BROWSER_TRANSLATE_QORAI_TRANSLATE_UTILS_H_

namespace content {
class BrowserContext;
}
namespace translate {

bool IsTranslateExtensionEnabled(content::BrowserContext* context);

}  // namespace translate

#endif  // QORAI_BROWSER_TRANSLATE_QORAI_TRANSLATE_UTILS_H_
