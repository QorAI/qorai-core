// Copyright 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiCore
import QoraiUI
import Preferences
import SwiftUI

extension QoraiCoreSwitchKey {
  fileprivate var displayString: String {
    switch self {
    case .vModule:
      return "Log Verbosity"
    case .componentUpdater:
      return "Component Updater"
    case .syncURL:
      return "Sync URL"
    case .variationsPR:
      return "Variations PR"
    case .variationsURL:
      return "Variations URL"
    case .p3aDoNotRandomizeUploadInterval:
      return "Don't Randomize Upload Interval"
    case .p3aIgnoreServerErrors:
      return "Ignore Server Errors"
    case .p3aUploadIntervalSeconds:
      return "Upload Interval"
    case .p3aTypicalRotationIntervalSeconds:
      return "Typical Rotation Interval"
    case .p3aExpressRotationIntervalSeconds:
      return "Express Rotation Interval"
    case .p3aJsonUploadServerURL:
      return "Json Upload Server URL"
    case .enableFeatures:
      return "Enable Features"
    case .p3aWalletCountTestNetworks:
      return "Qorai Wallet Count Test Networks"
    case .useDevGoUpdater:
      return "Use staging CRX components"
    case .servicesEnvironment:
      return "Qorai Services Environment"
    default:
      return ""
    }
  }
  /// Whether or not the key is passed in without a value
  public var isValueless: Bool {
    switch self {
    case .p3aDoNotRandomizeUploadInterval,
      .p3aIgnoreServerErrors,
      .p3aWalletCountTestNetworks,
      .useDevGoUpdater:
      return true
    default:
      return false
    }
  }

  static let enableFeatures: Self = .init(rawValue: "enable-features")
  static let p3aWalletCountTestNetworks: Self = .init(
    rawValue: QoraiWallet.P3aCountTestNetworksSwitch
  )
}

private enum QoraiServicesEnvironment: String, CaseIterable {
  case development = "dev"
  case staging
  case production = "prod"
}

private struct BasicStringInputView: View {
  @ObservedObject private var activeSwitches = Preferences.QoraiCore.activeSwitches
  @ObservedObject private var switchValues = Preferences.QoraiCore.switchValues
  @Environment(\.dismiss) private var dismiss

  var coreSwitch: QoraiCoreSwitchKey
  var hint: String?

  @State private var text: String = ""

  var body: some View {
    Form {
      Section {
        TextField(coreSwitch.displayString, text: $text)
          .disableAutocorrection(true)
          .autocapitalization(.none)
          .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      } footer: {
        if let hint = hint {
          Text(hint)
        }
      }
    }
    .listStyle(.insetGrouped)
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationTitle(coreSwitch.displayString)
    .onAppear {
      // SwiftUI bug, has to wait a bit
      DispatchQueue.main.asyncAfter(deadline: .now() + 0.1) {
        text = switchValues.value[coreSwitch.rawValue, default: ""]
      }
    }
    .toolbar {
      ToolbarItemGroup(placement: .confirmationAction) {
        Button {
          if text.isEmpty {
            switchValues.value[coreSwitch.rawValue] = nil
            activeSwitches.value.removeAll(where: { $0 == coreSwitch.rawValue })
          } else {
            switchValues.value[coreSwitch.rawValue] = text
            if !activeSwitches.value.contains(coreSwitch.rawValue) {
              activeSwitches.value.append(coreSwitch.rawValue)
            }
          }
          dismiss()
        } label: {
          Text("Save")
            .foregroundColor(Color(.qoraiBlurpleTint))
        }
      }
    }
  }
}

private struct BasicPickerInputView: View {
  @ObservedObject private var activeSwitches = Preferences.QoraiCore.activeSwitches
  @ObservedObject private var switchValues = Preferences.QoraiCore.switchValues
  @Environment(\.dismiss) private var dismiss

  var coreSwitch: QoraiCoreSwitchKey
  var options: [String]

  @State private var selectedItem: String = ""

  var body: some View {
    Form {
      Picker("", selection: $selectedItem) {
        Text("Default")
          .foregroundColor(Color(.secondaryQoraiLabel))
          .tag("")
        ForEach(options, id: \.self) { option in
          Text(option.capitalized).tag(option)
        }
      }
      .pickerStyle(.inline)
    }
    .listStyle(.insetGrouped)
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationTitle(coreSwitch.displayString)
    .onAppear {
      // SwiftUI bug, has to wait a bit
      DispatchQueue.main.asyncAfter(deadline: .now() + 0.1) {
        selectedItem = switchValues.value[coreSwitch.rawValue, default: ""]
      }
    }
    .toolbar {
      ToolbarItemGroup(placement: .confirmationAction) {
        Button {
          if selectedItem.isEmpty {
            switchValues.value[coreSwitch.rawValue] = nil
            activeSwitches.value.removeAll(where: { $0 == coreSwitch.rawValue })
          } else {
            switchValues.value[coreSwitch.rawValue] = selectedItem
            if !activeSwitches.value.contains(coreSwitch.rawValue) {
              activeSwitches.value.append(coreSwitch.rawValue)
            }
          }
          dismiss()
        } label: {
          Text("Save")
            .foregroundColor(Color(.qoraiBlurpleTint))
        }
      }
    }
  }
}

