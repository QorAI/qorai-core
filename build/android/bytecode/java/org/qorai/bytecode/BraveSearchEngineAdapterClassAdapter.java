/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSearchEngineAdapterClassAdapter extends QoraiClassVisitor {
    static String sSearchEngineAdapterClassName =
            "org/chromium/chrome/browser/search_engines/settings/SearchEngineAdapter";

    static String sQoraiSearchEngineAdapterClassName =
            "org/chromium/chrome/browser/search_engines/settings/QoraiSearchEngineAdapter";

    static String sQoraiBaseSearchEngineAdapterClassName =
            "org/chromium/chrome/browser/search_engines/settings/QoraiBaseSearchEngineAdapter";

    static String sSearchEngineSettingsClassName =
            "org/chromium/chrome/browser/search_engines/settings/SearchEngineSettings";

    static String sQoraiSearchEnginePreferenceClassName =
            "org/chromium/chrome/browser/search_engines/settings/QoraiSearchEnginePreference";

    static String sMethodGetSearchEngineSourceType = "getSearchEngineSourceType";

    static String sMethodSortAndFilterUnnecessaryTemplateUrl =
            "sortAndFilterUnnecessaryTemplateUrl";

    public QoraiSearchEngineAdapterClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeSuperName(sSearchEngineAdapterClassName, sQoraiBaseSearchEngineAdapterClassName);

        changeMethodOwner(sSearchEngineAdapterClassName, sMethodGetSearchEngineSourceType,
                sQoraiBaseSearchEngineAdapterClassName);

        changeMethodOwner(sSearchEngineAdapterClassName, sMethodSortAndFilterUnnecessaryTemplateUrl,
                sQoraiBaseSearchEngineAdapterClassName);

        deleteField(sQoraiSearchEngineAdapterClassName, "mProfile");
        makeProtectedField(sSearchEngineAdapterClassName, "mProfile");
    }
}
