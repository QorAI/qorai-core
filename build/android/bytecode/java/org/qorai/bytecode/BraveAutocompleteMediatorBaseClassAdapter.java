/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAutocompleteMediatorBaseClassAdapter extends QoraiClassVisitor {
    static String sAutocompleteMediator =
            "org/chromium/chrome/browser/omnibox/suggestions/AutocompleteMediator";
    static String sQoraiAutocompleteMediatorBase =
            "org/chromium/chrome/browser/omnibox/suggestions/QoraiAutocompleteMediatorBase";

    public QoraiAutocompleteMediatorBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sAutocompleteMediator, sQoraiAutocompleteMediatorBase);

        makeProtectedField(sAutocompleteMediator, "mContext");
        makeProtectedField(sAutocompleteMediator, "mDataProvider");
        changeMethodOwner(
                sAutocompleteMediator, "loadUrlForOmniboxMatch", sQoraiAutocompleteMediatorBase);
    }
}
