/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.minidump_uploader.util;

import org.chromium.base.version_info.VersionInfo;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;

import java.net.HttpURLConnection;

@NullMarked
public class QoraiHttpURLConnectionFactoryImpl extends HttpURLConnectionFactoryImpl {
    // Guid is intentionally zeroed so we couldn't identify our users
    static final String CRASH_URL_STRING_TEMPLATE =
            "https://cr.qorai.com/?product=Qorai_Android&version=%s&guid=00000000-0000-0000-0000-000000000000";

    @Override
    public @Nullable HttpURLConnection createHttpURLConnection(String url) {
        String version = VersionInfo.getProductVersion();
        String qoraiUploadUrl = String.format(CRASH_URL_STRING_TEMPLATE, version);
        return super.createHttpURLConnection(qoraiUploadUrl);
    }
}
