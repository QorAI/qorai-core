// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_PRIVATE_NEW_TAB_PAGE_QORAI_PRIVATE_NEW_TAB_PAGE_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_PRIVATE_NEW_TAB_PAGE_QORAI_PRIVATE_NEW_TAB_PAGE_HANDLER_H_

#include <stdint.h>

#include <memory>
#include <string>

#include "base/scoped_observation.h"
#include "base/timer/timer.h"
#include "qorai/components/qorai_private_new_tab_ui/common/qorai_private_new_tab.mojom.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/tor/tor_launcher_observer.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

class Profile;

namespace content {
class WebContents;
}  // namespace content

#if BUILDFLAG(ENABLE_TOR)
class TorLauncherFactory;
#endif

class QoraiPrivateNewTabPageHandler
    : public qorai_private_new_tab::mojom::PageHandler,
      public TorLauncherObserver {
 public:
  QoraiPrivateNewTabPageHandler(
      Profile* profile,
      content::WebContents* web_contents,
      mojo::PendingReceiver<qorai_private_new_tab::mojom::PageHandler>
          receiver);

  QoraiPrivateNewTabPageHandler(const QoraiPrivateNewTabPageHandler&) = delete;
  QoraiPrivateNewTabPageHandler& operator=(
      const QoraiPrivateNewTabPageHandler&) = delete;

  ~QoraiPrivateNewTabPageHandler() override;

  // qorai_private_new_tab::mojom::PageHandler overrides:
  void SetClientPage(
      mojo::PendingRemote<qorai_private_new_tab::mojom::PrivateTabPage> page)
      override;
  void SetDisclaimerDismissed(bool dismissed) override;
  void GetDisclaimerDismissed(GetDisclaimerDismissedCallback callback) override;
  void GetIsTorConnected(GetIsTorConnectedCallback callback) override;
  void GetIsTorDisabled(GetIsTorDisabledCallback callback) override;
  void GoToQoraiSearch(const std::string& input, bool open_new_tab) override;
  void GoToQoraiSupport() override;

 private:
  // TorLauncherObserver overrides:
  void OnTorCircuitEstablished(bool result) override;
  void OnTorInitializing(const std::string& percentage,
                         const std::string& message) override;

  void OnTorCircuitTimer(qorai_private_new_tab::mojom::ConnectionStatus status);

  // Handle back to the page by which we can pass results.
  mojo::Remote<qorai_private_new_tab::mojom::PrivateTabPage> page_;

  // The Profile* handed to us in our constructor.
  raw_ptr<Profile> profile_;

  raw_ptr<content::WebContents> web_contents_ = nullptr;

#if BUILDFLAG(ENABLE_TOR)
  raw_ptr<TorLauncherFactory> tor_launcher_factory_ = nullptr;
#endif
  // Timer for detecting a Tor connection failuer. It starts at each connection
  // event and shots when the time between events exceeds kStuckPeriod seconds.
  base::OneShotTimer stuck_timer_;

  mojo::Receiver<qorai_private_new_tab::mojom::PageHandler> receiver_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_PRIVATE_NEW_TAB_PAGE_QORAI_PRIVATE_NEW_TAB_PAGE_HANDLER_H_
