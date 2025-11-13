/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_CLEAR_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_CLEAR_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/storage/edge_storage.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeActor;
class NodeStorage;

class EdgeStorageClear final : public EdgeStorage {
 public:
  EdgeStorageClear(GraphItemContext* context,
                   NodeActor* out_node,
                   NodeStorage* in_node,
                   const FrameId& frame_id);
  ~EdgeStorageClear() override;

  ItemName GetItemName() const override;

  bool IsEdgeStorageClear() const override;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeStorageClear> {
  static bool AllowFrom(const qorai_page_graph::EdgeStorage& storage_edge) {
    return storage_edge.IsEdgeStorageClear();
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeStorageClear>(
        DynamicTo<qorai_page_graph::EdgeStorage>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeStorageClear>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_CLEAR_H_