private struct CustomSwitchInputView: View {
  @ObservedObject private var customSwitches = Preferences.QoraiCore.customSwitches
  @ObservedObject private var switchValues = Preferences.QoraiCore.switchValues
  @Environment(\.dismiss) private var dismiss

  @State var key: String
  @State private var value: String = ""

  init(key: String) {
    _key = State(wrappedValue: key)
  }

  var body: some View {
    Form {
      Section {
        TextField("Key", text: $key)
          .disableAutocorrection(true)
          .autocapitalization(.none)
          .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      } footer: {
        Text("Enter the key. Format: --")
          + Text("**Key**")
          .foregroundColor(Color(qoraiSystemName: .textInteractive))
          + Text("=Value")
      }

      Section {
        TextField("Value", text: $value)
          .disableAutocorrection(true)
          .autocapitalization(.none)
          .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      } footer: {
        Text("Enter the value. Format: --Key=")
          + Text("**Value**")
          .foregroundColor(Color(qoraiSystemName: .textInteractive))
      }
    }
    .listStyle(.insetGrouped)
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationTitle("Custom Switch")
    .onAppear {
      // SwiftUI bug, has to wait a bit
      DispatchQueue.main.asyncAfter(deadline: .now() + 0.1) {
        value = switchValues.value[key, default: ""]
      }
    }
    .toolbar {
      ToolbarItemGroup(placement: .confirmationAction) {
        Button {
          switchValues.value[key] = value
          if !customSwitches.value.contains(key) {
            customSwitches.value.append(key)
          }
          dismiss()
        } label: {
          Text("Save")
            .foregroundColor(
              !key.isEmpty ? Color(.qoraiBlurpleTint) : Color(qoraiSystemName: .buttonDisabled)
            )
        }
        .disabled(key.isEmpty)
      }
    }
  }
}

struct QoraiCoreDebugSwitchesView: View {
  @ObservedObject private var activeSwitches = Preferences.QoraiCore.activeSwitches
  @ObservedObject private var switchValues = Preferences.QoraiCore.switchValues

  private struct SwitchContainer: View {
    @ObservedObject private var activeSwitches = Preferences.QoraiCore.activeSwitches
    @ObservedObject private var switchValues = Preferences.QoraiCore.switchValues

    var coreSwitch: QoraiCoreSwitchKey

    init(_ coreSwitch: QoraiCoreSwitchKey) {
      self.coreSwitch = coreSwitch
    }

    private var binding: Binding<Bool> {
      .init(
        get: {
          activeSwitches.value.contains(coreSwitch.rawValue)
            && (coreSwitch.isValueless
              || !switchValues.value[coreSwitch.rawValue, default: ""].isEmpty)
        },
        set: { isOn in
          if !coreSwitch.isValueless && switchValues.value[coreSwitch.rawValue, default: ""].isEmpty
          {
            return
          }
          var switches = Set(activeSwitches.value)
          if isOn {
            switches.insert(coreSwitch.rawValue)
          } else {
            switches.remove(coreSwitch.rawValue)
          }
          activeSwitches.value = Array(switches)
        }
      )
    }

    var body: some View {
      HStack(spacing: 16) {
        Toggle(coreSwitch.displayString, isOn: binding)
          .toggleStyle(SwitchToggleStyle(tint: Color(.qoraiBlurpleTint)))
          .labelsHidden()
        VStack(alignment: .leading) {
          HStack {
            Text(coreSwitch.displayString)
              .font(.headline)
          }
          VStack(alignment: .leading, spacing: 4) {
            Text(coreSwitch.rawValue)
              .font(.footnote)
              .foregroundColor(Color(.secondaryQoraiLabel))
            if let value = switchValues.value[coreSwitch.rawValue], !value.isEmpty {
              Text("\(Image(systemName: "equal.square.fill")) \(value)")
                .font(.caption)
                .foregroundColor(
                  binding.wrappedValue ? Color(.qoraiBlurpleTint) : Color(.secondaryQoraiLabel)
                )
                .lineLimit(1)
            }
          }
        }
      }
      .padding(.vertical, 2)
    }
  }

