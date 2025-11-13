/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_BINDING_EDGE_BINDING_EVENT_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_BINDING_EDGE_BINDING_EVENT_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/graph_edge.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeBindingEvent;
class NodeScript;

class EdgeBindingEvent : public GraphEdge {
 public:
  EdgeBindingEvent(GraphItemContext* context,
                   NodeScript* out_node,
                   NodeBindingEvent* in_node,
                   const ScriptPosition script_position);
  ~EdgeBindingEvent() override;

  ScriptPosition GetScriptPosition() const { return script_position_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsEdgeBindingEvent() const override;

 private:
  const ScriptPosition script_position_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeBindingEvent> {
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return edge.IsEdgeBindingEvent();
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeBindingEvent>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_BINDING_EDGE_BINDING_EVENT_H_
