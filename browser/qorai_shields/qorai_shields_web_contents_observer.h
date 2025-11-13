/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_WEB_CONTENTS_OBSERVER_H_
#define QORAI_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_WEB_CONTENTS_OBSERVER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "base/synchronization/lock.h"
#include "qorai/components/qorai_shields/core/common/qorai_shields.mojom.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/browser/render_frame_host_receiver_set.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
}

class PrefRegistrySimple;

namespace qorai_shields {

class QorAIShieldsWebContentsObserver
    : public content::WebContentsObserver,
      public content::WebContentsUserData<QorAIShieldsWebContentsObserver>,
      public qorai_shields::mojom::QorAIShieldsHost {
 public:
  explicit QorAIShieldsWebContentsObserver(content::WebContents*);
  QorAIShieldsWebContentsObserver(const QorAIShieldsWebContentsObserver&) =
      delete;
  QorAIShieldsWebContentsObserver& operator=(
      const QorAIShieldsWebContentsObserver&) = delete;
  ~QorAIShieldsWebContentsObserver() override;

  static void BindQorAIShieldsHost(
      mojo::PendingAssociatedReceiver<qorai_shields::mojom::QorAIShieldsHost>
          receiver,
      content::RenderFrameHost* rfh);

  static void RegisterProfilePrefs(PrefRegistrySimple* registry);
  static void DispatchBlockedEventForWebContents(
      const std::string& block_type,
      const std::string& subresource,
      content::WebContents* web_contents);
  static void DispatchAllowedOnceEventForWebContents(
      const std::string& block_type,
      const std::string& subresource,
      content::WebContents* web_contents);
  static void DispatchWebcompatFeatureInvokedForWebContents(
      ContentSettingsType webcompat_content_settings,
      content::WebContents* web_contents);
  static void DispatchBlockedEvent(const GURL& request_url,
                                   content::FrameTreeNodeId frame_tree_node_id,
                                   const std::string& block_type);
  static GURL GetTabURLFromRenderFrameInfo(int render_frame_tree_node_id);
  void AllowScriptsOnce(const std::vector<std::string>& origins);
  void BlockAllowedScripts(const std::vector<std::string>& origins);
  bool IsBlockedSubresource(const std::string& subresource);
  void AddBlockedSubresource(const std::string& subresource);

 protected:
  // content::WebContentsObserver overrides.
  void ReadyToCommitNavigation(
      content::NavigationHandle* navigation_handle) override;

  // qorai_shields::mojom::QorAIShieldsHost.
  void OnJavaScriptBlocked(const std::u16string& details) override;
  void OnJavaScriptAllowedOnce(const std::u16string& details) override;
  void OnWebcompatFeatureInvoked(
      ContentSettingsType webcompat_settings_type) override;

 private:
  friend class content::WebContentsUserData<QorAIShieldsWebContentsObserver>;
  friend class QorAIShieldsWebContentsObserverBrowserTest;

  // Allows indicating a implementor of qorai_shields::mojom::QorAIShieldsHost
  // other than this own class, for testing purposes only.
  static void SetReceiverImplForTesting(QorAIShieldsWebContentsObserver* impl);

  // Only used from the BindQorAIShieldsHost() static method, useful to bind
  // the mojo receiver of qorai_shields::mojom::QorAIShieldsHost to a
  // different implementor when needed, for testing purposes.
  void BindReceiver(mojo::PendingAssociatedReceiver<
                        qorai_shields::mojom::QorAIShieldsHost> receiver,
                    content::RenderFrameHost* rfh);

  // Sends the current shields settings to the renderer process bound to the
  // given |navigation_handle|.
  void SendShieldsSettings(content::NavigationHandle* navigation_handle);

  std::vector<std::string> allowed_scripts_;
  // We keep a set of the current page's blocked URLs in case the page
  // continually tries to load the same blocked URLs.
  std::set<std::string> blocked_url_paths_;

  content::RenderFrameHostReceiverSet<qorai_shields::mojom::QorAIShieldsHost>
      receivers_;

  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

}  // namespace qorai_shields

#endif  // QORAI_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_WEB_CONTENTS_OBSERVER_H_
