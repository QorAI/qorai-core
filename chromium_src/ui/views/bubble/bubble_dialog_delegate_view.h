/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_UI_VIEWS_BUBBLE_BUBBLE_DIALOG_DELEGATE_VIEW_H_
#define QORAI_CHROMIUM_SRC_UI_VIEWS_BUBBLE_BUBBLE_DIALOG_DELEGATE_VIEW_H_

#include "ui/views/window/dialog_delegate.h"

class QoraiNewsBubbleView;
class QoraiHelpBubbleDelegateView;
class SplitViewMenuBubble;
class WaybackMachineBubbleView;
class SidebarItemAddedFeedbackBubble;
class SidebarEditItemBubbleDelegateView;
class SidebarAddItemBubbleDelegateView;

namespace playlist {
class PlaylistBubbleView;
}  // namespace playlist

namespace views {
class QoraiBubbleDialogDelegateView;
}

#define CreatePassKey                                  \
  CreatePassKey_Unused();                              \
  friend class ::QoraiNewsBubbleView;                  \
  friend class ::QoraiHelpBubbleDelegateView;          \
  friend class ::WaybackMachineBubbleView;             \
  friend class ::playlist::PlaylistBubbleView;         \
  friend class ::SplitViewMenuBubble;                  \
  friend class ::SidebarItemAddedFeedbackBubble;       \
  friend class ::SidebarEditItemBubbleDelegateView;    \
  friend class ::SidebarAddItemBubbleDelegateView;     \
  friend class ::views::QoraiBubbleDialogDelegateView; \
  static BddvPassKey CreatePassKey

#include <ui/views/bubble/bubble_dialog_delegate_view.h>  // IWYU pragma: export

#undef CreatePassKey

#endif  // QORAI_CHROMIUM_SRC_UI_VIEWS_BUBBLE_BUBBLE_DIALOG_DELEGATE_VIEW_H_
