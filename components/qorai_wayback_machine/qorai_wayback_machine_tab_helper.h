/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WAYBACK_MACHINE_QORAI_WAYBACK_MACHINE_TAB_HELPER_H_
#define QORAI_COMPONENTS_QORAI_WAYBACK_MACHINE_QORAI_WAYBACK_MACHINE_TAB_HELPER_H_

#include <optional>
#include <string>

#include "base/functional/callback_forward.h"
#include "base/gtest_prod_util.h"
#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_wayback_machine/wayback_machine_url_fetcher.h"
#include "qorai/components/qorai_wayback_machine/wayback_state.h"
#include "components/prefs/pref_member.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "ui/gfx/native_ui_types.h"

class PrefService;

class QoraiWaybackMachineTabHelper
    : public content::WebContentsObserver,
      public WaybackMachineURLFetcher::Client,
      public content::WebContentsUserData<QoraiWaybackMachineTabHelper> {
 public:
  static void CreateIfNeeded(content::WebContents* web_contents);

  using WaybackStateChangedCallback =
      base::RepeatingCallback<void(WaybackState state)>;

  ~QoraiWaybackMachineTabHelper() override;

  QoraiWaybackMachineTabHelper(const QoraiWaybackMachineTabHelper&) = delete;
  QoraiWaybackMachineTabHelper& operator=(
      const QoraiWaybackMachineTabHelper&) = delete;

  void SetWaybackStateChangedCallback(WaybackStateChangedCallback callback);
  void set_active_window(std::optional<gfx::NativeWindow> window) {
    active_window_ = window;
  }
  std::optional<gfx::NativeWindow> active_window() const {
    return active_window_;
  }
  WaybackState wayback_state() const { return wayback_state_; }

  void FetchWaybackURL();

 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiWaybackMachineTest, BubbleLaunchTest);

  explicit QoraiWaybackMachineTabHelper(content::WebContents* contents);

  // content::WebContentsObserver overrides:
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;

  // WaybackMachineURLFetcher::Client overrides:
  void OnWaybackURLFetched(const GURL& latest_wayback_url) override;

  void SetWaybackState(WaybackState state);
  bool ShouldCheckWaybackMachine(int response_code) const;
  void OnWaybackEnabledChanged(const std::string& pref_name);
  void ResetState();

  // Cache wayback url navigation handle.
  // It uses to check whether it's wayback url loading or not.
  // If it's wayback url loading from previous navigation,
  // we should not touch wayback state.
  std::optional<int64_t> wayback_url_navigation_id_;

  // If not null, this tab has active window.
  std::optional<gfx::NativeWindow> active_window_;
  WaybackState wayback_state_ = WaybackState::kInitial;
  WaybackStateChangedCallback wayback_state_changed_callback_;
  raw_ref<PrefService> pref_service_;
  WaybackMachineURLFetcher wayback_machine_url_fetcher_;
  BooleanPrefMember wayback_enabled_;

  friend WebContentsUserData;
  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

#endif  // QORAI_COMPONENTS_QORAI_WAYBACK_MACHINE_QORAI_WAYBACK_MACHINE_TAB_HELPER_H_
