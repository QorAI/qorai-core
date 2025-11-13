/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_JS_EDGE_JS_RESULT_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_JS_EDGE_JS_RESULT_H_

#include <string>

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/blink_probe_types.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/js/edge_js.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeScript;
class NodeJS;

class EdgeJSResult final : public EdgeJS {
 public:
  EdgeJSResult(GraphItemContext* context,
               NodeJS* out_node,
               NodeScript* in_node,
               const FrameId& frame_id,
               const blink::PageGraphValue& result);

  ~EdgeJSResult() override;

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  const std::string& GetResult() const;
  const MethodName& GetMethodName() const override;
  bool IsEdgeJSResult() const override;

 private:
  const std::string result_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeJSResult> {
  static bool AllowFrom(const qorai_page_graph::EdgeJS& edge) {
    return edge.IsEdgeJSResult();
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeJSResult>(
        DynamicTo<qorai_page_graph::EdgeJS>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeJSResult>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_JS_EDGE_JS_RESULT_H_
