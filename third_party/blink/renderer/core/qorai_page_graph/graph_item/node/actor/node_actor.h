/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_ACTOR_NODE_ACTOR_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_ACTOR_NODE_ACTOR_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/graph_node.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace qorai_page_graph {

class NodeActor : public GraphNode {
 public:
  explicit NodeActor(GraphItemContext* context);
  ~NodeActor() override;

  bool IsNodeActor() const override;

  virtual bool IsNodeParser() const;
  virtual bool IsNodeScript() const;
  virtual bool IsNodeScriptLocal() const;
  virtual bool IsNodeScriptRemote() const;
  virtual bool IsNodeUnknown() const;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::NodeActor> {
  static bool AllowFrom(const qorai_page_graph::GraphNode& node) {
    return node.IsNodeActor();
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::NodeActor>(
        DynamicTo<qorai_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_ACTOR_NODE_ACTOR_H_
