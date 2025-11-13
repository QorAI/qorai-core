/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_DOM_ROOT_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_DOM_ROOT_H_

#include "qorai/third_party/blink/renderer/core/qorai_page_graph/graph_item/node/html/node_html_element.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace qorai_page_graph {

class NodeDOMRoot final : public NodeHTMLElement {
 public:
  NodeDOMRoot(GraphItemContext* context,
              const blink::DOMNodeId dom_node_id,
              const blink::String& tag_name,
              bool is_attached);

  void SetURL(const blink::String& url) { url_ = url; }
  const blink::String& GetURL() const { return url_; }

  void SetSecurityOrigin(const blink::String& security_origin) {
    security_origin_ = security_origin;
  }
  const blink::String& GetSecurityOrigin() const { return security_origin_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsNodeDOMRoot() const override;

 private:
  blink::String url_;
  blink::String security_origin_;
  const bool is_attached_;
};

}  // namespace qorai_page_graph

namespace blink {

template <>
struct DowncastTraits<qorai_page_graph::NodeDOMRoot> {
  static bool AllowFrom(const qorai_page_graph::NodeHTMLElement& element_node) {
    return element_node.IsNodeDOMRoot();
  }
  static bool AllowFrom(const qorai_page_graph::NodeHTML& html_node) {
    return IsA<qorai_page_graph::NodeDOMRoot>(
        DynamicTo<qorai_page_graph::NodeHTMLElement>(html_node));
  }
  static bool AllowFrom(const qorai_page_graph::GraphNode& node) {
    return IsA<qorai_page_graph::NodeDOMRoot>(
        DynamicTo<qorai_page_graph::NodeHTML>(node));
  }
  static bool AllowFrom(const qorai_page_graph::GraphItem& graph_item) {
    return IsA<qorai_page_graph::NodeDOMRoot>(
        DynamicTo<qorai_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_CORE_QORAI_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_DOM_ROOT_H_
