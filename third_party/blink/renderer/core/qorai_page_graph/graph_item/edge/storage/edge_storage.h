/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/graph_edge.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class GraphNode;

class EdgeStorage : public GraphEdge {
 public:
  EdgeStorage(GraphItemContext* context,
              GraphNode* out_node,
              GraphNode* in_node,
              const FrameId& frame_id,
              const blink::String& key);
  ~EdgeStorage() override;

  const blink::String& GetKey() const { return key_; }

  ItemName GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsEdgeStorage() const override;

  virtual bool IsEdgeStorageClear() const;
  virtual bool IsEdgeStorageDelete() const;
  virtual bool IsEdgeStorageReadCall() const;
  virtual bool IsEdgeStorageReadResult() const;
  virtual bool IsEdgeStorageSet() const;

 private:
  const FrameId frame_id_;
  const blink::String key_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeStorage> {
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return edge.IsEdgeStorage();
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeStorage>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_STORAGE_EDGE_STORAGE_H_
