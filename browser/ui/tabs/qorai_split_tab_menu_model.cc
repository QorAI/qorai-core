/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/tabs/qorai_split_tab_menu_model.h"

#include <memory>

#include "qorai/components/vector_icons/vector_icons.h"
#include "chrome/browser/ui/tabs/split_tab_util.h"
#include "components/grit/qorai_components_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/image_model.h"

std::unique_ptr<ui::SimpleMenuModel> CreateQoraiSplitTabMenuModel(
    TabStripModel* tab_strip_model,
    SplitTabMenuModel::MenuSource source) {
  return std::make_unique<QoraiSplitTabMenuModel>(tab_strip_model, source);
}

QoraiSplitTabMenuModel::QoraiSplitTabMenuModel(
    TabStripModel* tab_strip_model,
    MenuSource menu_source,
    std::optional<int> split_tab_index)
    : SplitTabMenuModel(tab_strip_model, menu_source, split_tab_index) {
  // Remove "Send feedback" and the separator above it.
  auto feedback_command_index =
      GetIndexOfCommandId(GetCommandIdInt(CommandId::kSendFeedback));
  if (feedback_command_index.has_value()) {
    CHECK(feedback_command_index.value() > 1);
    auto separator_index = feedback_command_index.value() - 1;
    CHECK(GetSeparatorTypeAt(separator_index) ==
          ui::MenuSeparatorType::NORMAL_SEPARATOR);
    RemoveItemAt(feedback_command_index.value());
    RemoveItemAt(separator_index);
  }
}

QoraiSplitTabMenuModel::~QoraiSplitTabMenuModel() = default;

bool QoraiSplitTabMenuModel::IsItemForCommandIdDynamic(int command_id) const {
  const CommandId id = GetCommandIdEnum(command_id);

  // It's not dynamic but handle like that to apply our label/icon via GetXXX().
  if (id == CommandId::kExitSplit) {
    return true;
  }

  return SplitTabMenuModel::IsItemForCommandIdDynamic(command_id);
}

std::u16string QoraiSplitTabMenuModel::GetLabelForCommandId(
    int command_id) const {
  const CommandId id = GetCommandIdEnum(command_id);

  if (id == CommandId::kReversePosition) {
    return l10n_util::GetStringUTF16(IDS_IDC_SWAP_SPLIT_VIEW);
  }

  if (id == CommandId::kExitSplit) {
    return l10n_util::GetStringUTF16(IDS_IDC_BREAK_TILE);
  }

  return SplitTabMenuModel::GetLabelForCommandId(command_id);
}

ui::ImageModel QoraiSplitTabMenuModel::GetIconForCommandId(
    int command_id) const {
  const CommandId id = GetCommandIdEnum(command_id);

  if (id == CommandId::kExitSplit) {
    return ui::ImageModel::FromVectorIcon(
        kQoraBrowserSplitViewUnsplitIcon, ui::kColorMenuIcon,
        ui::SimpleMenuModel::kDefaultIconSize);
  }

  return SplitTabMenuModel::GetIconForCommandId(command_id);
}

const gfx::VectorIcon& QoraiSplitTabMenuModel::GetReversePositionIcon(
    split_tabs::SplitTabActiveLocation active_split_tab_location) const {
  switch (active_split_tab_location) {
    case split_tabs::SplitTabActiveLocation::kStart:
      [[fallthrough]];
    case split_tabs::SplitTabActiveLocation::kEnd:
      return kQoraSwapHorizontalIcon;
    default:
      return SplitTabMenuModel::GetReversePositionIcon(
          active_split_tab_location);
  }
}
