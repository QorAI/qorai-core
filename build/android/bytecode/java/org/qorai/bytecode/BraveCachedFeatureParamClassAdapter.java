/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiCachedFeatureParamClassAdapter extends QoraiClassVisitor {
    static String sCachedFeatureParamClassName =
            "org/chromium/components/cached_flags/CachedFeatureParam";
    static String sQoraiCachedFeatureParamClassName =
            "org/chromium/components/cached_flags/QoraiCachedFeatureParam";

    public QoraiCachedFeatureParamClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sCachedFeatureParamClassName, "getAllInstances", sQoraiCachedFeatureParamClassName);
    }
}
