/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiIntentHandlerClassAdapter extends QoraiClassVisitor {
    static String sIntentHandlerClassName = "org/chromium/chrome/browser/IntentHandler";
    static String sQoraiIntentHandlerClassName = "org/chromium/chrome/browser/QoraiIntentHandler";

    public QoraiIntentHandlerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        makePublicMethod(sIntentHandlerClassName, "getUrlForCustomTab");
        changeMethodOwner(
                sQoraiIntentHandlerClassName, "getUrlForCustomTab", sIntentHandlerClassName);

        makePublicMethod(sIntentHandlerClassName, "getUrlForWebapp");
        changeMethodOwner(sQoraiIntentHandlerClassName, "getUrlForWebapp", sIntentHandlerClassName);

        makePublicMethod(sIntentHandlerClassName, "isJavascriptSchemeOrInvalidUrl");
        changeMethodOwner(sQoraiIntentHandlerClassName, "isJavascriptSchemeOrInvalidUrl",
                sIntentHandlerClassName);

        changeMethodOwner(
                sIntentHandlerClassName, "extractUrlFromIntent", sQoraiIntentHandlerClassName);
    }
}
