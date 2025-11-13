// Copyright 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import QoraiShared
import QoraiStore
import QoraiUI
import GuardianConnect
import Preferences
import Shared
import Static
import SwiftUI
import UIKit
import os.log

public class QoraiVPNSettingsViewController: TableViewController {

  public var openURL: ((URL) -> Void)?
  let iapObserver: QoraiVPNInAppPurchaseObserver

  public init(iapObserver: QoraiVPNInAppPurchaseObserver) {
    self.iapObserver = iapObserver

    super.init(style: .insetGrouped)
  }

  @available(*, unavailable)
  required init(coder: NSCoder) { fatalError() }

  private var credentialSummary: SkusCredentialSummary?

  // Cell/section tags so we can update them dynamically.
  private let serverSectionId = "server"
  private let subscriptionStatusSectionId = "subscriptionStatus"
  private let locationCellId = "location"
  private let protocolCellId = "protocol"
  private let resetCellId = "reset"
  private let vpnStatusSectionCellId = "vpnStatus"
  private let vpnStatusProductTypeCellId = "vpnStatusProductType"
  private let vpnStatusExpiryDateCellId = "vpnStatusExpiryDate"
  private let vpnSmartProxySectionCellId = "vpnSmartProxy"
  private let vpnKillSwitchSectionCellId = "vpnKillSwitch"

  private var vpnConnectionStatusSwitch: SwitchAccessoryView?

  private var vpnReconfigurationPending = false {
    didSet {
      DispatchQueue.main.async {
        self.vpnConnectionStatusSwitch?.isEnabled = !self.vpnReconfigurationPending
      }
    }
  }

  /// View to show when the vpn config reset is pending.
  private var overlayView: UIView?

  private var isLoading: Bool = false {
    didSet {
      overlayView?.removeFromSuperview()

      if !isLoading { return }

      let overlay = UIView().then {
        $0.backgroundColor = UIColor.black.withAlphaComponent(0.5)
        let activityIndicator = UIActivityIndicatorView().then {
          $0.style = .large
          $0.color = .white
          $0.startAnimating()
          $0.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        }

        $0.addSubview(activityIndicator)
      }

      view.addSubview(overlay)
      overlay.frame = CGRect(size: tableView.contentSize)

      overlayView = overlay
    }
  }

  private var vpnProductStatusInfo: (subscriptionStatus: String, statusDetailColor: UIColor) {
    if Preferences.VPN.vpnReceiptStatus.value
      == QoraiVPN.ReceiptResponse.Status.retryPeriod.rawValue
    {
      return (Strings.VPN.vpnActionUpdatePaymentMethodSettingsText, .qoraiErrorLabel)
    }

    if QoraiVPN.vpnState == .expired {
      return (Strings.VPN.subscriptionStatusExpired, .qoraiErrorLabel)
    } else {
      return (QoraiVPN.subscriptionName, .qoraiLabel)
    }
  }

  @MainActor
  func fetchCredentialSummary() async -> SkusCredentialSummary? {
    self.isLoading = true
    defer { self.isLoading = false }

    if QoraiStoreSDK.shared.vpnSubscriptionStatus != nil {
      return nil
    }

    do {
      return try await QoraiSkusSDK.shared.credentialsSummary(for: .vpn)
    } catch {
      Logger.module.error("Error Fetching VPN Skus Credential Summary: \(error)")
    }

    return nil
  }

  private var linkReceiptRows: [Row] {
    var rows = [Row]()

    rows.append(
      Row(
        text: Strings.VPN.settingsLinkReceipt,
        selection: { [unowned self] in
          Task {
            try await QoraiVPNInAppPurchaseObserver.refreshReceipt()
          }
          openURL?(.qorai.qoraiVPNLinkReceiptProd)
        },
        cellClass: ButtonCell.self
      )
    )

    if QoraiVPN.isSandbox {
      rows += [
        Row(
          text: "[Staging] Link Receipt",
          selection: { [unowned self] in
            Task {
              try await QoraiVPNInAppPurchaseObserver.refreshReceipt()
            }
            openURL?(.qorai.qoraiVPNLinkReceiptStaging)
          },
          cellClass: ButtonCell.self
        ),
        Row(
          text: "[Dev] Link Receipt",
          selection: { [unowned self] in
            Task {
              try await QoraiVPNInAppPurchaseObserver.refreshReceipt()
            }
            openURL?(.qorai.qoraiVPNLinkReceiptDev)
          },
          cellClass: ButtonCell.self
        ),
      ]
    }

    rows.append(
      Row(
        text: Strings.VPN.settingsViewReceipt,
        selection: { [unowned self] in
          let controller = UIHostingController(rootView: StoreKitReceiptSimpleView())
          self.navigationController?.pushViewController(controller, animated: true)
        },
        cellClass: ButtonCell.self
      )
    )

    return rows
  }

