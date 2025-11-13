/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAutocompleteMediatorClassAdapter extends QoraiClassVisitor {
    static String sAutocompleteMediator =
            "org/chromium/chrome/browser/omnibox/suggestions/AutocompleteMediator";
    static String sQoraiAutocompleteMediator =
            "org/chromium/chrome/browser/omnibox/suggestions/QoraiAutocompleteMediator";

    public QoraiAutocompleteMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sAutocompleteMediator, sQoraiAutocompleteMediator);

        deleteField(sQoraiAutocompleteMediator, "mDropdownViewInfoListManager");
        makeProtectedField(sAutocompleteMediator, "mDropdownViewInfoListManager");

        deleteField(sQoraiAutocompleteMediator, "mDropdownViewInfoListBuilder");
        makeProtectedField(sAutocompleteMediator, "mDropdownViewInfoListBuilder");
    }
}
