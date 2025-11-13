/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_NODE_EDGE_NODE_DELETE_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_NODE_EDGE_NODE_DELETE_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/node/edge_node.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/types.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeHTML;
class NodeScript;

class EdgeNodeDelete final : public EdgeNode {
 public:
  EdgeNodeDelete(GraphItemContext* context,
                 NodeScript* out_node,
                 NodeHTML* in_node,
                 const FrameId& frame_id);
  ~EdgeNodeDelete() override;

  ItemName GetItemName() const override;

  bool IsEdgeNodeDelete() const override;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeNodeDelete> {
  static bool AllowFrom(const qorai_page_graph::EdgeNode& edge) {
    return edge.IsEdgeNodeDelete();
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeNodeDelete>(
        DynamicTo<qorai_page_graph::EdgeNode>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeNodeDelete>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_NODE_EDGE_NODE_DELETE_H_
