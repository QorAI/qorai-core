/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_PROFILES_PROFILE_UTIL_H_
#define QORAI_BROWSER_PROFILES_PROFILE_UTIL_H_

class Profile;

namespace qorai {

// Used for capturing the value of kQoraiCurrentDataVersion so that the
// default search engine for that version can be determined. New profiles
// will get locked into newer versions when created. Existing profiles
// missing this value are backfilled to the first version introduced.
void SetDefaultSearchVersion(Profile* profile, bool is_new_profile);

// Sets the default value for Cookie Controls Mode to 'Block Third Party'
// instead of 'Block Third Party in Incognito'
void SetDefaultThirdPartyCookieBlockValue(Profile* profile);

// Checks if the user previously had fingerprinting mode disabled.
// If so, set the new fingerprinting toggle to disabled.
void MigrateFingerprintingSettings(Profile* profile);

}  // namespace qorai

#endif  // QORAI_BROWSER_PROFILES_PROFILE_UTIL_H_
