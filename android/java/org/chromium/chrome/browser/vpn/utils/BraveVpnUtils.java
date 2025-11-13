/**
 * Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.vpn.utils;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.util.Pair;

import androidx.annotation.Nullable;
import androidx.fragment.app.FragmentActivity;

import com.wireguard.config.Config;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import org.chromium.base.ContextUtils;
import org.chromium.base.Log;
import org.chromium.qorai_vpn.mojom.QoraiVpnConstants;
import org.chromium.qorai_vpn.mojom.Region;
import org.chromium.chrome.browser.QoraiRewardsNativeWorker;
import org.chromium.chrome.browser.vpn.QoraiVpnNativeWorker;
import org.chromium.chrome.browser.vpn.activities.QoraiVpnProfileActivity;
import org.chromium.chrome.browser.vpn.activities.QoraiVpnSupportActivity;
import org.chromium.chrome.browser.vpn.activities.VpnAlwaysOnActivity;
import org.chromium.chrome.browser.vpn.activities.VpnPaywallActivity;
import org.chromium.chrome.browser.vpn.activities.VpnServerActivity;
import org.chromium.chrome.browser.vpn.activities.VpnServerSelectionActivity;
import org.chromium.chrome.browser.vpn.fragments.QoraiVpnAlwaysOnErrorDialogFragment;
import org.chromium.chrome.browser.vpn.fragments.QoraiVpnConfirmDialogFragment;
import org.chromium.chrome.browser.vpn.models.QoraiVpnServerRegion;
import org.chromium.chrome.browser.vpn.models.QoraiVpnWireguardProfileCredentials;
import org.chromium.chrome.browser.vpn.split_tunnel.SplitTunnelActivity;
import org.chromium.chrome.browser.vpn.wireguard.WireguardConfigUtils;
import org.chromium.gms.ChromiumPlayServicesAvailability;
import org.chromium.ui.widget.Toast;

import java.util.ArrayList;
import java.util.Locale;
import java.util.Random;

public class QoraiVpnUtils {
    private static final String TAG = "QoraiVPN";
    public static final String SUBSCRIPTION_PARAM_TEXT = "subscription";
    public static final String IAP_ANDROID_PARAM_TEXT = "iap-android";
    public static final String VERIFY_CREDENTIALS_FAILED = "verify_credentials_failed";
    public static final String DESKTOP_CREDENTIAL = "desktop_credential";

    public static boolean mUpdateProfileAfterSplitTunnel;
    public static QoraiVpnServerRegion selectedServerRegion;
    public static Region selectedRegion;
    public static Region selectedCity;
    private static ProgressDialog sProgressDialog;

    public static String IS_KILL_SWITCH = "is_kill_switch";
    public static String REGION = "region";

    public static void openQoraiVpnPlansActivity(@Nullable Context context) {
        if (context == null) {
            return;
        }
        Intent qoraiVpnPlanIntent = new Intent(context, VpnPaywallActivity.class);
        qoraiVpnPlanIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        qoraiVpnPlanIntent.setAction(Intent.ACTION_VIEW);
        context.startActivity(qoraiVpnPlanIntent);
    }

    public static void openQoraiVpnProfileActivity(Activity activity) {
        if (activity == null) {
            return;
        }
        Intent qoraiVpnProfileIntent = new Intent(activity, QoraiVpnProfileActivity.class);
        qoraiVpnProfileIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        qoraiVpnProfileIntent.setAction(Intent.ACTION_VIEW);
        activity.startActivity(qoraiVpnProfileIntent);
    }

    public static void openQoraiVpnSupportActivity(Activity activity) {
        if (activity == null) {
            return;
        }
        Intent qoraiVpnSupportIntent = new Intent(activity, QoraiVpnSupportActivity.class);
        qoraiVpnSupportIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        qoraiVpnSupportIntent.setAction(Intent.ACTION_VIEW);
        activity.startActivity(qoraiVpnSupportIntent);
    }

    public static void openSplitTunnelActivity(Activity activity) {
        if (activity == null) {
            return;
        }
        Intent qoraiVpnSupportIntent = new Intent(activity, SplitTunnelActivity.class);
        qoraiVpnSupportIntent.setAction(Intent.ACTION_VIEW);
        activity.startActivity(qoraiVpnSupportIntent);
    }

    public static void openAutoReconnectVpnActivity(Activity activity) {
        if (activity == null) {
            return;
        }
        Intent autoReconnectVpnActivityIntent = new Intent(activity, VpnAlwaysOnActivity.class);
        activity.startActivity(autoReconnectVpnActivityIntent);
    }

    public static void openVpnSettings(Activity activity) {
        if (activity == null) {
            return;
        }
        Intent vpnSettingsIntent = new Intent("android.net.vpn.SETTINGS");
        vpnSettingsIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        activity.startActivity(vpnSettingsIntent);
    }

    public static void openVpnServerSelectionActivity(@Nullable Context context) {
        if (context == null) {
            return;
        }
        Intent vpnServerSelectionIntent = new Intent(context, VpnServerSelectionActivity.class);
        context.startActivity(vpnServerSelectionIntent);
    }

    public static void openVpnServerActivity(Activity activity, Region region) {
        if (activity == null) {
            return;
        }
        Intent vpnServerIntent = new Intent(activity, VpnServerActivity.class);
        activity.startActivity(vpnServerIntent);
    }

    public static void showProgressDialog(Activity activity, String message) {
        sProgressDialog = ProgressDialog.show(activity, "", message, true);
    }

    public static void dismissProgressDialog() {
        if (sProgressDialog != null && sProgressDialog.isShowing()) {
            sProgressDialog.dismiss();
            sProgressDialog = null;
        }
    }

    public static QoraiVpnServerRegion getServerRegionForTimeZone(
            String jsonTimezones, String currentTimezone) {
        // Add root element to make it real JSON, otherwise getJSONArray cannot parse it
        jsonTimezones = "{\"regions\":" + jsonTimezones + "}";
        try {
            JSONObject result = new JSONObject(jsonTimezones);
            JSONArray regions = result.getJSONArray("regions");
            for (int i = 0; i < regions.length(); i++) {
                JSONObject region = regions.getJSONObject(i);
                JSONArray timezones = region.getJSONArray("timezones");
                for (int j = 0; j < timezones.length(); j++) {
                    if (timezones.getString(j).equals(currentTimezone)) {
                        String isoCode = region.getString("country-iso-code");
                        String country = new Locale("", isoCode).getDisplayCountry();
                        QoraiVpnServerRegion qoraiVpnServerRegion =
                                new QoraiVpnServerRegion(
                                        true,
                                        country,
                                        region.getString("continent"),
                                        isoCode,
                                        region.getString("name"),
                                        region.getString("name-pretty"),
                                        QoraiVpnConstants.REGION_PRECISION_COUNTRY);
                        return qoraiVpnServerRegion;
                    }
                }
            }
        } catch (JSONException e) {
            Log.e(TAG, "QoraiVpnUtils -> getRegionForTimeZone JSONException error " + e);
        }
        return null;
    }

    public static Pair<String, String> getHostnameForRegion(String jsonHostnames) {
        jsonHostnames = "{\"hostnames\":" + jsonHostnames + "}";
        try {
            JSONObject result = new JSONObject(jsonHostnames);
            JSONArray hostnames = result.getJSONArray("hostnames");
            ArrayList<JSONObject> hosts = new ArrayList<JSONObject>();
            for (int i = 0; i < hostnames.length(); i++) {
                JSONObject hostname = hostnames.getJSONObject(i);
                if (hostname.getInt("capacity-score") == 0
                        || hostname.getInt("capacity-score") == 1) {
                    hosts.add(hostname);
                }
            }

            JSONObject hostname;
            if (hosts.size() < 2) {
                hostname = hostnames.getJSONObject(new Random().nextInt(hostnames.length()));
            } else {
                hostname = hosts.get(new Random().nextInt(hosts.size()));
            }
            return new Pair<>(hostname.getString("hostname"), hostname.getString("display-name"));
        } catch (JSONException e) {
            Log.e(TAG, "QoraiVpnUtils -> getHostnameForRegion JSONException error " + e);
        }
        return new Pair<String, String>("", "");
    }

    public static QoraiVpnWireguardProfileCredentials getWireguardProfileCredentials(
            String jsonWireguardProfileCredentials) {
        try {
            JSONObject wireguardProfileCredentials =
                    new JSONObject(jsonWireguardProfileCredentials);
            QoraiVpnWireguardProfileCredentials qoraiVpnWireguardProfileCredentials =
                    new QoraiVpnWireguardProfileCredentials(
                            wireguardProfileCredentials.getString("api-auth-token"),
                            wireguardProfileCredentials.getString("client-id"),
                            wireguardProfileCredentials.getString("mapped-ipv4-address"),
                            wireguardProfileCredentials.getString("mapped-ipv6-address"),
                            wireguardProfileCredentials.getString("server-public-key"));
            return qoraiVpnWireguardProfileCredentials;
        } catch (JSONException e) {
            Log.e(TAG, "QoraiVpnUtils -> getWireguardProfileCredentials JSONException error " + e);
        }
        return null;
    }

    public static Long getPurchaseExpiryDate(String json) {
        try {
            JSONObject purchase = new JSONObject(json);
            String expiryTimeInString = purchase.getString("expiryTimeMillis");
            return Long.parseLong(expiryTimeInString);
        } catch (JSONException | NumberFormatException e) {
            Log.e(
                    TAG,
                    "QoraiVpnUtils -> getPurchaseExpiryDate JSONException | NumberFormatException"
                            + " error "
                            + e);
        }
        return 0L;
    }

    public static int getPaymentState(String json) {
        try {
            JSONObject purchase = new JSONObject(json);
            int paymentState = purchase.getInt("paymentState");
            return paymentState;
        } catch (JSONException e) {
            Log.e(TAG, "QoraiVpnUtils -> getPaymentState JSONException error " + e);
        }
        return 0;
    }

    public static void resetProfileConfiguration(Activity activity) {
        if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(activity)) {
            QoraiVpnProfileUtils.getInstance().stopVpn(activity);
        }
        try {
            WireguardConfigUtils.deleteConfig(activity);
        } catch (Exception ex) {
            Log.e(TAG, "resetProfileConfiguration : " + ex.getMessage());
        }
        QoraiVpnPrefUtils.setResetConfiguration(true);
        dismissProgressDialog();
    }

    public static void updateProfileConfiguration(Activity activity) {
        try {
            Config existingConfig = WireguardConfigUtils.loadConfig(activity);
            WireguardConfigUtils.deleteConfig(activity);
            WireguardConfigUtils.createConfig(activity, existingConfig);
        } catch (Exception ex) {
            Log.e(TAG, "updateProfileConfiguration : " + ex.getMessage());
        }
        if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(activity)) {
            QoraiVpnProfileUtils.getInstance().stopVpn(activity);
            QoraiVpnProfileUtils.getInstance().startVpn(activity);
        }
        dismissProgressDialog();
    }

    public static void showVpnAlwaysOnErrorDialog(Activity activity) {
        QoraiVpnAlwaysOnErrorDialogFragment mQoraiVpnAlwaysOnErrorDialogFragment =
                new QoraiVpnAlwaysOnErrorDialogFragment();
        mQoraiVpnAlwaysOnErrorDialogFragment.show(
                ((FragmentActivity) activity).getSupportFragmentManager(),
                "QoraiVpnAlwaysOnErrorDialogFragment");
    }

    public static void showVpnConfirmDialog(Activity activity) {
        QoraiVpnConfirmDialogFragment qoraiVpnConfirmDialogFragment =
                new QoraiVpnConfirmDialogFragment();
        qoraiVpnConfirmDialogFragment.show(
                ((FragmentActivity) activity).getSupportFragmentManager(),
                "QoraiVpnConfirmDialogFragment");
    }

    public static void reportBackgroundUsageP3A() {
        // Will report previous/current session timestamps...
        QoraiVpnNativeWorker.getInstance().reportBackgroundP3A(
                QoraiVpnPrefUtils.getSessionStartTimeMs(), QoraiVpnPrefUtils.getSessionEndTimeMs());
        // ...and then reset the timestamps so we don't report the same session again.
        QoraiVpnPrefUtils.setSessionStartTimeMs(-1);
        QoraiVpnPrefUtils.setSessionEndTimeMs(-1);
    }

    public static void showToast(String message) {
        Context context = ContextUtils.getApplicationContext();
        Toast.makeText(context, message, Toast.LENGTH_SHORT).show();
    }

    private static boolean isRegionSupported() {
        QoraiRewardsNativeWorker qoraiRewardsNativeWorker = QoraiRewardsNativeWorker.getInstance();
        return (qoraiRewardsNativeWorker != null && qoraiRewardsNativeWorker.isSupported());
    }

    public static boolean isVpnFeatureSupported(Context context) {
        return isRegionSupported()
                && ChromiumPlayServicesAvailability.isGooglePlayServicesAvailable(context);
    }

    public static String countryCodeToEmoji(String countryCode) {
        int firstLetter = Character.codePointAt(countryCode, 0) - 0x41 + 0x1F1E6;
        int secondLetter = Character.codePointAt(countryCode, 1) - 0x41 + 0x1F1E6;
        return new String(Character.toChars(firstLetter))
                + new String(Character.toChars(secondLetter));
    }
}
