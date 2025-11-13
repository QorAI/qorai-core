/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiCachedFlagUtilsClassAdapter extends QoraiClassVisitor {
    static String sCachedFlagUtilsClassName =
            "org/chromium/components/cached_flags/CachedFlagUtils";
    static String sQoraiCachedFlagUtilsClassName =
            "org/chromium/components/cached_flags/QoraiCachedFlagUtils";

    public QoraiCachedFlagUtilsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sCachedFlagUtilsClassName, "cacheNativeFlags", sQoraiCachedFlagUtilsClassName);
        changeMethodOwner(
                sCachedFlagUtilsClassName, "cacheFeatureParams", sQoraiCachedFlagUtilsClassName);
        changeMethodOwner(
                sCachedFlagUtilsClassName, "setFullListOfFlags", sQoraiCachedFlagUtilsClassName);
        changeMethodOwner(
                sCachedFlagUtilsClassName,
                "setFullListOfFeatureParams",
                sQoraiCachedFlagUtilsClassName);
    }
}