  public override func viewDidLoad() {
    super.viewDidLoad()

    title = Strings.VPN.vpnName
    NotificationCenter.default.addObserver(
      self,
      selector: #selector(vpnConfigChanged(_:)),
      name: .NEVPNStatusDidChange,
      object: nil
    )

    let vpnEnabledToggleView = SwitchAccessoryView(
      initialValue: QoraiVPN.isConnected,
      valueChange: { vpnOn in
        if vpnOn {
          QoraiVPN.reconnect()
        } else {
          QoraiVPN.disconnect()
        }
      }
    )

    let vpnSmartProxyToggleView = QoraiVPNLinkSwitchView(
      isOn: { QoraiVPN.isSmartProxyRoutingEnabled },
      valueChange: { isSmartProxyEnabled in
        QoraiVPN.isSmartProxyRoutingEnabled = isSmartProxyEnabled
      },
      openURL: openURL
    )

    let vpnKillSwitchToggleView = QoraiVPNLinkSwitchView(
      isOn: { QoraiVPN.isKillSwitchEnabled },
      valueChange: { isKillSwitchEnabled in
        QoraiVPN.isKillSwitchEnabled = isKillSwitchEnabled
      },
      openURL: openURL
    )

    if Preferences.VPN.vpnReceiptStatus.value
      == QoraiVPN.ReceiptResponse.Status.retryPeriod.rawValue
    {
      vpnEnabledToggleView.onTintColor = .qoraiErrorLabel
    }

    self.vpnConnectionStatusSwitch = vpnEnabledToggleView

    let vpnStatusSection = Section(
      rows: [
        Row(
          text: Strings.VPN.settingsVPNEnabled,
          accessory: .view(vpnEnabledToggleView),
          uuid: vpnStatusSectionCellId
        ),
        Row(
          text: Strings.VPN.settingsVPNSmartProxyEnabled,
          detailText: String.localizedStringWithFormat(
            Strings.VPN.settingsVPNSmartProxyDescription,
            URL.qorai.qoraiVPNSmartProxySupport.absoluteString
          ),
          accessory: .view(vpnSmartProxyToggleView),
          cellClass: QoraiVPNLinkSwitchCell.self,
          context: [QoraiVPNLinkSwitchCell.textAccessoryKey: "qora.smart.proxy-routing"],
          uuid: vpnSmartProxySectionCellId
        ),
        Row(
          text: Strings.VPN.settingsVPNKillSwitchTitle,
          detailText: String.localizedStringWithFormat(
            Strings.VPN.settingsVPNKillSwitchDescription,
            URL.qorai.qoraiVPNKillSwitchSupport.absoluteString
          ),
          accessory: .view(vpnKillSwitchToggleView),
          cellClass: QoraiVPNLinkSwitchCell.self,
          uuid: vpnKillSwitchSectionCellId
        ),
      ],
      uuid: vpnStatusSectionCellId
    )

    let (subscriptionStatus, statusDetailColor) = vpnProductStatusInfo
    let expiration = QoraiVPN.vpnState == .expired ? "-" : expirationDate

    let subscriptionSection =
      Section(
        header: .title(Strings.VPN.settingsSubscriptionSection),
        rows: [
          Row(
            text: Strings.VPN.settingsSubscriptionStatus,
            detailText: subscriptionStatus,
            cellClass: ColoredDetailCell.self,
            context: [ColoredDetailCell.colorKey: statusDetailColor],
            uuid: vpnStatusProductTypeCellId
          ),
          Row(
            text: Strings.VPN.settingsSubscriptionExpiration,
            detailText: expiration,
            uuid: vpnStatusExpiryDateCellId
          ),
          Row(
            text: Strings.VPN.settingsManageSubscription,
            selection: {
              guard let url = URL.apple.manageSubscriptions else { return }
              if UIApplication.shared.canOpenURL(url) {
                // Opens Apple's 'manage subscription' screen.
                UIApplication.shared.open(url, options: [:])
              }
            },
            cellClass: ButtonCell.self
          ),
          Row(
            text: Strings.VPN.settingsRedeemOfferCode,
            selection: {
              self.isLoading = false
              // Open the redeem code sheet
              SKPaymentQueue.default().presentCodeRedemptionSheet()
            },
            cellClass: ButtonCell.self
          ),
        ] + linkReceiptRows,
        footer: .title(Strings.VPN.settingsLinkReceiptFooter),
        uuid: subscriptionStatusSectionId
      )

    let locationCity = QoraiVPN.serverLocationDetailed.city ?? "-"
    let locationCountry = QoraiVPN.serverLocationDetailed.country ?? hostname

    let userPreferredTunnelProtocol = GRDTransportProtocol.getUserPreferredTransportProtocol()
    let transportProtocol = GRDTransportProtocol.prettyTransportProtocolString(
      for: userPreferredTunnelProtocol
    )

    var smartProxyAvailable = false
    if let activatedRegion = QoraiVPN.activatedRegion {
      smartProxyAvailable =
        !activatedRegion.smartRoutingProxyState.isEmpty
        && (QoraiVPN.activatedRegion?.smartRoutingProxyState != kGRDRegionSmartRoutingProxyNone)
    }
    let rowContext =
      smartProxyAvailable
      ? [QoraiVPNServerLocationCell.textAccessoryKey: "qora.smart.proxy-routing"] : nil
    let serverSection = Section(
      header: .title(Strings.VPN.settingsServerSection),
      rows: [
        Row(
          text: locationCountry,
          detailText: locationCity,
          selection: { [unowned self] in
            self.selectServerTapped()
          },
          image: QoraiVPN.serverLocation.isoCode?.regionFlagImage
            ?? UIImage(qoraiSystemNamed: "qora.globe"),
          accessory: .disclosureIndicator,
          cellClass: QoraiVPNServerLocationCell.self,
          context: rowContext,
          uuid: locationCellId
        ),
        Row(
          text: Strings.VPN.settingsTransportProtocol,
          detailText: transportProtocol,
          selection: { [unowned self] in
            self.selectProtocolTapped()
          },
          accessory: .disclosureIndicator,
          uuid: protocolCellId
        ),
        Row(
          text: Strings.VPN.settingsResetConfiguration,
          selection: { [unowned self] in
            self.resetConfigurationTapped()
          },
          cellClass: ButtonCell.self,
          uuid: resetCellId
        ),
      ],
      uuid: serverSectionId
    )

    let techSupportSection = Section(
      header: .title(Strings.support.capitalized),
      rows: [
        Row(
          text: Strings.VPN.settingsContactSupport,
          selection: { [unowned self] in
            self.sendContactSupportEmail()
          },
          accessory: .disclosureIndicator
        ),
        Row(
          text: Strings.VPN.settingsFAQ,
          selection: { [unowned self] in
            self.openURL?(.qorai.qoraiVPNFaq)
          },
          cellClass: ButtonCell.self
        ),
      ]
    )

    dataSource.sections = [
      vpnStatusSection,
      subscriptionSection,
      serverSection,
      techSupportSection,
    ]

    Task { @MainActor in
      self.credentialSummary = await fetchCredentialSummary()
      self.updateSubscriptionStatus()
      self.updateSubscriptionExpiryDate()
    }
  }

