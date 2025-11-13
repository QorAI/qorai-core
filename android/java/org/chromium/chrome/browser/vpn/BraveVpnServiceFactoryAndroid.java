/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.vpn;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.qorai_vpn.mojom.ServiceHandler;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.bindings.Interface;
import org.chromium.mojo.bindings.Interface.Proxy.Handler;
import org.chromium.mojo.system.MessagePipeHandle;
import org.chromium.mojo.system.impl.CoreImpl;

@JNINamespace("chrome::android")
public class QoraiVpnServiceFactoryAndroid {
    private static final Object sLock = new Object();
    private static QoraiVpnServiceFactoryAndroid sInstance;

    public static QoraiVpnServiceFactoryAndroid getInstance() {
        synchronized (sLock) {
            if (sInstance == null) {
                sInstance = new QoraiVpnServiceFactoryAndroid();
            }
        }
        return sInstance;
    }

    private QoraiVpnServiceFactoryAndroid() {}

    public ServiceHandler getVpnService(
            Profile profile, ConnectionErrorHandler connectionErrorHandler) {
        if (profile == null) {
            return null;
        }
        long nativeHandle =
                QoraiVpnServiceFactoryAndroidJni.get().getInterfaceToVpnService(profile);
        if (nativeHandle == -1) {
            return null;
        }
        MessagePipeHandle handle = wrapNativeHandle(nativeHandle);
        ServiceHandler serviceHandler = ServiceHandler.MANAGER.attachProxy(handle, 0);
        Handler handler = ((Interface.Proxy) serviceHandler).getProxyHandler();
        handler.setErrorHandler(connectionErrorHandler);

        return serviceHandler;
    }

    private MessagePipeHandle wrapNativeHandle(long nativeHandle) {
        return CoreImpl.getInstance().acquireNativeHandle(nativeHandle).toMessagePipeHandle();
    }

    @NativeMethods
    interface Natives {
        long getInterfaceToVpnService(Profile profile);
    }
}
