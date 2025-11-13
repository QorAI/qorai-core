// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import Strings
import SwiftUI

/// A playback control which lets the user pick a playback speed, either by cycling through speeds
/// with taps or by long-pressing to see the list of options
struct PlaybackSpeedPicker: View {
  @Binding var playbackSpeed: PlayerModel.PlaybackSpeed

  private var label: some View {
    Label(
      Strings.Playlist.accessibilityPlaybackSpeed,
      qoraiSystemImage: playbackSpeed.qoraiSystemName
    )
    .transition(.opacity.animation(.linear(duration: 0.1)))
  }

  var body: some View {
    if #available(iOS 17.0, *) {
      Menu {
        Picker("", selection: $playbackSpeed) {
          ForEach(PlayerModel.PlaybackSpeed.supportedSpeeds) { speed in
            Text(verbatim: "\(speed.rate.formatted())×")
              .tag(speed)
          }
        }
      } label: {
        label
      } primaryAction: {
        playbackSpeed.cycle()
      }
    } else {
      Button {
        playbackSpeed.cycle()
      } label: {
        label
      }
    }
  }
}

/// A playback control which lets the user pick a repeat mode, either by cycling through each mode
/// with taps or by long-pressing to see the list of options
struct RepeatModePicker: View {
  @Binding var repeatMode: PlayerModel.RepeatMode

  private var label: some View {
    Group {
      switch repeatMode {
      case .none:
        Label(Strings.Playlist.accessibilityRepeatModeOff, qoraiSystemImage: "qora.loop.off")
      case .one:
        Label(Strings.Playlist.accessibilityRepeatModeOne, qoraiSystemImage: "qora.loop.1")
      case .all:
        Label(Strings.Playlist.accessibilityRepeatModeAll, qoraiSystemImage: "qora.loop.all")
      }
    }
    .transition(.opacity.animation(.linear(duration: 0.1)))
  }

  var body: some View {
    if #available(iOS 17.0, *) {
      Menu {
        Picker("", selection: $repeatMode) {
          Label(Strings.Playlist.repeatModeOptionNone, qoraiSystemImage: "qora.loop.off")
            .tag(PlayerModel.RepeatMode.none)
          Label(Strings.Playlist.repeatModeOptionOne, qoraiSystemImage: "qora.loop.1")
            .tag(PlayerModel.RepeatMode.one)
          Label(Strings.Playlist.repeatModeOptionAll, qoraiSystemImage: "qora.loop.all")
            .tag(PlayerModel.RepeatMode.all)
        }
      } label: {
        label
      } primaryAction: {
        repeatMode.cycle()
      }
    } else {
      Button {
        repeatMode.cycle()
      } label: {
        label
      }
    }
  }
}
