// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_PERF_QORAI_PERF_FEATURES_PROCESSOR_H_
#define QORAI_BROWSER_PERF_QORAI_PERF_FEATURES_PROCESSOR_H_

class Profile;

namespace perf {

// Handlers for --enable-qorai-features-for-perf-testing switch.
// They are split into two because the first is invoked from
// QoraiProfileManager::InitProfileUserPrefs and cannot instantiate services
// that rely on identity manager because ProfileImpl::OnLocaleReady expects
// identity manager not to be initialized before browser context services are
// created. The second one is invoked from
// QoraiProfileManager::DoFinalInitForServices.
void MaybeEnableQoraiFeaturesPrefsForPerfTesting(Profile* profile);
void MaybeEnableQoraiFeaturesServicesAndComponentsForPerfTesting(
    Profile* profile);

}  // namespace perf

#endif  // QORAI_BROWSER_PERF_QORAI_PERF_FEATURES_PROCESSOR_H_
