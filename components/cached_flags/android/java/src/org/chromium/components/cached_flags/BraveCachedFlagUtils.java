/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.cached_flags;

import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;

/**
 * Qorai's extension of CachedFlagUtils to include Qorai-specific cached flags and feature params.
 */
@NullMarked
public class QoraiCachedFlagUtils extends CachedFlagUtils {
    private static @Nullable List<CachedFlag> sQoraiFlags;
    private static @Nullable List<CachedFeatureParam<?>> sQoraiParams;

    /** Set Qorai-specific cached flags. */
    public static void setQoraiFlags(List<CachedFlag> qoraiFlags) {
        sQoraiFlags = qoraiFlags;
    }

    /** Set Qorai-specific cached feature parameters. */
    public static void setQoraiParams(List<CachedFeatureParam<?>> qoraiParams) {
        sQoraiParams = qoraiParams;
    }

    /** Caches flags that must take effect on startup but are set via native code. */
    public static void cacheNativeFlags(List<List<CachedFlag>> listsOfFeaturesToCache) {
        List<List<CachedFlag>> allLists = new ArrayList<>(listsOfFeaturesToCache);
        if (sQoraiFlags != null && !sQoraiFlags.isEmpty()) {
            allLists.add(sQoraiFlags);
        }
        CachedFlagUtils.cacheNativeFlags(allLists);
    }

    /** Caches feature params that must take effect on startup but are set via native code. */
    public static void cacheFeatureParams(List<List<CachedFeatureParam<?>>> listsOfParameters) {
        List<List<CachedFeatureParam<?>>> allLists = new ArrayList<>(listsOfParameters);
        if (sQoraiParams != null && !sQoraiParams.isEmpty()) {
            allLists.add(sQoraiParams);
        }
        CachedFlagUtils.cacheFeatureParams(allLists);
    }

    /** Store a reference to the full list of CachedFlags for future use. */
    public static void setFullListOfFlags(List<List<CachedFlag>> listsOfFlags) {
        List<List<CachedFlag>> allLists = new ArrayList<>(listsOfFlags);
        if (sQoraiFlags != null && !sQoraiFlags.isEmpty()) {
            allLists.add(sQoraiFlags);
        }
        CachedFlagUtils.setFullListOfFlags(allLists);
    }

    /** Store a reference to the full list of CachedFeatureParam for future use. */
    public static void setFullListOfFeatureParams(
            List<List<CachedFeatureParam<?>>> listsOfParameters) {
        List<List<CachedFeatureParam<?>>> allLists = new ArrayList<>(listsOfParameters);
        if (sQoraiParams != null && !sQoraiParams.isEmpty()) {
            allLists.add(sQoraiParams);
        }
        CachedFlagUtils.setFullListOfFeatureParams(allLists);
    }
}
