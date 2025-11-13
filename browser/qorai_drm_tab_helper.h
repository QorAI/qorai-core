/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_DRM_TAB_HELPER_H_
#define QORAI_BROWSER_QORAI_DRM_TAB_HELPER_H_

#include "base/scoped_observation.h"
#include "qorai/components/qorai_drm/qorai_drm.mojom.h"
#include "components/component_updater/component_updater_service.h"
#include "content/public/browser/render_frame_host_receiver_set.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

// Reacts to DRM content detected on the renderer side.
class QoraiDrmTabHelper final
    : public content::WebContentsObserver,
      public content::WebContentsUserData<QoraiDrmTabHelper>,
      public qorai_drm::mojom::QoraiDRM,
      public component_updater::ComponentUpdateService::Observer {
 public:
  explicit QoraiDrmTabHelper(content::WebContents* contents);
  ~QoraiDrmTabHelper() override;

  static void BindQoraiDRM(
      mojo::PendingAssociatedReceiver<qorai_drm::mojom::QoraiDRM> receiver,
      content::RenderFrameHost* rfh);

  bool ShouldShowWidevineOptIn() const;

  // content::WebContentsObserver
  void DidStartNavigation(
      content::NavigationHandle* navigation_handle) override;

  // blink::mojom::QoraiDRM
  void OnWidevineKeySystemAccessRequest() override;

  // component_updater::ComponentUpdateService::Observer
  void OnEvent(const update_client::CrxUpdateItem& item) override;

  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  content::RenderFrameHostReceiverSet<qorai_drm::mojom::QoraiDRM>
      qorai_drm_receivers_;

  // Permission request is done only once during the navigation. If user
  // chooses dismiss/deny, additional request is added again only when new
  // main frame navigation is started.
  bool is_permission_requested_ = false;

  // True if we are notified that a page requested widevine availability.
  bool is_widevine_requested_ = false;

  base::ScopedObservation<component_updater::ComponentUpdateService,
                          component_updater::ComponentUpdateService::Observer>
      observer_{this};
};

#endif  // QORAI_BROWSER_QORAI_DRM_TAB_HELPER_H_
