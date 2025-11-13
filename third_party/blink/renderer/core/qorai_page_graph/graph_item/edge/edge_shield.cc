/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/edge_shield.h"

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/shield/node_shield.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/shield/node_shields.h"

namespace qorai_page_graph {

EdgeShield::EdgeShield(GraphItemContext* context,
                       NodeShields* out_node,
                       NodeShield* in_node)
    : GraphEdge(context, out_node, in_node) {}

EdgeShield::~EdgeShield() = default;

ItemName EdgeShield::GetItemName() const {
  return "shield";
}

bool EdgeShield::IsEdgeShield() const {
  return true;
}

}  // namespace qorai_page_graph
