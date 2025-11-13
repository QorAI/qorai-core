// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_ACTOR_NODE_SCRIPT_REMOTE_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_ACTOR_NODE_SCRIPT_REMOTE_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/actor/node_script.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class NodeScriptRemote : public NodeScript {
 public:
  NodeScriptRemote(GraphItemContext* context, const ScriptId script_id);
  ~NodeScriptRemote() override;

  ItemName GetItemName() const override;

  bool IsNodeScriptRemote() const override;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::NodeScriptRemote> {
  static bool AllowFrom(const qorai_page_graph::NodeActor& actor_node) {
    return actor_node.IsNodeScriptRemote();
  }
  static bool AllowFrom(const qorai_page_graph::GraphNode& node) {
    return IsA<qorai_page_graph::NodeScriptRemote>(
        DynamicTo<qorai_page_graph::GraphNode>(node));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::NodeScriptRemote>(
        DynamicTo<qorai_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_ACTOR_NODE_SCRIPT_REMOTE_H_
