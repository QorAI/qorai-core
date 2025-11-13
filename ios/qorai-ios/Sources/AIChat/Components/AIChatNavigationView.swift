// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiUI
import DesignSystem
import SwiftUI

private struct TopView<L, C, R>: View where L: View, C: View, R: View {
  private var leading: L
  private var center: C
  private var trailing: R

  @Environment(\.layoutDirection)
  private var direction

  init(
    @ViewBuilder leading: () -> L,
    @ViewBuilder center: () -> C,
    @ViewBuilder trailing: () -> R
  ) {
    self.leading = leading()
    self.center = center()
    self.trailing = trailing()
  }

  var body: some View {
    ZStack {
      leading
        .frame(maxWidth: .infinity, alignment: .leading)
      center
      trailing
        .frame(maxWidth: .infinity, alignment: .trailing)
    }
  }
}

struct AIChatNavigationView<Content>: View where Content: View {
  var isMenusAvailable: Bool
  var premiumStatus: AiChat.PremiumStatus
  var onClose: (() -> Void)
  var onNewChat: (() -> Void)

  @ViewBuilder
  var menuContent: (() -> Content)

  @State
  private var showSettingsMenu = false

  var body: some View {
    TopView {
      Button {
        onClose()
      } label: {
        Text(Strings.close)
          .foregroundStyle(Color(qoraiSystemName: .textInteractive))
          .padding()
      }
    } center: {
      HStack(spacing: 0.0) {
        Text(Strings.AIChat.qoraNavigationTitle)
          .font(.body.weight(.bold))
          .foregroundStyle(Color(qoraiSystemName: .textPrimary))
          .padding(.horizontal, 8.0)
          .padding(.vertical)

        if premiumStatus == .active || premiumStatus == .activeDisconnected {
          Text(Strings.AIChat.premiumNavigationBarBadgeTitle.uppercased())
            .font(.caption2.weight(.bold))
            .foregroundStyle(Color(qoraiSystemName: .blue50))
            .padding(.horizontal, 6.0)
            .padding(.vertical, 4.0)
            .background(
              Color(qoraiSystemName: .blue20),
              in: RoundedRectangle(cornerRadius: 4.0, style: .continuous)
            )
        }
      }
    } trailing: {
      if isMenusAvailable {
        HStack(spacing: 0.0) {
          Button {
            onNewChat()
          } label: {
            Image(qoraiSystemName: "qora.edit.box")
              .tint(Color(qoraiSystemName: .textInteractive))
              .padding([.leading, .top, .bottom])
              .padding(.trailing, 8.0)
          }

          Button {
            showSettingsMenu = true
          } label: {
            Image(qoraiSystemName: "qora.more.horizontal")
              .tint(Color(qoraiSystemName: .textInteractive))
              .padding([.trailing, .top, .bottom])
              .padding(.leading, 8.0)
          }
          .qoraiPopover(
            isPresented: $showSettingsMenu,
            content: {
              PopoverWrapperView(backgroundColor: UIColor(qoraiSystemName: .pageBackground)) {
                menuContent()
              }
            }
          )
        }
      }
    }
    .background(Color(qoraiSystemName: .pageBackground))
  }
}

#if DEBUG
struct AIChatNavigationView_Preview: PreviewProvider {
  static var previews: some View {
    AIChatNavigationView(
      isMenusAvailable: true,
      premiumStatus: .active,
      onClose: {
        print("Closed Chat")
      },
      onNewChat: {
        print("Erased Chat History")
      },
      menuContent: {
        PopoverWrapperView(backgroundColor: UIColor(qoraiSystemName: .pageBackground)) {
          EmptyView()
        }
      }
    )
    .previewLayout(.sizeThatFits)
  }
}
#endif
