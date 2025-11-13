// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { getLocale } from '$web-common/locale'

export type Message =
  | 'qoraiDefaultPlaylistName'
  | 'qoraiPlaylistContextMenuEdit'
  | 'qoraiPlaylistContextMenuShare'
  | 'qoraiPlaylistContextMenuKeepForOfflinePlaying'
  | 'qoraiPlaylistContextMenuRemovePlayedContents'
  | 'qoraiPlaylistContextMenuMove'
  | 'qoraiPlaylistContextMenuRemoveOfflineData'
  | 'qoraiPlaylistContextMenuRemoveFromPlaylist'
  | 'qoraiPlaylistContextMenuRenamePlaylist'
  | 'qoraiPlaylistContextMenuDeletePlaylist'
  | 'qoraiPlaylistContextMenuViewOriginalPage'
  | 'qoraiPlaylistEmptyFolderMessage'
  | 'qoraiPlaylistTooltipCreatePlaylistFolder'
  | 'qoraiPlaylistTooltipOpenPlaylistSettings'
  | 'qoraiPlaylistTooltipClosePanel'
  | 'qoraiPlaylistTooltipPlay'
  | 'qoraiPlaylistTooltipPause'
  | 'qoraiPlaylistTooltipNext'
  | 'qoraiPlaylistTooltipPrevious'
  | 'qoraiPlaylistTooltipToggleMuted'
  | 'qoraiPlaylistTooltipShuffle'
  | 'qoraiPlaylistTooltipRewind'
  | 'qoraiPlaylistTooltipForward'
  | 'qoraiPlaylistTooltipClose'
  | 'qoraiPlaylistTooltipLoopOff'
  | 'qoraiPlaylistTooltipLoopOne'
  | 'qoraiPlaylistTooltipLoopAll'
  | 'qoraiPlaylistFailedToPlayTitle'
  | 'qoraiPlaylistFailedToPlayDescription'
  | 'qoraiPlaylistFailedToPlayRecover'
  | 'qoraiPlaylistAlertDismiss'
  | 'qoraiPlaylistAddMediaFromPage'

export function getLocalizedString(message: Message) {
  return getLocale(message)
}