  deinit {
    NotificationCenter.default.removeObserver(self)
  }

  private var hostname: String {
    QoraiVPN.hostname?.components(separatedBy: ".").first ?? "-"
  }

  private var expirationDate: String {
    let dateFormatter = DateFormatter().then {
      $0.locale = Locale.current
      $0.dateStyle = .short
    }

    if let order = credentialSummary?.order, let expiresAt = order.expiresAt {
      Preferences.VPN.expirationDate.value = expiresAt
      return dateFormatter.string(from: expiresAt)
    }

    guard let expirationDate = Preferences.VPN.expirationDate.value else {
      return ""
    }

    return dateFormatter.string(from: expirationDate)
  }

  private func updateServerInfo() {
    guard
      let locationIndexPath =
        dataSource
        .indexPath(rowUUID: locationCellId, sectionUUID: serverSectionId)
    else { return }

    guard
      let protocolIndexPath =
        dataSource
        .indexPath(rowUUID: protocolCellId, sectionUUID: serverSectionId)
    else { return }

    dataSource.sections[locationIndexPath.section].rows[locationIndexPath.row]
      .text = QoraiVPN.serverLocationDetailed.city ?? "-"
    dataSource.sections[locationIndexPath.section].rows[locationIndexPath.row]
      .detailText = QoraiVPN.serverLocationDetailed.country ?? hostname
    dataSource.sections[locationIndexPath.section].rows[locationIndexPath.row]
      .image =
      QoraiVPN.serverLocation.isoCode?.regionFlagImage ?? UIImage(qoraiSystemNamed: "qora.globe")

    dataSource.sections[protocolIndexPath.section].rows[protocolIndexPath.row]
      .detailText = GRDTransportProtocol.prettyTransportProtocolString(
        for: GRDTransportProtocol.getUserPreferredTransportProtocol()
      )
  }

