// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/actor/node_unknown.h"

namespace qorai_page_graph {

NodeUnknown::NodeUnknown(GraphItemContext* context) : NodeActor(context) {}

NodeUnknown::~NodeUnknown() = default;

ItemName NodeUnknown::GetItemName() const {
  return "unknown actor";
}

bool NodeUnknown::IsNodeUnknown() const {
  return true;
}

}  // namespace qorai_page_graph
