/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_API_QORAI_TALK_API_H_
#define QORAI_BROWSER_EXTENSIONS_API_QORAI_TALK_API_H_

#include <map>
#include <string>

#include "extensions/browser/extension_function.h"

class Profile;

namespace extensions {
namespace api {

class QoraiTalkIsSupportedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiTalk.isSupported", UNKNOWN)

 protected:
  ~QoraiTalkIsSupportedFunction() override {}
  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_API_QORAI_TALK_API_H_