  private func updateSubscriptionStatus() {
    if let credentialSummary = credentialSummary {
      Preferences.VPN.subscriptionProductId.value = credentialSummary.order.items.first?.sku

      guard
        let statusIndexPath =
          dataSource
          .indexPath(rowUUID: vpnStatusProductTypeCellId, sectionUUID: subscriptionStatusSectionId)
      else { return }

      let (subscriptionStatus, statusDetailColor) = vpnProductStatusInfo
      dataSource.sections[statusIndexPath.section].rows[statusIndexPath.row]
        .detailText = subscriptionStatus
      dataSource.sections[statusIndexPath.section].rows[statusIndexPath.row]
        .context = [ColoredDetailCell.colorKey: statusDetailColor]
    }
  }

  private func updateSubscriptionExpiryDate() {
    guard
      let expiryDateIndexPath =
        dataSource
        .indexPath(rowUUID: vpnStatusExpiryDateCellId, sectionUUID: subscriptionStatusSectionId)
    else { return }

    let expiration = QoraiVPN.vpnState == .expired ? "-" : expirationDate
    dataSource.sections[expiryDateIndexPath.section].rows[expiryDateIndexPath.row]
      .text = Strings.VPN.settingsSubscriptionExpiration
    dataSource.sections[expiryDateIndexPath.section].rows[expiryDateIndexPath.row]
      .detailText = expiration
  }

  private func sendContactSupportEmail() {
    navigationController?.pushViewController(QoraiVPNContactFormViewController(), animated: true)
  }

  private func resetConfigurationTapped() {
    let alert = UIAlertController(
      title: Strings.VPN.vpnResetAlertTitle,
      message: Strings.VPN.vpnResetAlertBody,
      preferredStyle: .actionSheet
    )

    let cancel = UIAlertAction(title: Strings.cancelButtonTitle, style: .cancel)
    let reset = UIAlertAction(
      title: Strings.VPN.vpnResetButton,
      style: .destructive,
      handler: { [weak self] _ in
        guard let self = self else { return }
        self.vpnReconfigurationPending = true
        self.isLoading = true
        Logger.module.debug("Reconfiguring the vpn")

        QoraiVPN.reconfigureVPN { success in
          Logger.module.debug("Reconfiguration suceedeed: \(success)")
          // Small delay before unlocking UI because enabling vpn
          // takes a moment after we call to connect to the vpn.
          DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
            self.isLoading = false
            self.vpnReconfigurationPending = false
            self.updateServerInfo()
            self.showVPNResetAlert(success: success)
          }
        }
      }
    )

    alert.addAction(cancel)
    alert.addAction(reset)

    if UIDevice.current.userInterfaceIdiom == .pad {
      alert.popoverPresentationController?.permittedArrowDirections = [.down, .up]

      if let resetCellIndexPath =
        dataSource
        .indexPath(rowUUID: resetCellId, sectionUUID: serverSectionId)
      {
        let cell = tableView.cellForRow(at: resetCellIndexPath)

        alert.popoverPresentationController?.sourceView = cell
        alert.popoverPresentationController?.sourceRect = cell?.bounds ?? .zero
      } else {
        alert.popoverPresentationController?.sourceView = self.view
        alert.popoverPresentationController?.sourceRect = self.view.bounds
      }
    }

