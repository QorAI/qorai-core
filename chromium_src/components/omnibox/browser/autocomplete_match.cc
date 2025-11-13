// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "components/omnibox/browser/autocomplete_match.h"

#include "qorai/components/omnibox/browser/commander_provider.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "components/grit/qorai_components_strings.h"
#include "components/search_engines/template_url_starter_pack_data.h"

#if (!BUILDFLAG(IS_ANDROID) || BUILDFLAG(ENABLE_VR)) && !BUILDFLAG(IS_IOS)
const gfx::VectorIcon& AutocompleteMatch::GetVectorIcon(
    bool is_bookmark,
    const TemplateURL* turl) const {
  // TODO: `GetAdditionalInfoForDebugging()` shouldn't be used for non-debugging
  // purposes.
  if (!GetAdditionalInfoForDebugging(commander::kCommanderMatchMarker)
           .empty()) {
    return kQoraCaratRightIcon;
  }
  if (type == Type::STARTER_PACK && turl &&
      turl->GetBuiltinEngineType() ==
          KEYWORD_MODE_STARTER_PACK_ASK_QORAI_SEARCH) {
    return kQoraMessageBubbleAskIcon;
  }
  return GetVectorIcon_Chromium(is_bookmark, turl);
}

#define GetVectorIcon GetVectorIcon_Chromium
#endif

// Add case statements to set omnibox placeholder message IDs for Qorai-defined
// starter packs.
#define kAiMode                                                     \
  kAskQoraiSearch:                                                  \
  message_id = IDS_OMNIBOX_ASK_QORAI_SEARCH_SCOPE_PLACEHOLDER_TEXT; \
  break;                                                            \
  case template_url_starter_pack_data::kAiMode

#include <components/omnibox/browser/autocomplete_match.cc>  // IWYU pragma: export

#undef kAiMode
#undef GetVectorIcon
