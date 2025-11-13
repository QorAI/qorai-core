/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/extensions/qorai_extension_provider.h"

#include <string>

#include "base/notreached.h"
#include "extensions/common/constants.h"

namespace extensions {

QoraiExtensionProvider::QoraiExtensionProvider() = default;

QoraiExtensionProvider::~QoraiExtensionProvider() = default;

std::string QoraiExtensionProvider::GetDebugPolicyProviderName() const {
#if defined(NDEBUG)
  NOTREACHED();
#else
  return "Qorai Extension Provider";
#endif
}

bool QoraiExtensionProvider::MustRemainInstalled(const Extension* extension,
                                                 std::u16string* error) const {
  return extension->id() == qorai_extension_id;
}

}  // namespace extensions
