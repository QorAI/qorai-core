/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_ROUNDED_OMNIBOX_RESULTS_FRAME_H_
#define QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_ROUNDED_OMNIBOX_RESULTS_FRAME_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/views/omnibox/rounded_omnibox_results_frame.h"
#include "components/prefs/pref_member.h"

class Browser;
class LocationBarView;

class QoraiRoundedOmniboxResultsFrame : public RoundedOmniboxResultsFrame {
  METADATA_HEADER(QoraiRoundedOmniboxResultsFrame, RoundedOmniboxResultsFrame)
 public:
  QoraiRoundedOmniboxResultsFrame(views::View* contents,
                                  LocationBarView* location_bar);
  ~QoraiRoundedOmniboxResultsFrame() override;

 private:
  void UpdateShadowBorder();

  BooleanPrefMember show_vertical_tabs_;
  BooleanPrefMember show_window_title_for_vertical_tabs_;

  raw_ptr<Browser> browser_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_ROUNDED_OMNIBOX_RESULTS_FRAME_H_
