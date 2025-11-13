/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAutocompleteEditTextClassAdapter extends QoraiClassVisitor {
    static String sQoraiAutocompleteEditText =
            "org/chromium/chrome/browser/omnibox/QoraiAutocompleteEditText";
    static String sUrlBarClassName = "org/chromium/chrome/browser/omnibox/UrlBar";

    public QoraiAutocompleteEditTextClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sUrlBarClassName, sQoraiAutocompleteEditText);
    }
}
