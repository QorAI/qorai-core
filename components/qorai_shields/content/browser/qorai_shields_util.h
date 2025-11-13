// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_QORAI_SHIELDS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_QORAI_SHIELDS_UTIL_H_

namespace content {
struct Referrer;
}

class GURL;
class HostContentSettingsMap;

namespace qorai_shields {

// Referrers is always set along with cookies so there is no setter and
// these is just included for backwards compat.
bool AreReferrersAllowed(HostContentSettingsMap* map, const GURL& url);

bool IsSameOriginNavigation(const GURL& referrer, const GURL& target_url);

bool MaybeChangeReferrer(bool allow_referrers,
                         bool shields_up,
                         const GURL& current_referrer,
                         const GURL& target_url,
                         content::Referrer* output_referrer);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_QORAI_SHIELDS_UTIL_H_
