/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_BROWSER_H_
#define QORAI_BROWSER_UI_QORAI_BROWSER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/browser.h"

class QoraiBrowserWindow;

namespace content {
class WebContents;
}  // namespace content

class QoraiBrowser : public Browser {
 public:
  explicit QoraiBrowser(const CreateParams& params);
  ~QoraiBrowser() override;

  QoraiBrowser(const QoraiBrowser&) = delete;
  QoraiBrowser& operator=(const QoraiBrowser&) = delete;

  // Browser overrides:
  void ScheduleUIUpdate(content::WebContents* source,
                        unsigned changed_flags) override;
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;
  void FinishWarnBeforeClosing(WarnBeforeClosingResult result) override;
  void BeforeUnloadFired(content::WebContents* source,
                         bool proceed,
                         bool* proceed_to_fire_unload) override;
  bool TryToCloseWindow(
      bool skip_beforeunload,
      const base::RepeatingCallback<void(bool)>& on_close_confirmed) override;
  void UpdateTargetURL(content::WebContents* source, const GURL& url) override;
  void ResetTryToCloseWindow() override;
  bool NormalBrowserSupportsWindowFeature(
      WindowFeature feature,
      bool check_can_support) const override;

  // This overrides ChromeWebModalDialogManagerDelegate::IsWebContentsVisible()
  // and it's called from WebContentsModalDialogManager.
  // That manager prevents web modal dialog when web contents is not visible.
  // As we have visible but inactive tabs in split tab, this should return false
  // when it's inactive tab. Otherwse, web modal from inactive split tab can be
  // shown.
  bool IsWebContentsVisible(content::WebContents* web_contents) override;

  void OnTabClosing(content::WebContents* contents) override;
  void TabStripEmpty() override;

  void RunFileChooser(content::RenderFrameHost* render_frame_host,
                      scoped_refptr<content::FileSelectListener> listener,
                      const blink::mojom::FileChooserParams& params) override;

  void TabCustomTitleChanged(
      content::WebContents* contents,
      const std::optional<std::string>& custom_title) override;

  // Returns true when we should ask browser closing to users before handling
  // any warning/onbeforeunload handlers.
  bool ShouldAskForBrowserClosingBeforeHandlers();

  QoraiBrowserWindow* qorai_window();

  void set_confirmed_to_close(bool close) { confirmed_to_close_ = close; }

  void set_ignore_enable_closing_last_tab_pref() {
    ignore_enable_closing_last_tab_pref_ = true;
  }

 private:
  friend class QoraiTestLauncherDelegate;
  friend class WindowClosingConfirmBrowserTest;
  friend class InProcessBrowserTest;

  // static
  static void SuppressBrowserWindowClosingDialogForTesting(bool suppress);

  bool AreAllTabsSharedPinnedTabs();

  // Set true when user allowed to close browser before starting any
  // warning or onbeforeunload handlers.
  bool confirmed_to_close_ = false;

  // When "kEnableClosingLastTab" is false, browser will try to add new tab in
  // TabStripEmpty() if there is no tab. But, in some cases, we should not add
  // new tab, like when user tries to "Bring all tabs" to other window.
  bool ignore_enable_closing_last_tab_pref_ = false;

  base::WeakPtrFactory<QoraiBrowser> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_UI_QORAI_BROWSER_H_