  var body: some View {
    Form {
      Section {
        Text("Switches only affect fresh launches")
          .frame(maxWidth: .infinity)
          .font(.footnote)
          .foregroundColor(Color(.qoraiLabel))
          .listRowBackground(Color(.qoraiGroupedBackground))
          .listRowInsets(.zero)
      }
      Section {
        Group {
          NavigationLink {
            BasicStringInputView(coreSwitch: .syncURL)
              .keyboardType(.URL)
          } label: {
            SwitchContainer(.syncURL)
          }
          NavigationLink {
            BasicStringInputView(coreSwitch: .variationsPR)
              .keyboardType(.numberPad)
          } label: {
            SwitchContainer(.variationsPR)
          }
          NavigationLink {
            BasicStringInputView(coreSwitch: .variationsURL)
              .keyboardType(.URL)
          } label: {
            SwitchContainer(.variationsURL)
          }
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .componentUpdater,
              hint: "Should match the format: url-source={url}"
            )
          } label: {
            SwitchContainer(.componentUpdater)
          }
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .vModule,
              hint:
                "Should match the format:\n\n{folder-expression}={level}\n\nDefaults to */qorai/*=5"
            )
          } label: {
            SwitchContainer(.vModule)
          }
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .enableFeatures,
              hint:
                "Should match the format:\n\n{feature_name}\n\nMultiple features can be enabled via comma separation"
            )
          } label: {
            SwitchContainer(.enableFeatures)
          }
          SwitchContainer(.useDevGoUpdater)

          NavigationLink {
            BasicPickerInputView(
              coreSwitch: .servicesEnvironment,
              options: QoraiServicesEnvironment.allCases.map({ $0.rawValue })
            )
          } label: {
            SwitchContainer(.servicesEnvironment)
          }
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }
      Section {
        Group {
          SwitchContainer(.p3aDoNotRandomizeUploadInterval)
          SwitchContainer(.p3aIgnoreServerErrors)
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .p3aUploadIntervalSeconds,
              hint: "Overrides the number of seconds to upload P3A metrics"
            )
          } label: {
            SwitchContainer(.p3aUploadIntervalSeconds)
          }
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .p3aJsonUploadServerURL,
              hint: "Overrides the P3A cloud backend URL."
            )
          } label: {
            SwitchContainer(.p3aJsonUploadServerURL)
          }
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .p3aTypicalRotationIntervalSeconds,
              hint:
                "Interval in seconds between restarting the uploading process for all gathered values"
            )
          } label: {
            SwitchContainer(.p3aTypicalRotationIntervalSeconds)
          }
          NavigationLink {
            BasicStringInputView(
              coreSwitch: .p3aExpressRotationIntervalSeconds,
              hint:
                "Interval in seconds between restarting the uploading process for all gathered values"
            )
          } label: {
            SwitchContainer(.p3aExpressRotationIntervalSeconds)
          }
          SwitchContainer(.p3aWalletCountTestNetworks)
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      } header: {
        Text("P3A")
      }

      if !Preferences.QoraiCore.customSwitches.value.isEmpty {
        Section {
          Group {
            ForEach(Preferences.QoraiCore.customSwitches.value, id: \.self) { switchKey in
              NavigationLink {
                CustomSwitchInputView(key: switchKey)
              } label: {
                VStack(alignment: .leading) {
                  Text(String(switchKey.separatedBy("-").map({ $0.capitalized }).joined(by: " ")))
                    .font(.headline)

                  if let value = Preferences.QoraiCore.switchValues.value[switchKey], !value.isEmpty
                  {
                    Text("--\(switchKey)=\(value)")
                      .font(.caption)
                      .foregroundColor(
                        Color(.secondaryQoraiLabel)
                      )
                      .lineLimit(1)
                  }
                }
              }
            }
            .onDelete {
              let keys = $0.map { Preferences.QoraiCore.customSwitches.value[$0] }

              withAnimation(.default) {
                for key in keys {
                  Preferences.QoraiCore.switchValues.value[key] = nil
                  Preferences.QoraiCore.customSwitches.value.removeAll(where: { $0 == key })
                }
              }
            }
          }
          .listRowBackground(Color(.secondaryQoraiGroupedBackground))
        } header: {
          Text("Custom Switches")
        }
      }

      Section {
        NavigationLink {
          CustomSwitchInputView(key: "")
        } label: {
          Text("Add Custom Switch")
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }

      Section {
        Button("Disable All") {
          withAnimation {
            activeSwitches.value = []
          }
        }
        .listRowBackground(Color(.secondaryQoraiGroupedBackground))
      }
    }
    .listStyle(.insetGrouped)
    .listBackgroundColor(Color(UIColor.qoraiGroupedBackground))
    .navigationBarTitle("QoraiCore Switches")
  }
}

#if DEBUG
struct QoraiCoreDebugSwitchesView_Previews: PreviewProvider {
  static var previews: some View {
    NavigationView {
      QoraiCoreDebugSwitchesView()
        .navigationBarTitleDisplayMode(.inline)
    }
  }
}
#endif
