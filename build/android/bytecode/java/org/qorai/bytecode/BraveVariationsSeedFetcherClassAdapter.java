/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiVariationsSeedFetcherClassAdapter extends QoraiClassVisitor {
    static String sVariationsSeedFetcherClassName =
            "org/chromium/components/variations/firstrun/VariationsSeedFetcher";
    static String sQoraiVariationsSeedFetcherClassName =
            "org/chromium/components/variations/firstrun/QoraiVariationsSeedFetcher";

    public QoraiVariationsSeedFetcherClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sVariationsSeedFetcherClassName, "get", sQoraiVariationsSeedFetcherClassName);

        deleteField(sQoraiVariationsSeedFetcherClassName, "sLock");
        makeProtectedField(sVariationsSeedFetcherClassName, "sLock");
        deleteField(sQoraiVariationsSeedFetcherClassName, "DEFAULT_VARIATIONS_SERVER_URL");
        makeProtectedField(sVariationsSeedFetcherClassName, "DEFAULT_VARIATIONS_SERVER_URL");
        deleteField(sQoraiVariationsSeedFetcherClassName, "DEFAULT_FAST_VARIATIONS_SERVER_URL");
        makeProtectedField(sVariationsSeedFetcherClassName, "DEFAULT_FAST_VARIATIONS_SERVER_URL");
    }
}
