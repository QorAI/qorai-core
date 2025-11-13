/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.app.flags;

import org.chromium.base.QoraiFeatureList;
import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.browser.flags.ChromeFeatureMap;
import org.chromium.components.cached_flags.QoraiCachedFeatureParam;
import org.chromium.components.cached_flags.QoraiCachedFlagUtils;
import org.chromium.components.cached_flags.CachedFeatureParam;
import org.chromium.components.cached_flags.CachedFlag;
import org.chromium.components.cached_flags.StringCachedFeatureParam;

import java.util.List;

@NullMarked
public class QoraiCachedFlags extends ChromeCachedFlags {
    // Cached feature flag for fresh NTP after idle expiration - safe to access before native is
    // ready
    public static final CachedFlag sQoraiFreshNtpAfterIdleExpirementEnabled =
            new CachedFlag(
                    ChromeFeatureMap.getInstance(),
                    QoraiFeatureList.QORAI_FRESH_NTP_AFTER_IDLE_EXPIREMENT,
                    false);

    // Cached variant parameter for fresh NTP experiment - safe to access before native is ready
    public static final StringCachedFeatureParam sQoraiFreshNtpAfterIdleExpirementVariant =
            new StringCachedFeatureParam(
                    ChromeFeatureMap.getInstance(),
                    QoraiFeatureList.QORAI_FRESH_NTP_AFTER_IDLE_EXPIREMENT,
                    "variant",
                    "A");

    // List of cached flags for Qorai features - safe to access before native is ready
    private static final List<CachedFlag> sQoraiFlagsCached =
            List.of(sQoraiFreshNtpAfterIdleExpirementEnabled);
    // List of cached feature params for Qorai features - safe to access before native is ready
    private static final List<CachedFeatureParam<?>> sQoraiFeatureParamsCached =
            List.of(sQoraiFreshNtpAfterIdleExpirementVariant);

    QoraiCachedFlags() {
        QoraiCachedFeatureParam.setQoraiParams(sQoraiFeatureParamsCached);
        QoraiCachedFlagUtils.setQoraiFlags(sQoraiFlagsCached);
        QoraiCachedFlagUtils.setQoraiParams(sQoraiFeatureParamsCached);
    }
}
