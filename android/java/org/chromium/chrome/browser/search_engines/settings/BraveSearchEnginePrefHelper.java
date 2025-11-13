/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.search_engines.settings;

import org.jni_zero.NativeMethods;

import org.chromium.base.ThreadUtils;

public class QoraiSearchEnginePrefHelper {
    private static QoraiSearchEnginePrefHelper sInstance;

    private QoraiSearchEnginePrefHelper() {}

    public static QoraiSearchEnginePrefHelper getInstance() {
        ThreadUtils.assertOnUiThread();
        if (sInstance == null) {
            sInstance = new QoraiSearchEnginePrefHelper();
        }
        return sInstance;
    }

    public void setFetchSEFromNative(boolean value) {
        QoraiSearchEnginePrefHelperJni.get().setFetchSEFromNative(value);
    }

    public boolean getFetchSEFromNative() {
        return QoraiSearchEnginePrefHelperJni.get().getFetchSEFromNative();
    }

    @NativeMethods
    interface Natives {
        void setFetchSEFromNative(boolean value);
        boolean getFetchSEFromNative();
    }
}
