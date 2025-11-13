/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.sync;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

@JNINamespace("chrome::android")
public class QoraiSyncDevices {
    private static final String TAG = "SYNC";
    private long mNativeQoraiSyncDevicesAndroid;

    private static QoraiSyncDevices sQoraiSyncDevices;
    private static boolean sInitialized;

    public static QoraiSyncDevices get() {
        ThreadUtils.assertOnUiThread();
        if (!sInitialized) {
            sQoraiSyncDevices = new QoraiSyncDevices();
            sInitialized = true;
        }
        return sQoraiSyncDevices;
    }

    public QoraiSyncDevices() {
        init();
    }

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeQoraiSyncDevicesAndroid == 0;
        mNativeQoraiSyncDevicesAndroid = nativePtr;
    }

    private void init() {
        if (mNativeQoraiSyncDevicesAndroid == 0) {
            QoraiSyncDevicesJni.get().init(QoraiSyncDevices.this);
        }
    }

    /**
     * A finalizer is required to ensure that the native object associated with this descriptor gets
     * torn down, otherwise there would be a memory leak.
     */
    @SuppressWarnings("Finalize")
    @Override
    protected void finalize() {
        destroy();
    }

    private void destroy() {
        if (mNativeQoraiSyncDevicesAndroid != 0) {
            QoraiSyncDevicesJni.get().destroy(mNativeQoraiSyncDevicesAndroid);
            mNativeQoraiSyncDevicesAndroid = 0;
        }
    }

    /**
     * Listener for the devices syncchain changes.
     */
    public interface DeviceInfoChangedListener {
        // Invoked when the device info has changed.
        public void deviceInfoChanged();
    }

    // Sync state changes more often than listeners are added/removed, so using CopyOnWrite.
    private final List<DeviceInfoChangedListener> mDeviceInfoListeners =
            new CopyOnWriteArrayList<DeviceInfoChangedListener>();

    public void addDeviceInfoChangedListener(DeviceInfoChangedListener listener) {
        ThreadUtils.assertOnUiThread();
        mDeviceInfoListeners.add(listener);
    }

    public void removeDeviceInfoChangedListener(DeviceInfoChangedListener listener) {
        ThreadUtils.assertOnUiThread();
        mDeviceInfoListeners.remove(listener);
    }

    /**
     * Called when the state of the native sync engine has changed, so various
     * UI elements can update themselves.
     */
    @CalledByNative
    protected void deviceInfoChanged() {
        for (DeviceInfoChangedListener listener : mDeviceInfoListeners) {
            listener.deviceInfoChanged();
        }
    }

    public static class SyncDeviceInfo {
        public String mName;
        public boolean mIsCurrentDevice;
        public boolean mSupportsSelfDelete;
        public String mType;
        public Date mLastUpdatedTimestamp;
        public String mGuid;
    }

    public ArrayList<SyncDeviceInfo> getSyncDeviceList() {
        ArrayList<SyncDeviceInfo> deviceList = new ArrayList<SyncDeviceInfo>();
        String json =
                QoraiSyncDevicesJni.get().getSyncDeviceListJson(mNativeQoraiSyncDevicesAndroid);
        // Add root element to make it real JSON, otherwise getJSONArray cannot parse it
        json = "{\"devices\":" + json + "}";
        try {
            JSONObject result = new JSONObject(json);
            JSONArray devices = result.getJSONArray("devices");
            Log.i(TAG, "getSyncDeviceList devices length is " + devices.length());
            for (int i = 0; i < devices.length(); i++) {
                SyncDeviceInfo deviceInfo = new SyncDeviceInfo();
                JSONObject device = devices.getJSONObject(i);
                deviceInfo.mName = device.getString("name");
                deviceInfo.mIsCurrentDevice = device.getBoolean("isCurrentDevice");
                deviceInfo.mType = device.getString("type");
                long lastUpdatedTimestamp = device.getLong("lastUpdatedTimestamp");
                deviceInfo.mLastUpdatedTimestamp = new Date(lastUpdatedTimestamp);
                deviceInfo.mGuid = device.getString("guid");
                deviceInfo.mSupportsSelfDelete = device.getBoolean("supportsSelfDelete");
                deviceList.add(deviceInfo);
            }
        } catch (JSONException e) {
            Log.e(TAG, "getSyncDeviceList JSONException error " + e);
        } catch (IllegalStateException e) {
            Log.e(TAG, "getSyncDeviceList IllegalStateException error " + e);
        }
        return deviceList;
    }

    public void deleteDevice(String deviceGuid) {
        QoraiSyncDevicesJni.get().deleteDevice(mNativeQoraiSyncDevicesAndroid, deviceGuid);
    }

    @NativeMethods
    interface Natives {
        void init(QoraiSyncDevices caller);
        void destroy(long nativeQoraiSyncDevicesAndroid);

        String getSyncDeviceListJson(long nativeQoraiSyncDevicesAndroid);
        void deleteDevice(long nativeQoraiSyncDevicesAndroid, String deviceGuid);
    }
}
