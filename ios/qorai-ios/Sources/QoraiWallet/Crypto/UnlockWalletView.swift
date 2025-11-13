// Copyright 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import DesignSystem
import LocalAuthentication
import Strings
import SwiftUI

struct UnlockWalletView: View {
  @ObservedObject var keyringStore: KeyringStore
  // Used to dismiss all of Wallet
  let dismissAction: () -> Void

  @State private var password: String = ""
  @FocusState private var isPasswordFieldFocused: Bool
  @State private var unlockError: UnlockError?
  @State private var attemptedBiometricsUnlock: Bool = false

  private enum UnlockError: LocalizedError {
    case incorrectPassword

    var errorDescription: String? {
      switch self {
      case .incorrectPassword:
        return Strings.Wallet.incorrectPasswordErrorMessage
      }
    }
  }

  private var isPasswordValid: Bool {
    !password.isEmpty
  }

  private func fillPasswordFromKeychain() {
    if let password = keyringStore.retrievePasswordFromKeychain() {
      self.password = password
      unlock()
    }
  }

  private func unlock() {
    // Conflict with the keyboard submit/dismissal that causes a bug
    // with SwiftUI animating the screen away...
    DispatchQueue.main.asyncAfter(deadline: .now() + 0.05) {
      keyringStore.unlock(password: password) { unlocked in
        if !unlocked {
          unlockError = .incorrectPassword
          UIImpactFeedbackGenerator(style: .medium).vibrate()
        }
      }
    }
  }

  var body: some View {
    ScrollView {
      VStack(spacing: 40) {
        VStack(spacing: 4) {
          Text(Strings.Wallet.unlockWallet)
            .font(.title)
            .fontWeight(.medium)
            .foregroundColor(Color(qoraiSystemName: .textPrimary))
          Text(Strings.Wallet.unlockWalletDescription)
            .font(.subheadline)
            .foregroundColor(Color(qoraiSystemName: .textSecondary))
        }
        .padding(.top, 44)

        VStack(spacing: 32) {
          SecureField(Strings.Wallet.passwordPlaceholder, text: $password, onCommit: unlock)
            .textContentType(.password)
            .modifier(
              WalletUnlockStyleModifier(isFocused: isPasswordFieldFocused, error: unlockError)
            )
            .focused($isPasswordFieldFocused)

          VStack(spacing: 16) {
            Button(action: unlock) {
              Text(Strings.Wallet.unlockWalletButtonTitle)
                .frame(maxWidth: .infinity)
            }
            .buttonStyle(QoraiFilledButtonStyle(size: .large))
            .disabled(!isPasswordValid)

            NavigationLink(
              destination: RestoreWalletView(
                keyringStore: keyringStore,
                dismissAction: dismissAction
              )
            ) {
              Text(Strings.Wallet.restoreWalletButtonTitle)
                .fontWeight(.semibold)
                .foregroundColor(Color(qoraiSystemName: .textInteractive))
                .padding(.vertical, 10)
                .padding(.horizontal, 20)
                .frame(maxWidth: .infinity)
            }
          }
        }

        if keyringStore.isKeychainPasswordStored, let icon = biometricsIcon {
          Button(action: fillPasswordFromKeychain) {
            icon
              .imageScale(.large)
              .font(.headline)
              .foregroundColor(Color(qoraiSystemName: .iconInteractive))
              .padding()
              .background(
                Circle()
                  .strokeBorder(Color(qoraiSystemName: .dividerInteractive), lineWidth: 1)
              )
          }
        }
      }
      .padding(.horizontal, 34)
    }
    .frame(maxWidth: .infinity, maxHeight: .infinity)
    .background(
      Image("wallet-background", bundle: .module)
        .resizable()
        .aspectRatio(contentMode: .fill)
        .edgesIgnoringSafeArea(.all)
    )
    .onChange(of: password) { _ in
      unlockError = nil
    }
    .onAppear {
      self.isPasswordFieldFocused = true

      DispatchQueue.main.asyncAfter(deadline: .now() + 0.5) { [self] in
        if !keyringStore.lockedManually && !attemptedBiometricsUnlock && keyringStore.isWalletLocked
          && UIApplication.shared.isProtectedDataAvailable
        {
          attemptedBiometricsUnlock = true
          fillPasswordFromKeychain()
        }
      }
    }
    .navigationTitle(Strings.Wallet.cryptoTitle)
    .navigationBarTitleDisplayMode(.inline)
    .transparentUnlessScrolledNavigationAppearance()
    .ignoresSafeArea(.keyboard, edges: .bottom)
  }

  private var biometricsIcon: Image? {
    let context = LAContext()
    if context.canEvaluatePolicy(.deviceOwnerAuthenticationWithBiometrics, error: nil) {
      switch context.biometryType {
      case .faceID:
        return Image(qoraiSystemName: "qora.face.id")
      case .touchID:
        return Image(qoraiSystemName: "qora.biometric.login")
      case .opticID:
        return Image(systemName: "opticid")
      case .none:
        return nil
      @unknown default:
        return nil
      }
    }
    return nil
  }
}

#if DEBUG
struct UnlockWalletView_Previews: PreviewProvider {
  static var previews: some View {
    NavigationView {
      UnlockWalletView(
        keyringStore: .previewStoreWithWalletCreated,
        dismissAction: {}
      )
    }
    .previewColorSchemes()
  }
}
#endif

private struct WalletUnlockStyleModifier<Failure: LocalizedError & Equatable>: ViewModifier {

  var isFocused: Bool
  var error: Failure?

  private var borderColor: Color {
    if error != nil {
      return Color.red
    } else if isFocused {
      return Color(qoraiSystemName: .iconInteractive)
    }
    return Color.clear
  }

  func body(content: Content) -> some View {
    VStack(spacing: 6) {
      content
        .padding(.horizontal, 16)
        .padding(.vertical, 10)
        .background(
          RoundedRectangle(cornerRadius: 10, style: .continuous)
            .strokeBorder(borderColor, lineWidth: 1)
            .background(
              RoundedRectangle(cornerRadius: 10, style: .continuous)
                .fill(Color(qoraiSystemName: .containerBackground))
            )
        )
      HStack(alignment: .firstTextBaseline, spacing: 4) {
        Image(qoraiSystemName: "qora.warning.triangle-outline")
        // maintain space when not showing an error, `hidden()` below
        Text(error?.localizedDescription ?? " ")
          .fixedSize(horizontal: false, vertical: true)
          // Dont animate the text change, just alpha
          .animation(nil, value: error?.localizedDescription)
      }
      .frame(maxWidth: .infinity, alignment: .leading)
      .transition(
        .asymmetric(
          insertion: .opacity.animation(.default),
          removal: .identity
        )
      )
      .font(.footnote)
      .foregroundColor(Color(.qoraiErrorLabel))
      .padding(.leading, 8)
      .hidden(isHidden: error == nil)
    }
  }
}
