// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/omnibox/browser/omnibox_text_util.h"

#include "url/gurl.h"

#if !BUILDFLAG(IS_IOS)
#include "content/public/common/url_constants.h"
#endif

namespace {
void QoraiAdjustTextForCopy(GURL* url) {
#if !BUILDFLAG(IS_IOS)
  if (url->scheme() == content::kChromeUIScheme) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kQoraiUIScheme);
    *url = url->ReplaceComponents(replacements);
  }
#endif
}

}  // namespace

#define QORAI_ADJUST_TEXT_FOR_COPY QoraiAdjustTextForCopy(url_from_text);

#include <components/omnibox/browser/omnibox_text_util.cc>

#undef QORAI_ADJUST_TEXT_FOR_COPY
