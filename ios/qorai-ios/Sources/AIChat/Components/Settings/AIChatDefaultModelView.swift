// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiStore
import QoraiUI
import Preferences
import SwiftUI

struct AIChatDefaultModelView: View {

  @Environment(\.openURL)
  private var openURL

  @Environment(\.dismiss)
  private var dismiss

  @State
  private var isPresentingPaywallPremium: Bool = false

  @ObservedObject
  var aiModel: AIChatViewModel

  var regularModels: [AiChat.Model] {
    aiModel.models.filter({
      $0.options.tag == .qoraModelOptions
    })
  }

  var customModels: [AiChat.Model] {
    aiModel.models.filter({
      $0.options.tag == .customModelOptions
    })
  }

  var body: some View {
    List {
      Section {
        ForEach(regularModels, id: \.key) { model in
          viewForModel(model)
        }
      } header: {
        Text(Strings.AIChat.defaultModelChatSectionTitle.uppercased())
      }

      if !customModels.isEmpty {
        Section {
          ForEach(customModels, id: \.key) { model in
            viewForModel(model)
          }
        } header: {
          Text(Strings.AIChat.customModelChatSectionTitle.uppercased())
        }
      }
    }
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .listStyle(.insetGrouped)
    .navigationTitle(Strings.AIChat.defaultModelViewTitle)
    .sheet(isPresented: $isPresentingPaywallPremium) {
      AIChatPaywallView(
        premiumUpgrageSuccessful: { _ in
          Task { @MainActor in
            await aiModel.refreshPremiumStatus()
          }
        },
        refreshCredentials: {
          openURL(.qorai.qoraiQoraRefreshCredentials)
          dismiss()
        },
        openDirectCheckout: {
          openURL(.qorai.qoraiQoraCheckoutURL)
          dismiss()
        }
      )
    }
  }

  @ViewBuilder
  private func viewForModel(_ model: AiChat.Model) -> some View {
    Button(
      action: {
        if model.options.tag == .qoraModelOptions {
          if model.options.qoraModelOptions?.access == .premium, aiModel.shouldShowPremiumPrompt {
            isPresentingPaywallPremium = true
          } else {
            aiModel.defaultAIModelKey = model.key
            dismiss()
          }
        } else {
          aiModel.defaultAIModelKey = model.key
          dismiss()
        }
      },
      label: {
        HStack(spacing: 0.0) {
          VStack(alignment: .leading) {
            Text(model.displayName)
              .foregroundStyle(Color(qoraiSystemName: .textPrimary))

            Text(model.purposeDescription)
              .font(.footnote)
              .foregroundStyle(Color(qoraiSystemName: .textSecondary))
          }
          .frame(maxWidth: .infinity, alignment: .leading)

          // If the model is selected show check
          if model.key == aiModel.defaultAIModelKey {
            Image(qoraiSystemName: "qora.check.normal")
              .foregroundStyle(Color(qoraiSystemName: .textInteractive))
              .padding(.horizontal, 4.0)
          } else {
            if model.options.tag == .qoraModelOptions {
              if model.options.qoraModelOptions?.access == .premium
                && aiModel.premiumStatus != .active
                && aiModel.premiumStatus != .activeDisconnected
              {
                Text(Strings.AIChat.premiumModelStatusTitle.uppercased())
                  .font(.caption2)
                  .foregroundStyle(Color(qoraiSystemName: .blue50))
                  .padding(.horizontal, 4.0)
                  .padding(.vertical, 2.0)
                  .overlay(
                    RoundedRectangle(cornerRadius: 4.0, style: .continuous)
                      .strokeBorder(Color(qoraiSystemName: .blue50), lineWidth: 1.0)
                  )
              }
            }
          }
        }
        .contentShape(Rectangle())
      }
    )
    .buttonStyle(.plain)
    .listRowBackground(Color(.secondaryQoraiGroupedBackground))
  }
}
