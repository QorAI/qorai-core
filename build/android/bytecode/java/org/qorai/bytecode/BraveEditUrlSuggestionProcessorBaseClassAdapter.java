/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiEditUrlSuggestionProcessorBaseClassAdapter extends QoraiClassVisitor {
    static String sEditUrlSuggestionProcessor =
            "org/chromium/chrome/browser/omnibox/suggestions/editurl/EditUrlSuggestionProcessor";
    static String sQoraiEditUrlSuggestionProcessorBase =
            "org/chromium/chrome/browser/omnibox/suggestions/editurl/QoraiEditUrlSuggestionProcessorBase";

    public QoraiEditUrlSuggestionProcessorBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sEditUrlSuggestionProcessor, sQoraiEditUrlSuggestionProcessorBase);

        changeMethodOwner(
                sEditUrlSuggestionProcessor, "onCopyLink", sQoraiEditUrlSuggestionProcessorBase);
    }
}