    present(alert, animated: true)
  }

  private func selectServerTapped() {
    if QoraiVPN.allRegions.isEmpty {
      let alert = UIAlertController(
        title: Strings.VPN.vpnConfigGenericErrorTitle,
        message: Strings.VPN.settingsFailedToFetchServerList,
        preferredStyle: .alert
      )
      alert.addAction(.init(title: Strings.OKString, style: .default))
      // Failed to fetch regions at app init or first vpn configuration.
      // Let's try again here.
      QoraiVPN.populateRegionDataIfNecessary()
      present(alert, animated: true)
      return
    }

    let vpnRegionListView = QoraiVPNRegionListView { [weak self] _ in
      self?.updateServerInfo()

      let controller = PopupViewController(
        rootView: QoraiVPNRegionConfirmationView(
          country: QoraiVPN.serverLocationDetailed.country,
          city: QoraiVPN.serverLocationDetailed.city,
          countryISOCode: QoraiVPN.serverLocation.isoCode
        ),
        isDismissable: true
      )
      self?.present(controller, animated: true)
      Timer.scheduledTimer(withTimeInterval: 2, repeats: false) { [weak controller] _ in
        controller?.dismiss(animated: true)
      }
    }
    let vc = UIHostingController(rootView: vpnRegionListView)
    vc.title = Strings.VPN.vpnRegionListServerScreenTitle
    navigationController?.pushViewController(vc, animated: true)
  }

  private func selectProtocolTapped() {
    let vc = QoraiVPNProtocolPickerViewController()
    navigationController?.pushViewController(vc, animated: true)
  }

  private func showVPNResetAlert(success: Bool) {
    let alert = UIAlertController(
      title: success ? Strings.VPN.resetVPNSuccessTitle : Strings.VPN.resetVPNErrorTitle,
      message: success ? Strings.VPN.resetVPNSuccessBody : Strings.VPN.resetVPNErrorBody,
      preferredStyle: .alert
    )

    if success {
      let okAction = UIAlertAction(title: Strings.OKString, style: .default)
      alert.addAction(okAction)
    } else {
      alert.addAction(UIAlertAction(title: Strings.close, style: .cancel, handler: nil))
      alert.addAction(
        UIAlertAction(
          title: Strings.VPN.resetVPNErrorButtonActionTitle,
          style: .default,
          handler: { [weak self] _ in
            self?.resetConfigurationTapped()
          }
        )
      )
    }

    present(alert, animated: true)
  }

  @objc func vpnConfigChanged(_ notification: NSNotification) {
    guard let vpnConnection = notification.object as? NEVPNConnection else {
      return
    }

    switch vpnConnection.status {
    case .connecting, .disconnecting, .reasserting:
      isLoading = true
    case .invalid:
      vpnConnectionStatusSwitch?.isOn = false
    case .connected, .disconnected:
      vpnConnectionStatusSwitch?.isOn = QoraiVPN.isConnected
    @unknown default:
      assertionFailure()
      break
    }

    isLoading = false
  }
}

// MARK: - IAPObserverDelegate

extension QoraiVPNSettingsViewController: QoraiVPNInAppPurchaseObserverDelegate {
  public func purchasedOrRestoredProduct(validateReceipt: Bool) {
    DispatchQueue.main.async {
      self.isLoading = false
    }

    if validateReceipt {
      Task {
        _ = try await QoraiVPN.validateReceiptData()
      }
    }
  }

  public func purchaseFailed(error: QoraiVPNInAppPurchaseObserver.PurchaseError) {
    // Handle Offer Code error
    guard isLoading else {
      return
    }

    handleOfferCodeError(error: error)
  }

  public func handlePromotedInAppPurchase() {
    // No-op
  }

  private func handleOfferCodeError(error: QoraiVPNInAppPurchaseObserver.PurchaseError) {
    DispatchQueue.main.async {
      self.isLoading = false

      let message = Strings.VPN.vpnErrorOfferCodeFailedBody

      let alert = UIAlertController(
        title: Strings.VPN.vpnErrorPurchaseFailedTitle,
        message: message,
        preferredStyle: .alert
      )
      let ok = UIAlertAction(title: Strings.OKString, style: .default, handler: nil)
      alert.addAction(ok)
      self.present(alert, animated: true)
    }
  }
}
