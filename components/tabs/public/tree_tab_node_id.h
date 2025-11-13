// Copyright (c) 2025 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_TABS_PUBLIC_TREE_TAB_NODE_ID_H_
#define QORAI_COMPONENTS_TABS_PUBLIC_TREE_TAB_NODE_ID_H_

#include "components/tab_groups/token_id.h"

namespace tree_tab {

class TreeTabNodeId : public tab_groups::TokenId<TreeTabNodeId> {};

// For use in std::unordered_map.
using TreeTabNodeIdHash = tab_groups::TokenIdHash<TreeTabNodeId>;

}  // namespace tree_tab

#endif  // QORAI_COMPONENTS_TABS_PUBLIC_TREE_TAB_NODE_ID_H_
