/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_SET_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_SET_H_

#include <string>

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/storage/edge_storage.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class NodeActor;
class NodeStorage;

class EdgeStorageSet final : public EdgeStorage {
 public:
  EdgeStorageSet(GraphItemContext* context,
                 NodeActor* out_node,
                 NodeStorage* in_node,
                 const FrameId& frame_id,
                 const blink::String& key,
                 const blink::PageGraphValue& value);
  ~EdgeStorageSet() override;

  const std::string& GetValue() const { return value_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsEdgeStorageSet() const override;

 private:
  const std::string value_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeStorageSet> {
  static bool AllowFrom(const qorai_page_graph::EdgeStorage& storage_edge) {
    return storage_edge.IsEdgeStorageSet();
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeStorageSet>(
        DynamicTo<qorai_page_graph::EdgeStorage>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeStorageSet>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_SET_H_
