/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_PROFILE_RESETTER_QORAI_PROFILE_RESETTER_H_
#define QORAI_BROWSER_PROFILE_RESETTER_QORAI_PROFILE_RESETTER_H_

#include "chrome/browser/profile_resetter/profile_resetter.h"

// Reset qorai specific prefs.
class QoraiProfileResetter : public ProfileResetter {
 public:
  using ProfileResetter::ProfileResetter;
  QoraiProfileResetter(const QoraiProfileResetter&) = delete;
  QoraiProfileResetter& operator=(const QoraiProfileResetter&) = delete;
  ~QoraiProfileResetter() override;

  // ProfileResetter overrides:
  void ResetDefaultSearchEngine() override;
};

#endif  // QORAI_BROWSER_PROFILE_RESETTER_QORAI_PROFILE_RESETTER_H_
