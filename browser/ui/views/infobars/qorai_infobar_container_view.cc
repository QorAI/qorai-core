/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/infobars/qorai_infobar_container_view.h"

#include <memory>

#include "base/check.h"
#include "ui/base/metadata/metadata_impl_macros.h"

QoraiInfoBarContainerView::QoraiInfoBarContainerView(
    infobars::InfoBarContainer::Delegate* delegate)
    : InfoBarContainerView(delegate) {
  // To hide shadow, replace it with empty view.
  DCHECK(content_shadow_);
  RemoveChildViewT(content_shadow_.ExtractAsDangling());
  content_shadow_ = AddChildView(std::make_unique<views::View>());
}

QoraiInfoBarContainerView::~QoraiInfoBarContainerView() = default;

BEGIN_METADATA(QoraiInfoBarContainerView)
END_METADATA
