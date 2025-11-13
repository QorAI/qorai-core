/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_FILTER_NODE_AD_FILTER_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_FILTER_NODE_AD_FILTER_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/filter/node_filter.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class NodeAdFilter : public NodeFilter {
 public:
  NodeAdFilter(GraphItemContext* context, const blink::String& rule);

  ~NodeAdFilter() override;

  const blink::String& GetRule() const { return rule_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsNodeAdFilter() const override;

 private:
  const blink::String rule_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::NodeAdFilter> {
  static bool AllowFrom(const qorai_page_graph::NodeFilter& filter_node) {
    return filter_node.IsNodeAdFilter();
  }
  static bool AllowFrom(const qorai_page_graph::GraphNode& node) {
    return IsA<qorai_page_graph::NodeAdFilter>(
        DynamicTo<qorai_page_graph::NodeFilter>(node));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::NodeAdFilter>(
        DynamicTo<qorai_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_FILTER_NODE_AD_FILTER_H_
