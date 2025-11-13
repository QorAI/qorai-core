/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/request/edge_request_redirect.h"

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/node_resource.h"

namespace qorai_page_graph {

EdgeRequestRedirect::EdgeRequestRedirect(GraphItemContext* context,
                                         NodeResource* out_node,
                                         NodeResource* in_node,
                                         const InspectorId request_id,
                                         const FrameId& frame_id,
                                         const ResponseMetadata& metadata)
    : EdgeRequestResponse(context,
                          out_node,
                          in_node,
                          request_id,
                          frame_id,
                          kRequestStatusRedirect,
                          metadata) {}

EdgeRequestRedirect::~EdgeRequestRedirect() = default;

ItemName EdgeRequestRedirect::GetItemName() const {
  return "request redirect";
}

bool EdgeRequestRedirect::IsEdgeRequestRedirect() const {
  return true;
}

}  // namespace qorai_page_graph
