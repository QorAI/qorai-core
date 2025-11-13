/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_VIEW_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/browser/ui/commands/accelerator_service.h"
#include "qorai/browser/ui/tabs/qorai_tab_strip_model.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/commands/browser/accelerator_pref_manager.h"
#include "build/build_config.h"
#include "chrome/browser/ui/tabs/tab_model.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/frame/contents_web_view.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/base/metadata/metadata_header_macros.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/ui/views/toolbar/qorai_vpn_panel_controller.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/ui/views/speedreader/reader_mode_toolbar_view.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
namespace speedreader {
class SpeedreaderBubbleView;
class SpeedreaderTabHelper;
enum class SpeedreaderBubbleLocation : int;
}  // namespace speedreader
#endif

namespace sidebar {
FORWARD_DECLARE_TEST(SidebarBrowserWithSplitViewTest,
                     ShowSidebarOnMouseOverTest);
}  // namespace sidebar

namespace content {
class WebContents;
}  // namespace content

namespace sidebar {
class SidebarBrowserTest;
}  // namespace sidebar

namespace views {
class Widget;
}  // namespace views

class QoraiBrowser;
class QoraiHelpBubbleHostView;
class QoraiMultiContentsView;
class ContentsLayoutManager;
class SidebarContainerView;
class SidePanelEntry;
class VerticalTabStripWidgetDelegateView;
class ViewShadow;
class WalletButton;

class QoraiBrowserView : public BrowserView,
                         public commands::AcceleratorService::Observer {
  METADATA_HEADER(QoraiBrowserView, BrowserView)
 public:
  explicit QoraiBrowserView(Browser* browser);
  QoraiBrowserView(const QoraiBrowserView&) = delete;
  QoraiBrowserView& operator=(const QoraiBrowserView&) = delete;
  ~QoraiBrowserView() override;

  static QoraiBrowserView* From(BrowserView* view);

  // We use rounded corners even rounded corners setting is disabled.
  // Call this when we want to know
  static bool ShouldUseQoraiWebViewRoundedCornersForContents(Browser* browser);

  void SetStarredState(bool is_starred) override;
  void ShowUpdateChromeDialog() override;

  void ShowQoraiVPNBubble(bool show_select = false);
  void CreateWalletBubble();
  void CreateApproveWalletBubble();
  void CloseWalletBubble();
  WalletButton* GetWalletButton();
  views::View* GetWalletButtonAnchorView();
  void UpdateContentsSeparatorVisibility();

  // Triggers layout of web modal dialogs
  void NotifyDialogPositionRequiresUpdate();

  // BrowserView overrides:
  void Layout(PassKey) override;
  void StartTabCycling() override;
  views::View* GetAnchorViewForQoraiVPNPanel();
  gfx::Rect GetShieldsBubbleRect() override;
#if BUILDFLAG(ENABLE_SPEEDREADER)
  // Give active tab's reader mode toolbar.
  ReaderModeToolbarView* reader_mode_toolbar();
  speedreader::SpeedreaderBubbleView* ShowSpeedreaderBubble(
      speedreader::SpeedreaderTabHelper* tab_helper,
      speedreader::SpeedreaderBubbleLocation location) override;
  void UpdateReaderModeToolbar() override;
#endif
  bool GetTabStripVisible() const override;
  bool ShouldShowWindowTitle() const override;
  void OnThemeChanged() override;
  void OnActiveTabChanged(content::WebContents* old_contents,
                          content::WebContents* new_contents,
                          int index,
                          int reason) override;
  bool AcceleratorPressed(const ui::Accelerator& accelerator) override;
  bool IsInTabDragging() const override;
  void ReadyToListenFullscreenChanges() override;

#if defined(USE_AURA)
  views::View* sidebar_host_view() { return sidebar_host_view_; }
#endif

  void StopListeningFullscreenChanges();
  bool IsSidebarVisible() const;
  void SetSidePanelOperationByActiveTabChange(bool tab_change);

  VerticalTabStripWidgetDelegateView*
  vertical_tab_strip_widget_delegate_view() {
    return vertical_tab_strip_widget_delegate_view_;
  }
  bool ShowQoraiHelpBubbleView(const std::string& text) override;

  // commands::AcceleratorService:
  void OnAcceleratorsChanged(const commands::Accelerators& changed) override;

  QoraiMultiContentsView* GetQoraiMultiContentsView() const;
  void UpdateRoundedCornersUI();
  void UpdateVerticalTabStripBorder();
  void UpdateSidebarBorder();

  SidebarContainerView* sidebar_container_view() {
    return sidebar_container_view_;
  }

 private:
  class TabCyclingEventHandler;
  class SidebarOnMouseOverEventHandler;
  friend class WindowClosingConfirmBrowserTest;
  friend class sidebar::SidebarBrowserTest;
  friend class VerticalTabStripDragAndDropBrowserTest;
  friend class SplitViewBrowserTest;
  friend class QoraiBrowserViewTest;

  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripBrowserTest, VisualState);
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripBrowserTest, Fullscreen);
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripDragAndDropBrowserTest,
                           DragTabToReorder);
  FRIEND_TEST_ALL_PREFIXES(SpeedReaderBrowserTest, Toolbar);
  FRIEND_TEST_ALL_PREFIXES(SpeedReaderBrowserTest, ToolbarLangs);
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripBrowserTest, ExpandedState);
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripBrowserTest, ExpandedWidth);
  FRIEND_TEST_ALL_PREFIXES(SideBySideEnabledBrowserTest,
                           QoraiMultiContentsViewTest);
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripHideCompletelyTest, GetMinimumWidth);
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripHideCompletelyTest,
                           ShouldBeInvisible);
  FRIEND_TEST_ALL_PREFIXES(SideBySideWithRoundedCornersTest,
                           TabFullscreenStateTest);
  FRIEND_TEST_ALL_PREFIXES(QoraiBrowserViewWithRoundedCornersTest,
                           ContentsBackgroundEventHandleTest);
  FRIEND_TEST_ALL_PREFIXES(SideBySideWithRoundedCornersTest,
                           ContentsShadowTest);
  FRIEND_TEST_ALL_PREFIXES(sidebar::SidebarBrowserWithSplitViewTest,
                           ShowSidebarOnMouseOverTest);

  static void SetDownloadConfirmReturnForTesting(bool allow);

  // BrowserView overrides:
  void AddedToWidget() override;
  void LoadAccelerators() override;
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;
  views::CloseRequestResult OnWindowCloseRequested() override;
  void ConfirmBrowserCloseWithPendingDownloads(
      int download_count,
      Browser::DownloadCloseType dialog_type,
      base::OnceCallback<void(bool)> callback) override;
  void MaybeShowReadingListInSidePanelIPH() override;
  bool MaybeUpdateDevtools(content::WebContents* web_contents) override;
  void OnWidgetActivationChanged(views::Widget* widget, bool active) override;
  void OnWidgetWindowModalVisibilityChanged(views::Widget* widget,
                                            bool visible) override;
  void ShowSplitView(bool focus_active_view) override;
  void HideSplitView() override;

  void HandleSidebarOnMouseOverMouseEvent(const ui::MouseEvent& event);
  bool IsQoraiWebViewRoundedCornersEnabled();
  void UpdateContentsShadowVisibility();
  void StopTabCycling();
  void UpdateSearchTabsButtonState();
  void OnPreferenceChanged(const std::string& pref_name);
  void OnWindowClosingConfirmResponse(bool allowed_to_close);
  QoraiBrowser* GetQoraiBrowser() const;
  void UpdateWebViewRoundedCorners();

  sidebar::Sidebar* InitSidebar() override;
  void ToggleSidebar() override;
  bool HasSelectedURL() const override;
  void CleanAndCopySelectedURL() override;

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
  void ShowPlaylistBubble() override;
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
  void ShowWaybackMachineBubble() override;
