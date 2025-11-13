/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_BUCKET_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_BUCKET_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/graph_edge.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeStorage;
class NodeStorageRoot;

class EdgeStorageBucket : public GraphEdge {
 public:
  EdgeStorageBucket(GraphItemContext* context,
                    NodeStorageRoot* out_node,
                    NodeStorage* in_node);
  ~EdgeStorageBucket() override;

  ItemName GetItemName() const override;

  bool IsEdgeStorageBucket() const override;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeStorageBucket> {
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return edge.IsEdgeStorageBucket();
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeStorageBucket>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_BUCKET_H_
