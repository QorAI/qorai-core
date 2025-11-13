/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/color/playlist/playlist_color_mixer.h"

#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/ui/color/nala/nala_color_id.h"
#include "ui/color/color_mixer.h"
#include "ui/color/color_provider.h"
#include "ui/color/color_recipe.h"

namespace playlist {

void AddThemeColorMixer(ui::ColorProvider* provider,
                        const ui::ColorProviderKey& key) {
  ui::ColorMixer& mixer = provider->AddMixer();
  mixer[kColorQoraiPlaylistAddedIcon] = {nala::kColorSystemfeedbackSuccessIcon};
  mixer[kColorQoraiPlaylistCheckedIcon] = {nala::kColorIconInteractive};
  mixer[kColorQoraiPlaylistSelectedBackground] = {
      nala::kColorContainerInteractive};
  mixer[kColorQoraiPlaylistListBorder] = {nala::kColorDividerSubtle};
  mixer[kColorQoraiPlaylistMoveDialogDescription] = {nala::kColorTextSecondary};
  mixer[kColorQoraiPlaylistMoveDialogCreatePlaylistAndMoveTitle] = {
      nala::kColorTextPrimary};
  mixer[kColorQoraiPlaylistNewPlaylistDialogNameLabel] = {
      nala::kColorTextPrimary};
  mixer[kColorQoraiPlaylistNewPlaylistDialogItemsLabel] = {
      nala::kColorTextSecondary};
  mixer[kColorQoraiPlaylistTextInteractive] = {nala::kColorTextInteractive};
}

}  // namespace playlist
