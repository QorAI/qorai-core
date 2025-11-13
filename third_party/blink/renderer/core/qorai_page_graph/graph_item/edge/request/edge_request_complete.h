/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_REQUEST_EDGE_REQUEST_COMPLETE_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_REQUEST_EDGE_REQUEST_COMPLETE_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/request/edge_request_response.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/utilities/response_metadata.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class GraphNode;
class NodeResource;

class EdgeRequestComplete final : public EdgeRequestResponse {
 public:
  EdgeRequestComplete(GraphItemContext* context,
                      NodeResource* out_node,
                      GraphNode* in_node,
                      const InspectorId request_id,
                      const FrameId& frame_id,
                      const blink::String& resource_type,
                      const ResponseMetadata& metadata,
                      const blink::String& hash);

  ~EdgeRequestComplete() override;

  const blink::String& GetResourceType() const { return resource_type_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsEdgeRequestComplete() const override;

 private:
  const blink::String resource_type_;
  const blink::String hash_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeRequestComplete> {
  static bool AllowFrom(
      const qorai_page_graph::EdgeRequestResponse& request_response_edge) {
    return request_response_edge.IsEdgeRequestComplete();
  }
  static bool AllowFrom(const qorai_page_graph::EdgeRequest& request_edge) {
    return IsA<qorai_page_graph::EdgeRequestComplete>(
        DynamicTo<qorai_page_graph::EdgeRequestResponse>(request_edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeRequestComplete>(
        DynamicTo<qorai_page_graph::EdgeRequest>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeRequestComplete>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_REQUEST_EDGE_REQUEST_COMPLETE_H_
