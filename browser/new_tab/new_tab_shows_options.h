/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
#define QORAI_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_

#include "base/values.h"
#include "url/gurl.h"

class Profile;

namespace qorai {

enum class NewTabPageShowsOptions {
  kDashboard,
  kHomepage,
  kBlankpage
};

GURL GetNewTabPageURL(Profile* profile);
base::Value::List GetNewTabShowsOptionsList(Profile* profile);
bool ShouldUseNewTabURLForNewTab(Profile* profile);
bool ShouldNewTabShowDashboard(Profile* profile);
bool ShouldNewTabShowBlankpage(Profile* profile);

}  // namespace qorai

#endif  // QORAI_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