#endif

  void UpdateSideBarHorizontalAlignment();
  views::View* top_container_separator_for_testing() const {
    return top_container_separator_;
  }

  std::unique_ptr<views::Widget> vertical_tab_strip_widget_;

  bool closing_confirm_dialog_activated_ = false;
  raw_ptr<QoraiHelpBubbleHostView> qorai_help_bubble_host_view_ = nullptr;
  raw_ptr<SidebarContainerView> sidebar_container_view_ = nullptr;
  raw_ptr<views::View> sidebar_separator_view_ = nullptr;
  raw_ptr<views::View> contents_background_view_ = nullptr;
  raw_ptr<views::View> vertical_tab_strip_host_view_ = nullptr;
  raw_ptr<VerticalTabStripWidgetDelegateView, DanglingUntriaged>
      vertical_tab_strip_widget_delegate_view_ = nullptr;

#if defined(USE_AURA)
  raw_ptr<views::View> sidebar_host_view_ = nullptr;
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
  QoraiVPNPanelController vpn_panel_controller_{this};
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
  raw_ptr<ReaderModeToolbarView> reader_mode_toolbar_;
#endif

  std::unique_ptr<TabCyclingEventHandler> tab_cycling_event_handler_;
  std::unique_ptr<SidebarOnMouseOverEventHandler>
      sidebar_on_mouse_over_event_handler_;
  std::unique_ptr<ViewShadow> contents_shadow_;

  PrefChangeRegistrar pref_change_registrar_;
  base::ScopedObservation<commands::AcceleratorService,
                          commands::AcceleratorService::Observer>
      accelerators_observation_{this};

  base::WeakPtrFactory<QoraiBrowserView> weak_ptr_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_VIEW_H_
