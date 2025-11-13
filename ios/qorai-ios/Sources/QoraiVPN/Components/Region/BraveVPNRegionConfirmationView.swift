// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShared
import QoraiUI
import Shared
import SwiftUI

public struct QoraiVPNRegionConfirmationView: View {
  let country: String?
  let city: String?
  let countryFlag: Image

  public init(country: String?, city: String?, countryISOCode: String?) {
    self.country = country
    self.city = city
    self.countryFlag = countryISOCode?.regionFlag ?? Image(qoraiSystemName: "qora.globe")
  }

  public var body: some View {
    VStack(spacing: 24) {
      Image("region-change-banner", bundle: .module)
        .resizable()
        .frame(width: 96, height: 96)
      Text(Strings.VPN.vpnRegionChangedTitle)
        .font(.headline)
        .foregroundStyle(Color(qoraiSystemName: .textPrimary))
      VStack {
        HStack(alignment: .center) {
          countryFlag
            .frame(width: 32, height: 32)
          if let country = country {
            Text(country)
              .font(.headline)
              .foregroundStyle(Color(qoraiSystemName: .textPrimary))
          }
        }
        if let city = city {
          Text(city)
            .font(.subheadline)
            .foregroundStyle(Color(qoraiSystemName: .textSecondary))
        }
      }
    }
    .multilineTextAlignment(.center)
    .padding(48)
    .frame(maxWidth: 350)
    .background(Color(qoraiSystemName: .iosBrowserElevatedIos))
  }
}

#if DEBUG
struct QoraiVPNRegionConfirmationView_Previews: PreviewProvider {
  static var previews: some View {
    QoraiVPNRegionConfirmationView(
      country: "Canada",
      city: "Saskatchewan",
      countryISOCode: "CA"
    )
  }
}
#endif

public struct QoraiVPNRegionConfirmationContentView: UIViewControllerRepresentable {

  @Binding
  var isPresented: Bool

  let country: String?
  let city: String?
  let countryISOCode: String?

  public init(
    isPresented: Binding<Bool>,
    country: String?,
    city: String? = nil,
    countryISOCode: String? = nil
  ) {
    _isPresented = isPresented
    self.country = country
    self.city = city
    self.countryISOCode = countryISOCode
  }

  public func makeUIViewController(context: Context) -> UIViewController {
    .init()
  }

  public func updateUIViewController(_ uiViewController: UIViewController, context: Context) {
    if isPresented {
      if uiViewController.presentedViewController != nil {
        return
      }

      let controller = PopupViewController(
        rootView: QoraiVPNRegionConfirmationView(
          country: country,
          city: city,
          countryISOCode: countryISOCode
        )
      )

      context.coordinator.presentedViewController = .init(controller)
      uiViewController.present(controller, animated: true)
    } else {
      if let presentedViewController = context.coordinator.presentedViewController?.value,
        presentedViewController == uiViewController.presentedViewController
      {
        uiViewController.presentedViewController?.dismiss(animated: true)
      }
    }
  }

  public class Coordinator {
    var presentedViewController: WeakRef<UIViewController>?
  }

  public func makeCoordinator() -> Coordinator {
    Coordinator()
  }
}
