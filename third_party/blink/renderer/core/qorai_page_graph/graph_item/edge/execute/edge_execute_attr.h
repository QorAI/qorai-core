/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_EXECUTE_EDGE_EXECUTE_ATTR_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_EXECUTE_EDGE_EXECUTE_ATTR_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/execute/edge_execute.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/types.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class NodeHTMLElement;
class NodeScript;

class EdgeExecuteAttr : public EdgeExecute {
 public:
  EdgeExecuteAttr(GraphItemContext* context,
                  NodeHTMLElement* out_node,
                  NodeScript* in_node,
                  const FrameId& frame_id,
                  const blink::String& attribute_name);

  ~EdgeExecuteAttr() override;

  const blink::String& GetAttributeName() { return attribute_name_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsEdgeExecuteAttr() const override;

 private:
  const blink::String attribute_name_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeExecuteAttr> {
  static bool AllowFrom(const qorai_page_graph::EdgeExecute& edge) {
    return edge.IsEdgeExecuteAttr();
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeExecuteAttr>(
        DynamicTo<qorai_page_graph::EdgeExecute>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeExecuteAttr>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_EXECUTE_EDGE_EXECUTE_ATTR_H_
