/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/qorai_news/qorai_news_bubble_controller.h"

#include <vector>

#include "base/check.h"
#include "base/memory/ptr_util.h"
#include "qorai/browser/ui/views/qorai_news/qorai_news_action_icon_view.h"
#include "qorai/browser/ui/views/qorai_news/qorai_news_bubble_view.h"
#include "ui/views/bubble/bubble_dialog_delegate_view.h"

namespace qorai_news {
// static
QoraiNewsBubbleController*
QoraiNewsBubbleController::CreateOrGetFromWebContents(
    content::WebContents* web_contents) {
  CHECK(web_contents);
  QoraiNewsBubbleController::CreateForWebContents(web_contents);
  return QoraiNewsBubbleController::FromWebContents(web_contents);
}

QoraiNewsBubbleController::~QoraiNewsBubbleController() = default;

void QoraiNewsBubbleController::ShowBubble(
    base::WeakPtr<QoraiNewsActionIconView> anchor_view) {
  if (!anchor_view) {
    return;
  }

  bubble_ = new QoraiNewsBubbleView(anchor_view.get(), web_contents_);
  views::BubbleDialogDelegateView::CreateBubble(
      base::WrapUnique(
          static_cast<views::BubbleDialogDelegateView*>(bubble_.get())))
      ->Show();
}

QoraiNewsBubbleView* QoraiNewsBubbleController::GetBubble() {
  return bubble_;
}

void QoraiNewsBubbleController::OnBubbleClosed() {
  bubble_ = nullptr;
}

base::WeakPtr<QoraiNewsBubbleController>
QoraiNewsBubbleController::AsWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}

QoraiNewsBubbleController::QoraiNewsBubbleController(
    content::WebContents* web_contents)
    : content::WebContentsUserData<QoraiNewsBubbleController>(*web_contents),
      web_contents_(web_contents) {}

WEB_CONTENTS_USER_DATA_KEY_IMPL(QoraiNewsBubbleController);

}  // namespace qorai_news
