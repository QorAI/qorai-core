/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import static org.chromium.chrome.browser.settings.MainSettings.PREF_UI_THEME;

import android.os.Bundle;

import androidx.preference.Preference;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.base.ContextUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.qorai.browser.customize_menu.CustomizeQoraiMenu;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.QoraiFeatureUtil;
import org.chromium.chrome.browser.QoraiRelaunchUtils;
import org.chromium.chrome.browser.QoraiRewardsNativeWorker;
import org.chromium.chrome.browser.QoraiRewardsObserver;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.multiwindow.QoraiMultiWindowDialogFragment;
import org.chromium.chrome.browser.multiwindow.QoraiMultiWindowUtils;
import org.chromium.chrome.browser.multiwindow.MultiWindowUtils;
import org.chromium.chrome.browser.night_mode.NightModeUtils;
import org.chromium.chrome.browser.ntp.NtpUtil;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.tasks.tab_management.QoraiTabUiFeatureUtilities;
import org.chromium.chrome.browser.toolbar.ToolbarPositionController;
import org.chromium.chrome.browser.toolbar.adaptive.AdaptiveToolbarFeatures;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;
import org.chromium.chrome.browser.toolbar.settings.AddressBarSettingsFragment;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.ui.base.DeviceFormFactor;

public class AppearancePreferences extends QoraiPreferenceFragment
        implements Preference.OnPreferenceChangeListener, QoraiRewardsObserver {
    public static final String PREF_HIDE_QORAI_REWARDS_ICON = "hide_qorai_rewards_icon";
    public static final String PREF_HIDE_QORAI_REWARDS_ICON_MIGRATION =
            "hide_qorai_rewards_icon_migration";
    public static final String PREF_SHOW_QORAI_REWARDS_ICON = "show_qorai_rewards_icon";
    public static final String PREF_ADS_SWITCH = "ads_switch";
    public static final String PREF_QORAI_NIGHT_MODE_ENABLED = "qorai_night_mode_enabled_key";
    public static final String PREF_QORAI_DISABLE_SHARING_HUB = "qorai_disable_sharing_hub";
    public static final String PREF_QORAI_ENABLE_TAB_GROUPS = "qorai_enable_tab_groups";
    public static final String PREF_ENABLE_MULTI_WINDOWS = "enable_multi_windows";
    public static final String PREF_SHOW_UNDO_WHEN_TABS_CLOSED = "show_undo_when_tabs_closed";
    public static final String PREF_ADDRESS_BAR = "address_bar";
    public static final String PREF_TOOLBAR_SHORTCUT = "toolbar_shortcut";
    private static final String PREF_QORAI_CUSTOMIZE_MENU = "qorai_customize_menu";

    private QoraiRewardsNativeWorker mQoraiRewardsNativeWorker;

    private final ObservableSupplierImpl<String> mPageTitle = new ObservableSupplierImpl<>();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mPageTitle.set(getString(R.string.prefs_appearance));
        SettingsUtils.addPreferencesFromResource(this, R.xml.qorai_appearance_preferences);

        // Forward the custom menu item keys from appearance to custom menu item preference screen.
        CustomizeQoraiMenu.propagateMenuItemExtras(
                findPreference(PREF_QORAI_CUSTOMIZE_MENU), getArguments());

        boolean isTablet =
                DeviceFormFactor.isNonMultiDisplayContextOnTablet(
                        ContextUtils.getApplicationContext());
        if (isTablet) {
            removePreferenceIfPresent(QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY);
        }

        if (!NightModeUtils.isNightModeSupported()) {
            removePreferenceIfPresent(PREF_UI_THEME);
        }

        mQoraiRewardsNativeWorker = QoraiRewardsNativeWorker.getInstance();
        if (mQoraiRewardsNativeWorker == null || !mQoraiRewardsNativeWorker.isSupported()) {
            removePreferenceIfPresent(PREF_SHOW_QORAI_REWARDS_ICON);
        }

        if (!new QoraiMultiWindowUtils().shouldShowEnableWindow(getActivity())) {
            removePreferenceIfPresent(PREF_ENABLE_MULTI_WINDOWS);
        }

        if (!ToolbarPositionController.isToolbarPositionCustomizationEnabled(getContext(), false)) {
            removePreferenceIfPresent(PREF_ADDRESS_BAR);
        }

        if (!AdaptiveToolbarFeatures.isCustomizationEnabled()) {
            removePreferenceIfPresent(PREF_TOOLBAR_SHORTCUT);
        }
    }

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {}

    private void removePreferenceIfPresent(String key) {
        Preference preference = getPreferenceScreen().findPreference(key);
        if (preference != null) getPreferenceScreen().removePreference(preference);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        ChromeSwitchPreference showQoraiRewardsIconPref =
                (ChromeSwitchPreference) findPreference(PREF_SHOW_QORAI_REWARDS_ICON);
        if (showQoraiRewardsIconPref != null) {
            showQoraiRewardsIconPref.setChecked(NtpUtil.shouldShowRewardsIcon());
            showQoraiRewardsIconPref.setOnPreferenceChangeListener(this);
        }

        ChromeSwitchPreference adsSwitchPref =
                (ChromeSwitchPreference) findPreference(PREF_ADS_SWITCH);
        if (adsSwitchPref != null) {
            adsSwitchPref.setChecked(getPrefAdsInBackgroundEnabled());
            adsSwitchPref.setOnPreferenceChangeListener(this);
        }

        Preference nightModeEnabled = findPreference(PREF_QORAI_NIGHT_MODE_ENABLED);
        nightModeEnabled.setOnPreferenceChangeListener(this);
        if (nightModeEnabled instanceof ChromeSwitchPreference) {
            ((ChromeSwitchPreference) nightModeEnabled)
                    .setChecked(ChromeFeatureList.isEnabled(
                            QoraiFeatureList.FORCE_WEB_CONTENTS_DARK_MODE));
        }

        Preference enableBottomToolbar =
                findPreference(QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY);
        if (enableBottomToolbar != null) {
            enableBottomToolbar.setOnPreferenceChangeListener(this);
        }

        Preference disableSharingHub = findPreference(PREF_QORAI_DISABLE_SHARING_HUB);
        if (disableSharingHub != null) {
            disableSharingHub.setOnPreferenceChangeListener(this);
            if (disableSharingHub instanceof ChromeSwitchPreference) {
                ((ChromeSwitchPreference) disableSharingHub)
                        .setChecked(
                                ChromeSharedPreferences.getInstance()
                                        .readBoolean(
                                                QoraiPreferenceKeys.QORAI_DISABLE_SHARING_HUB,
                                                false));
            }
        }

        Preference enableTabGroups = findPreference(PREF_QORAI_ENABLE_TAB_GROUPS);
        if (enableTabGroups != null) {
            enableTabGroups.setOnPreferenceChangeListener(this);
            if (enableTabGroups instanceof ChromeSwitchPreference) {
                ((ChromeSwitchPreference) enableTabGroups)
                        .setChecked(QoraiTabUiFeatureUtilities.isQoraiTabGroupsEnabled());
            }
        }

        Preference enableMultiWindow = findPreference(PREF_ENABLE_MULTI_WINDOWS);
        if (enableMultiWindow != null) {
            enableMultiWindow.setOnPreferenceChangeListener(this);
            if (enableMultiWindow instanceof ChromeSwitchPreference) {
                ((ChromeSwitchPreference) enableMultiWindow)
                        .setChecked(QoraiMultiWindowUtils.shouldEnableMultiWindows());
            }
        }

        ChromeSwitchPreference showUndoButtonOnTabClosed =
                (ChromeSwitchPreference) findPreference(PREF_SHOW_UNDO_WHEN_TABS_CLOSED);
        if (showUndoButtonOnTabClosed != null) {
            showUndoButtonOnTabClosed.setOnPreferenceChangeListener(this);
            ((ChromeSwitchPreference) showUndoButtonOnTabClosed)
                    .setChecked(
                            ChromeSharedPreferences.getInstance()
                                    .readBoolean(
                                            QoraiPreferenceKeys.SHOW_UNDO_WHEN_TABS_CLOSED, true));
        }
    }

    @Override
    public ObservableSupplier<String> getPageTitle() {
        return mPageTitle;
    }

    @Override
    public void onStart() {
        if (mQoraiRewardsNativeWorker != null) {
            mQoraiRewardsNativeWorker.addObserver(this);
        }
        super.onStart();

        if (ToolbarPositionController.isToolbarPositionCustomizationEnabled(getContext(), false)) {
            updatePreferenceTitle(
                    PREF_ADDRESS_BAR, AddressBarSettingsFragment.getTitle(getContext()));
            updatePreferenceIcon(
                    PREF_ADDRESS_BAR,
                    BottomToolbarConfiguration.isToolbarTopAnchored()
                            ? R.drawable.ic_browser_mobile_tabs_top
                            : R.drawable.ic_browser_mobile_tabs_bottom);
        }

        Preference enableBottomToolbar =
                findPreference(QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY);
        if (enableBottomToolbar instanceof ChromeSwitchPreference) {
            if (BottomToolbarConfiguration.isToolbarTopAnchored()) {
                boolean isTablet =
                        DeviceFormFactor.isNonMultiDisplayContextOnTablet(
                                ContextUtils.getApplicationContext());
                ((ChromeSwitchPreference) enableBottomToolbar)
                        .setChecked(
                                !isTablet
                                        && BottomToolbarConfiguration
                                                .isQoraiBottomControlsEnabled());
            }
            if (BottomToolbarConfiguration.isToolbarBottomAnchored()) {
                updatePreferenceSummary(
                        QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY,
                        R.string.qorai_bottom_navigation_toolbar_disabled_summary);
            } else {
                updatePreferenceSummary(
                        QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY,
                        ((ChromeSwitchPreference) enableBottomToolbar).isChecked()
                                ? R.string.text_on
                                : R.string.text_off);
            }
            ((ChromeSwitchPreference) enableBottomToolbar)
                    .setEnabled(BottomToolbarConfiguration.isToolbarTopAnchored());
        }

        if (AdaptiveToolbarFeatures.isCustomizationEnabled()) {
            updatePreferenceIcon(
                    PREF_TOOLBAR_SHORTCUT, R.drawable.ic_browser_customizable_shortcut);
        }
    }

    @Override
    public void onStop() {
        if (mQoraiRewardsNativeWorker != null) {
            mQoraiRewardsNativeWorker.removeObserver(this);
        }
        super.onStop();
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        String key = preference.getKey();
        boolean shouldRelaunch = false;
        if (QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY.equals(key)) {
            Boolean originalStatus = BottomToolbarConfiguration.isQoraiBottomControlsEnabled();
            updatePreferenceSummary(
                    QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY,
                    !originalStatus ? R.string.text_on : R.string.text_off);
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(
                            QoraiPreferenceKeys.QORAI_BOTTOM_TOOLBAR_ENABLED_KEY, !originalStatus);
            shouldRelaunch = true;
        } else if (PREF_SHOW_QORAI_REWARDS_ICON.equals(key)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(PREF_SHOW_QORAI_REWARDS_ICON, !(boolean) newValue);
            shouldRelaunch = true;
        } else if (PREF_ADS_SWITCH.equals(key)) {
            setPrefAdsInBackgroundEnabled((boolean) newValue);
        } else if (PREF_QORAI_NIGHT_MODE_ENABLED.equals(key)) {
            QoraiFeatureUtil.enableFeature(
                    QoraiFeatureList.ENABLE_FORCE_DARK, (boolean) newValue, true);
            shouldRelaunch = true;
        } else if (PREF_QORAI_DISABLE_SHARING_HUB.equals(key)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(
                            QoraiPreferenceKeys.QORAI_DISABLE_SHARING_HUB, (boolean) newValue);
        } else if (PREF_QORAI_ENABLE_TAB_GROUPS.equals(key)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPreferenceKeys.QORAI_TAB_GROUPS_ENABLED, (boolean) newValue);
        } else if (PREF_ENABLE_MULTI_WINDOWS.equals(key)) {
            if (!(boolean) newValue) {
                if (MultiWindowUtils.getInstanceCount() > 1) {
                    QoraiMultiWindowDialogFragment dialogFragment =
                            QoraiMultiWindowDialogFragment.newInstance();
                    QoraiMultiWindowDialogFragment.DismissListener dismissListener =
                            new QoraiMultiWindowDialogFragment.DismissListener() {
                                @Override
                                public void onDismiss() {
                                    if (MultiWindowUtils.getInstanceCount() == 1) {
                                        if (preference instanceof ChromeSwitchPreference) {
                                            ((ChromeSwitchPreference) preference).setChecked(false);
                                            QoraiMultiWindowUtils.updateEnableMultiWindows(false);
                                        }
                                    }
                                }
                            };
                    dialogFragment.setDismissListener(dismissListener);

                    dialogFragment.show(
                            getActivity().getSupportFragmentManager(),
                            "QoraiMultiWindowDialogFragment");

                    return false;
                }
            }
            QoraiMultiWindowUtils.updateEnableMultiWindows((boolean) newValue);
        } else if (PREF_SHOW_UNDO_WHEN_TABS_CLOSED.equals(key)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(
                            QoraiPreferenceKeys.SHOW_UNDO_WHEN_TABS_CLOSED, (boolean) newValue);
        }
        if (shouldRelaunch) {
            QoraiRelaunchUtils.askForRelaunch(getActivity());
        }

        return true;
    }

    /** Returns the user preference for whether the qorai ads in background is enabled. */
    public static boolean getPrefAdsInBackgroundEnabled() {
        return ChromeSharedPreferences.getInstance().readBoolean(PREF_ADS_SWITCH, false);
    }

    /** Sets the user preference for whether the qorai ads in background is enabled. */
    public void setPrefAdsInBackgroundEnabled(boolean enabled) {
        ChromeSharedPreferences.getInstance().writeBoolean(PREF_ADS_SWITCH, enabled);
    }

    private void updatePreferenceIcon(String preferenceString, int drawable) {
        Preference preference = findPreference(preferenceString);
        if (preference != null) {
            preference.setIcon(drawable);
        }
    }

    private void updatePreferenceTitle(String preferenceString, CharSequence title) {
        Preference preference = findPreference(preferenceString);
        if (preference != null) {
            preference.setTitle(title);
        }
    }

    private void updatePreferenceSummary(String preferenceString, int summaryId) {
        Preference preference = findPreference(preferenceString);
        if (preference != null) {
            preference.setSummary(summaryId);
        }
    }
}
