/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/edge/attribute/edge_attribute_delete.h"

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/types.h"

namespace qorai_page_graph {

EdgeAttributeDelete::EdgeAttributeDelete(GraphItemContext* context,
                                         NodeActor* out_node,
                                         NodeHTMLElement* in_node,
                                         const FrameId& frame_id,
                                         const blink::String& name,
                                         const bool is_style)
    : EdgeAttribute(context, out_node, in_node, frame_id, name, is_style) {}

EdgeAttributeDelete::~EdgeAttributeDelete() = default;

ItemName EdgeAttributeDelete::GetItemName() const {
  return "delete attribute";
}

bool EdgeAttributeDelete::IsEdgeAttributeDelete() const {
  return true;
}

}  // namespace qorai_page_graph
