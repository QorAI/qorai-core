// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_DOWNLOAD_QORAI_DOWNLOAD_COMMANDS_H_
#define QORAI_BROWSER_DOWNLOAD_QORAI_DOWNLOAD_COMMANDS_H_

#include "chrome/browser/download/download_commands.h"

// This class overrides the DownloadCommands class to provide Qorai-specific
// command handling. This class is used in DownloadBubbleRowView and
// DownloadShelfView.
class QoraiDownloadCommands : public DownloadCommands {
 public:
  using DownloadCommands::DownloadCommands;
  ~QoraiDownloadCommands() override = default;

  // DownloadCommands:
  bool IsCommandEnabled(Command command) const override;
  void ExecuteCommand(Command command) override;
};

#endif  // QORAI_BROWSER_DOWNLOAD_QORAI_DOWNLOAD_COMMANDS_H_
