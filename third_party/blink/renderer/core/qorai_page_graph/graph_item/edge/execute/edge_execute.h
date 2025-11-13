/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_EXECUTE_EDGE_EXECUTE_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_EXECUTE_EDGE_EXECUTE_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/graph_edge.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/types.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeExtensions;
class NodeHTMLElement;
class NodeActor;
class NodeScript;

class EdgeExecute : public GraphEdge {
 public:
  EdgeExecute(GraphItemContext* context,
              NodeHTMLElement* out_node,
              NodeScript* in_node,
              const FrameId& frame_id);
  EdgeExecute(GraphItemContext* context,
              NodeExtensions* out_node,
              NodeScript* in_node,
              const FrameId& frame_id);
  // Used by imported module scripts and eval
  EdgeExecute(GraphItemContext* context,
              NodeActor* out_node,
              NodeScript* in_node,
              const FrameId& frame_id);
  ~EdgeExecute() override;

  ItemName GetItemName() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsEdgeExecute() const override;

  virtual bool IsEdgeExecuteAttr() const;

 private:
  const FrameId frame_id_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeExecute> {
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return edge.IsEdgeExecute();
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeExecute>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_EXECUTE_EDGE_EXECUTE_H_
