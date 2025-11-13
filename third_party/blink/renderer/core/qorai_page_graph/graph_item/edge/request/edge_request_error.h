/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_REQUEST_EDGE_REQUEST_ERROR_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_REQUEST_EDGE_REQUEST_ERROR_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/request/edge_request_response.h"
#include "qorai/third_party/blink/renderer/core/qorai_page_graph/utilities/response_metadata.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class GraphNode;
class NodeResource;

class EdgeRequestError final : public EdgeRequestResponse {
 public:
  EdgeRequestError(GraphItemContext* context,
                   NodeResource* out_node,
                   GraphNode* in_node,
                   const InspectorId request_id,
                   const FrameId& frame_id,
                   const ResponseMetadata& metadata);
  ~EdgeRequestError() override;

  ItemName GetItemName() const override;

  bool IsEdgeRequestError() const override;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::EdgeRequestError> {
  static bool AllowFrom(
      const qorai_page_graph::EdgeRequestResponse& request_response_edge) {
    return request_response_edge.IsEdgeRequestError();
  }
  static bool AllowFrom(const qorai_page_graph::EdgeRequest& request_edge) {
    return IsA<qorai_page_graph::EdgeRequestError>(
        DynamicTo<qorai_page_graph::EdgeRequestResponse>(request_edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphEdge& edge) {
    return IsA<qorai_page_graph::EdgeRequestError>(
        DynamicTo<qorai_page_graph::EdgeRequest>(edge));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::EdgeRequestError>(
        DynamicTo<qorai_page_graph::GraphEdge>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_EDGE_REQUEST_EDGE_REQUEST_ERROR_H_
