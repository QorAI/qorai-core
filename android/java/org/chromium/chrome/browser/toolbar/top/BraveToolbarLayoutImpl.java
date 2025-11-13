/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.top;

import static org.chromium.ui.base.ViewUtils.dpToPx;

import android.animation.Animator;
import android.animation.ObjectAnimator;
import android.app.Activity;
import android.content.Context;
import android.content.res.ColorStateList;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.content.ContextCompat;
import androidx.core.content.res.ResourcesCompat;
import androidx.core.widget.ImageViewCompat;

import com.qorai.playlist.enums.PlaylistOptionsEnum;
import com.qorai.playlist.listener.PlaylistOnboardingActionClickListener;
import com.qorai.playlist.listener.PlaylistOptionsListener;
import com.qorai.playlist.model.PlaylistOptionsModel;
import com.qorai.playlist.model.SnackBarActionModel;
import com.qorai.playlist.util.ConstantUtils;
import com.qorai.playlist.util.PlaylistViewUtils;

import org.chromium.base.ApiCompatibilityUtils;
import org.chromium.base.QoraiFeatureList;
import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.base.QoraiReflectionUtil;
import org.chromium.base.Log;
import org.chromium.base.MathUtils;
import org.chromium.base.ThreadUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.task.AsyncTask;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.QoraiRewardsHelper;
import org.chromium.chrome.browser.QoraiRewardsNativeWorker;
import org.chromium.chrome.browser.QoraiRewardsObserver;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.qorai_stats.QoraiStatsUtil;
import org.chromium.chrome.browser.crypto_wallet.controller.DAppsWalletController;
import org.chromium.chrome.browser.custom_layout.popup_window_tooltip.PopupWindowTooltip;
import org.chromium.chrome.browser.customtabs.FullScreenCustomTabActivity;
import org.chromium.chrome.browser.customtabs.features.toolbar.CustomTabToolbar;
import org.chromium.chrome.browser.dialogs.QoraiAdsSignupDialog;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.local_database.QoraiStatsTable;
import org.chromium.chrome.browser.local_database.DatabaseHelper;
import org.chromium.chrome.browser.local_database.SavedBandwidthTable;
import org.chromium.chrome.browser.media.PictureInPicture;
import org.chromium.chrome.browser.ntp.NtpUtil;
import org.chromium.chrome.browser.omnibox.QoraiLocationBarCoordinator;
import org.chromium.chrome.browser.omnibox.LocationBarCoordinator;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.chrome.browser.onboarding.v2.HighlightItem;
import org.chromium.chrome.browser.onboarding.v2.HighlightView;
import org.chromium.chrome.browser.playlist.PlaylistServiceFactoryAndroid;
import org.chromium.chrome.browser.playlist.PlaylistServiceObserverImpl;
import org.chromium.chrome.browser.playlist.PlaylistServiceObserverImpl.PlaylistServiceObserverImplDelegate;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.preferences.website.QoraiShieldsContentSettings;
import org.chromium.chrome.browser.preferences.website.QoraiShieldsContentSettingsObserver;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.shields.QoraiShieldsHandler;
import org.chromium.chrome.browser.shields.QoraiShieldsMenuObserver;
import org.chromium.chrome.browser.shields.QoraiShieldsUtils;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabHidingType;
import org.chromium.chrome.browser.tab.TabSelectionType;
import org.chromium.chrome.browser.tabmodel.IncognitoStateProvider;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorTabModelObserver;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorTabObserver;
import org.chromium.chrome.browser.theme.ThemeColorProvider;
import org.chromium.chrome.browser.theme.ThemeUtils;
import org.chromium.chrome.browser.toolbar.ToolbarDataProvider;
import org.chromium.chrome.browser.toolbar.ToolbarProgressBar;
import org.chromium.chrome.browser.toolbar.ToolbarTabController;
import org.chromium.chrome.browser.toolbar.back_button.BackButtonCoordinator;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarVariationManager;
import org.chromium.chrome.browser.toolbar.extensions.ExtensionToolbarCoordinator;
import org.chromium.chrome.browser.toolbar.forward_button.ForwardButtonCoordinator;
import org.chromium.chrome.browser.toolbar.home_button.HomeButton;
import org.chromium.chrome.browser.toolbar.menu_button.QoraiMenuButtonCoordinator;
import org.chromium.chrome.browser.toolbar.menu_button.MenuButtonCoordinator;
import org.chromium.chrome.browser.toolbar.reload_button.ReloadButtonCoordinator;
import org.chromium.chrome.browser.toolbar.top.NavigationPopup.HistoryDelegate;
import org.chromium.chrome.browser.user_education.UserEducationHelper;
import org.chromium.chrome.browser.util.QoraiConstants;
import org.chromium.chrome.browser.util.QoraiTouchUtils;
import org.chromium.chrome.browser.util.PackageUtils;
import org.chromium.chrome.browser.youtube_script_injector.QoraiYouTubeScriptInjectorNativeHelper;
import org.chromium.components.embedder_support.util.UrlUtilities;
import org.chromium.components.feature_engagement.Tracker;
import org.chromium.content_public.browser.NavigationHandle;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;
import org.chromium.playlist.mojom.PlaylistItem;
import org.chromium.playlist.mojom.PlaylistService;
import org.chromium.ui.UiUtils;
import org.chromium.ui.base.DeviceFormFactor;
import org.chromium.ui.base.ViewUtils;
import org.chromium.ui.interpolators.Interpolators;
import org.chromium.ui.resources.dynamics.ViewResourceAdapter;
import org.chromium.ui.util.ColorUtils;
import org.chromium.ui.widget.Toast;
import org.chromium.url.GURL;
import org.chromium.url.mojom.Url;

import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;

public abstract class QoraiToolbarLayoutImpl extends ToolbarLayout
        implements QoraiToolbarLayout,
                OnClickListener,
                View.OnLongClickListener,
                QoraiRewardsObserver,
                QoraiRewardsNativeWorker.PublisherObserver,
                ConnectionErrorHandler,
                PlaylistServiceObserverImplDelegate {
    private static final String TAG = "QoraiToolbar";

    private static final String PREF_WAS_TOOLBAR_QOR_LOGO_BUTTON_PRESSED =
            "was_toolbar_bat_logo_button_pressed";

    private static final int URL_FOCUS_TOOLBAR_BUTTONS_TRANSLATION_X_DP = 10;

    private static final int DAYS_7 = 7;
    public static boolean mShouldShowPlaylistMenu;

    private PlaylistServiceObserverImpl mPlaylistServiceObserver;

    private final DatabaseHelper mDatabaseHelper = DatabaseHelper.getInstance();

    private ImageButton mQoraiWalletButton;
    private ImageButton mQoraiShieldsButton;
    private ImageButton mQoraiRewardsButton;
    private ImageButton mYouTubePipButton;
    private HomeButton mHomeButton;
    private FrameLayout mWalletLayout;
    private FrameLayout mShieldsLayout;
    private FrameLayout mRewardsLayout;
    private FrameLayout mYouTubePipLayout;
    private QoraiShieldsHandler mQoraiShieldsHandler;

    // TabModelSelectorTabObserver setups observer at the ctor
    @SuppressWarnings("UnusedVariable")
    private TabModelSelectorTabObserver mTabModelSelectorTabObserver;

    // TabModelSelectorTabModelObserver setups observer at the ctor
    @SuppressWarnings("UnusedVariable")
    private TabModelSelectorTabModelObserver mTabModelSelectorTabModelObserver;

    private QoraiRewardsNativeWorker mQoraiRewardsNativeWorker;
    private DAppsWalletController mDAppsWalletController;
    private QoraiShieldsContentSettings mQoraiShieldsContentSettings;
    private QoraiShieldsContentSettingsObserver mQoraiShieldsContentSettingsObserver;
    private TextView mQoraiRewardsNotificationsCount;
    private ImageView mQoraiRewardsOnboardingIcon;
    private View mQoraiWalletBadge;
    private ImageView mWalletIcon;
    private int mCurrentToolbarColor;

    @Nullable private final Runnable mToolbarSnapshotCaptureRunnable;

    private boolean mIsPublisherVerified;
    private String mPublisherId;
    private boolean mIsNotificationPosted;
    private boolean mIsInitialNotificationPosted; // initial red circle notification

    private PopupWindowTooltip mShieldsPopupWindowTooltip;

    private boolean mIsBottomControlsVisible;

    private ColorStateList mDarkModeTint;
    private ColorStateList mLightModeTint;

    private final Set<Integer> mTabsWithWalletIcon =
            Collections.synchronizedSet(new HashSet<Integer>());

    private PlaylistService mPlaylistService;

    private enum BigtechCompany {
        Google,
        Facebook,
        Amazon
    }

    public QoraiToolbarLayoutImpl(Context context, AttributeSet attrs) {
        super(context, attrs);

        if (DeviceFormFactor.isNonMultiDisplayContextOnTablet(getContext())) {
            mToolbarSnapshotCaptureRunnable = this::requestToolbarSnapshotCapture;
        } else {
            mToolbarSnapshotCaptureRunnable = null;
        }
    }

    @Override
    protected void onDetachedFromWindow() {
        removeCallbacks(mToolbarSnapshotCaptureRunnable);
        super.onDetachedFromWindow();
    }

    @Override
    public void destroy() {
        if (mQoraiShieldsContentSettings != null) {
            mQoraiShieldsContentSettings.removeObserver(mQoraiShieldsContentSettingsObserver);
        }
        if (mPlaylistService != null) {
            mPlaylistService.close();
        }
        if (mPlaylistServiceObserver != null) {
            mPlaylistServiceObserver.close();
            mPlaylistServiceObserver.destroy();
            mPlaylistServiceObserver = null;
        }
        super.destroy();
        if (mQoraiRewardsNativeWorker != null) {
            mQoraiRewardsNativeWorker.removeObserver(this);
            mQoraiRewardsNativeWorker.removePublisherObserver(this);
        }
    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();

        if (QoraiReflectionUtil.equalTypes(this.getClass(), ToolbarTablet.class)) {
            ImageButton forwardButton = findViewById(R.id.forward_button);
            if (forwardButton != null) {
                final Drawable forwardButtonDrawable =
                        UiUtils.getTintedDrawable(
                                getContext(),
                                R.drawable.btn_right_tablet,
                                R.color.default_icon_color_tint_list);
                forwardButton.setImageDrawable(forwardButtonDrawable);
            }
        }

        mWalletLayout = findViewById(R.id.qorai_wallet_button_layout);
        mShieldsLayout = findViewById(R.id.qorai_shields_button_layout);
        mRewardsLayout = findViewById(R.id.qorai_rewards_button_layout);
        mYouTubePipLayout = findViewById(R.id.qorai_youtube_pip_layout);
        mQoraiRewardsNotificationsCount = findViewById(R.id.br_notifications_count);
        mQoraiRewardsOnboardingIcon = findViewById(R.id.br_rewards_onboarding_icon);
        mQoraiWalletButton = findViewById(R.id.qorai_wallet_button);
        mQoraiShieldsButton = findViewById(R.id.qorai_shields_button);
        mQoraiRewardsButton = findViewById(R.id.qorai_rewards_button);
        mYouTubePipButton = findViewById(R.id.qorai_youtube_pip_button);
        mHomeButton = findViewById(R.id.home_button);
        mQoraiWalletBadge = findViewById(R.id.wallet_notfication_badge);
        if (mWalletLayout != null) {
            mWalletIcon = mWalletLayout.findViewById(R.id.qorai_wallet_button);
        }

        mDarkModeTint = ThemeUtils.getThemedToolbarIconTint(getContext(), false);
        mLightModeTint =
                ColorStateList.valueOf(ContextCompat.getColor(getContext(), R.color.qorai_white));

        if (mHomeButton != null) {
            mHomeButton.setOnLongClickListener(this);
        }

        if (mQoraiShieldsButton != null) {
            mQoraiShieldsButton.setClickable(true);
            mQoraiShieldsButton.setOnClickListener(this);
            mQoraiShieldsButton.setOnLongClickListener(this);
            QoraiTouchUtils.ensureMinTouchTarget(mQoraiShieldsButton);
        }

        if (mQoraiRewardsButton != null) {
            mQoraiRewardsButton.setClickable(true);
            mQoraiRewardsButton.setOnClickListener(this);
            mQoraiRewardsButton.setOnLongClickListener(this);
            QoraiTouchUtils.ensureMinTouchTarget(mQoraiRewardsButton);
        }

        if (mQoraiWalletButton != null) {
            mQoraiWalletButton.setClickable(true);
            mQoraiWalletButton.setOnClickListener(this);
            mQoraiWalletButton.setOnLongClickListener(this);
            QoraiTouchUtils.ensureMinTouchTarget(mQoraiWalletButton);
        }

        if (mYouTubePipButton != null) {
            mYouTubePipButton.setClickable(true);
            mYouTubePipButton.setOnClickListener(this);
            mYouTubePipButton.setOnLongClickListener(this);
            QoraiTouchUtils.ensureMinTouchTarget(mYouTubePipButton);
        }

        mQoraiShieldsHandler = new QoraiShieldsHandler(getContext());
        mQoraiShieldsHandler.addObserver(
                new QoraiShieldsMenuObserver() {
                    @Override
                    public void onMenuTopShieldsChanged(boolean isOn, boolean isTopShield) {
                        Tab currentTab = getToolbarDataProvider().getTab();
                        if (currentTab == null) {
                            return;
                        }
                        if (isTopShield) {
                            updateQoraiShieldsButtonState(currentTab);
                        }
                        if (currentTab.isLoading()) {
                            currentTab.stopLoading();
                        }
                        currentTab.reloadIgnoringCache();
                        if (null != mQoraiShieldsHandler) {
                            // Clean the Qorairy Panel
                            mQoraiShieldsHandler.updateValues(0, 0, 0);
                        }
                    }
                });
        mQoraiShieldsContentSettingsObserver = new QoraiShieldsContentSettingsObserver() {
            @Override
            public void blockEvent(int tabId, String blockType, String subresource) {
                mQoraiShieldsHandler.addStat(tabId, blockType, subresource);
                Tab currentTab = getToolbarDataProvider().getTab();
                if (currentTab == null || currentTab.getId() != tabId) {
                    return;
                }
                mQoraiShieldsHandler.updateValues(tabId);
                if (!isIncognito() && OnboardingPrefManager.getInstance().isQoraiStatsEnabled()
                        && (blockType.equals(QoraiShieldsContentSettings.RESOURCE_IDENTIFIER_ADS)
                                || blockType.equals(QoraiShieldsContentSettings
                                                            .RESOURCE_IDENTIFIER_TRACKERS))) {
                    addStatsToDb(blockType, subresource, currentTab.getUrl().getSpec());
                }
            }

            @Override
            public void savedBandwidth(long savings) {
                if (!isIncognito() && OnboardingPrefManager.getInstance().isQoraiStatsEnabled()) {
                    addSavedBandwidthToDb(savings);
                }
            }
        };
        // Initially show shields off image. Shields button state will be updated when tab is
        // shown and loading state is changed.
        updateQoraiShieldsButtonState(null);
        if (QoraiReflectionUtil.equalTypes(this.getClass(), ToolbarPhone.class)) {
            if (getMenuButtonCoordinator() != null
                    && isMenuButtonOnBottomControls()
                    && BottomToolbarConfiguration.isToolbarTopAnchored()) {
                getMenuButtonCoordinator().setVisibility(false);
            }
        }

        if (QoraiReflectionUtil.equalTypes(this.getClass(), CustomTabToolbar.class)) {
            LinearLayout customActionButtons = findViewById(R.id.action_buttons);
            assert customActionButtons != null : "Something has changed in the upstream!";
            if (customActionButtons != null && mQoraiShieldsButton != null) {
                ViewGroup.MarginLayoutParams qoraiShieldsButtonLayout =
                        (ViewGroup.MarginLayoutParams) mQoraiShieldsButton.getLayoutParams();
                ViewGroup.MarginLayoutParams actionButtonsLayout =
                        (ViewGroup.MarginLayoutParams) customActionButtons.getLayoutParams();
                actionButtonsLayout.setMarginEnd(actionButtonsLayout.getMarginEnd()
                        + qoraiShieldsButtonLayout.getMarginEnd());
                customActionButtons.setLayoutParams(actionButtonsLayout);
            }
        }
        updateShieldsLayoutBackground(isIncognito() || !NtpUtil.shouldShowRewardsIcon());
    }

    public String getLocationBarQuery() {
        if (getLocationBar() instanceof QoraiLocationBarCoordinator) {
            String query =
                    ((QoraiLocationBarCoordinator) getLocationBar())
                            .getUrlBarTextWithoutAutocomplete();
            return query;
        }
        return "";
    }

    public void clearOmniboxFocus() {
        if (getLocationBar() instanceof QoraiLocationBarCoordinator) {
            ((QoraiLocationBarCoordinator) getLocationBar()).clearOmniboxFocus();
        }
    }

    public boolean isUrlBarFocused() {
        if (getLocationBar() instanceof QoraiLocationBarCoordinator) {
            return ((QoraiLocationBarCoordinator) getLocationBar()).isUrlBarFocused();
        }
        return false;
    }

    @Override
    public void onConnectionError(MojoException e) {
        if (isPlaylistEnabledByPrefsAndFlags()) {
            mPlaylistService = null;
            initPlaylistService();
        }
    }

    private void initPlaylistService() {
        Tab currentTab = getToolbarDataProvider().getTab();
        if (mPlaylistService != null || currentTab == null) {
            return;
        }

        if (currentTab.isIncognito()) {
            return;
        }

        mPlaylistService =
                PlaylistServiceFactoryAndroid.getInstance()
                        .getPlaylistService(
                                Profile.fromWebContents(currentTab.getWebContents()), this);
    }

    @Override
    public void onTermsOfServiceUpdateAccepted() {
        showOrHideRewardsBadge(false);
    }

    private void showOrHideRewardsBadge(boolean shouldShow) {
        Context context = getContext();
        if (context instanceof Activity
                && (((Activity) context).isFinishing() || ((Activity) context).isDestroyed())) {
            return;
        }
        View rewardsBadge = findViewById(R.id.rewards_notfication_badge);
        if (rewardsBadge != null) {
            rewardsBadge.setVisibility(shouldShow ? View.VISIBLE : View.GONE);
        }
    }

    @Override
    protected void onNativeLibraryReady() {
        super.onNativeLibraryReady();
        if (isPlaylistEnabledByPrefsAndFlags()) {
            initPlaylistService();
            mPlaylistServiceObserver = new PlaylistServiceObserverImpl(this);
            mPlaylistService.addObserver(mPlaylistServiceObserver);
        }

        mQoraiShieldsContentSettings = QoraiShieldsContentSettings.getInstance();
        mQoraiShieldsContentSettings.addObserver(mQoraiShieldsContentSettingsObserver);

        mQoraiRewardsNativeWorker = QoraiRewardsNativeWorker.getInstance();
        if (mQoraiRewardsNativeWorker != null
                && mQoraiRewardsNativeWorker.isSupported()
                && NtpUtil.shouldShowRewardsIcon()
                && mRewardsLayout != null) {
            mRewardsLayout.setVisibility(View.VISIBLE);
        }
        if (mQoraiRewardsNativeWorker != null
                && mQoraiRewardsNativeWorker.isRewardsEnabled()
                && mQoraiRewardsNativeWorker.isSupported()
                && mQoraiRewardsNativeWorker.isTermsOfServiceUpdateRequired()) {
            showOrHideRewardsBadge(true);
        }
        if (mShieldsLayout != null) {
            updateShieldsLayoutBackground(
                    !(mRewardsLayout != null && mRewardsLayout.getVisibility() == View.VISIBLE));
            mShieldsLayout.setVisibility(View.VISIBLE);
        }
        if (mQoraiRewardsNativeWorker != null) {
            mQoraiRewardsNativeWorker.addObserver(this);
            mQoraiRewardsNativeWorker.addPublisherObserver(this);
            mQoraiRewardsNativeWorker.getAllNotifications();
        }
    }

    public void setTabModelSelector(TabModelSelector selector) {
        // We might miss events before calling setTabModelSelector, so we need
        // to proactively update the shields button state here, otherwise shields
        // might sometimes show as disabled while it is actually enabled.
        updateQoraiShieldsButtonState(getToolbarDataProvider().getTab());
        mTabModelSelectorTabObserver =
                new TabModelSelectorTabObserver(selector) {
                    @Override
                    protected void onTabRegistered(Tab tab) {
                        super.onTabRegistered(tab);
                        if (tab.isIncognito()) {
                            showWalletIcon(false);
                        }
                    }

                    @Override
                    public void onCrash(Tab tab) {
                        super.onCrash(tab);
                        // When a tab crashes it shows a custom view with a reload button.
                        // The PIP layout must be hidden.
                        hideYouTubePipIcon();
                    }

                    @Override
                    public void onShown(Tab tab, @TabSelectionType int type) {
                        if (!PictureInPicture.isEnabled(getContext())) {
                            hideYouTubePipIcon();
                        }
                        // Update shields button state when visible tab is changed.
                        updateQoraiShieldsButtonState(tab);
                        // case when window.open is triggered from dapps site and new tab is in
                        // focus
                        if (type != TabSelectionType.FROM_USER) {
                            dismissWalletPanelOrDialog();
                        }
                        findMediaFiles();
                    }

                    @Override
                    public void onHidden(Tab tab, @TabHidingType int reason) {
                        hidePlaylistButton();
                    }

                    @Override
                    public void onPageLoadStarted(Tab tab, GURL url) {
                        hideYouTubePipIcon();
                        showWalletIcon(false, tab);
                        if (getToolbarDataProvider().getTab() == tab) {
                            updateQoraiShieldsButtonState(tab);
                        }
                        mQoraiShieldsHandler.clearQoraiShieldsCount(tab.getId());
                        dismissShieldsTooltip();
                        hidePlaylistButton();
                        mPublisherId = "";
                    }

                    @Override
                    public void onPageLoadFinished(final Tab tab, GURL url) {
                        if (getToolbarDataProvider().getTab() == tab) {
                            mQoraiShieldsHandler.updateUrlSpec(url.getSpec());
                            updateQoraiShieldsButtonState(tab);

                            if (mQoraiShieldsButton != null
                                    && mQoraiShieldsButton.isShown()
                                    && mQoraiShieldsHandler != null
                                    && !mQoraiShieldsHandler.isShowing()) {
                                checkForTooltip(tab);
                            }
                        }

                        String countryCode = Locale.getDefault().getCountry();
                        if (countryCode.equals(QoraiConstants.INDIA_COUNTRY_CODE)
                                && url.domainIs(QoraiConstants.YOUTUBE_DOMAIN)
                                && ChromeSharedPreferences.getInstance()
                                        .readBoolean(
                                                QoraiPreferenceKeys.QORAI_AD_FREE_CALLOUT_DIALOG,
                                                true)) {
                            ChromeSharedPreferences.getInstance()
                                    .writeBoolean(QoraiPreferenceKeys.QORAI_OPENED_YOUTUBE, true);
                        }
                    }

                    @Override
                    public void onDidFinishNavigationInPrimaryMainFrame(
                            Tab tab, NavigationHandle navigation) {
                        if (navigation.isInPrimaryMainFrame() && navigation.hasCommitted()) {
                            showYouTubePipIcon(tab);
                        } else {
                            hideYouTubePipIcon();
                        }
                        if (mQoraiRewardsNativeWorker != null) {
                            mQoraiRewardsNativeWorker.triggerOnNotifyFrontTabUrlChanged();
                        }
                        if (getToolbarDataProvider().getTab() == tab
                                && mQoraiRewardsNativeWorker != null
                                && !tab.isIncognito()) {
                            mQoraiRewardsNativeWorker.onNotifyFrontTabUrlChanged(
                                    tab.getId(), tab.getUrl().getSpec());
                        }
                        hidePlaylistButton();
                    }

                    @Override
                    public void onDestroyed(Tab tab) {
                        // Remove references for the ads from the Database. Tab is destroyed, they
                        // are not
                        // needed anymore.
                        new Thread() {
                            @Override
                            public void run() {
                                mDatabaseHelper.deleteDisplayAdsFromTab(tab.getId());
                            }
                        }.start();
                        mQoraiShieldsHandler.removeStat(tab.getId());
                        mTabsWithWalletIcon.remove(tab.getId());
                    }
                };

        mTabModelSelectorTabModelObserver =
                new TabModelSelectorTabModelObserver(selector) {
                    @Override
                    public void didSelectTab(Tab tab, @TabSelectionType int type, int lastId) {
                        showYouTubePipIcon(tab);
                        if (mQoraiRewardsNativeWorker != null && !tab.isIncognito()) {
                            mQoraiRewardsNativeWorker.onNotifyFrontTabUrlChanged(
                                    tab.getId(), tab.getUrl().getSpec());
                            Tab providerTab = getToolbarDataProvider().getTab();
                            if (providerTab != null && providerTab.getId() == tab.getId()) {
                                showWalletIcon(mTabsWithWalletIcon.contains(tab.getId()));
                            } else if (mWalletLayout != null) {
                                mWalletLayout.setVisibility(
                                        mTabsWithWalletIcon.contains(tab.getId())
                                                ? View.VISIBLE
                                                : View.GONE);
                            }
                        }
                    }
                };
    }

    private void showYouTubePipIcon(@NonNull final Tab tab) {
        // The layout could be null in Custom Tabs layout.
        if (mYouTubePipLayout == null) {
            return;
        }

        // Return early if picture in picture is not supported
        // or disabled in the OS settings.
        if (!PictureInPicture.isEnabled(getContext())) {
            if (mYouTubePipLayout.getVisibility() != View.GONE) {
                mYouTubePipLayout.setVisibility(View.GONE);
                invalidateToolbarSnapshotOnTablet();
            }
            return;
        }

        // Hide the layout if the current tab is in a state where it doesn't support or allow PiP
        // mode. This can also happen when a tab is re-selected after a crash and it's showing
        // the crash custom view, or is in a frozen state (likely inactive or unloaded).
        final boolean available =
                QoraiYouTubeScriptInjectorNativeHelper.isPictureInPictureAvailable(
                        tab.getWebContents());
        final int newVisibility = available ? View.VISIBLE : View.GONE;
        if (mYouTubePipLayout.getVisibility() != newVisibility) {
            mYouTubePipLayout.setVisibility(newVisibility);
            invalidateToolbarSnapshotOnTablet();
        }
    }

    private void hideYouTubePipIcon() {
        // The layout could be null in Custom Tabs layout.
        if (mYouTubePipLayout == null) {
            return;
        }
        if (mYouTubePipLayout.getVisibility() != View.GONE) {
            mYouTubePipLayout.setVisibility(View.GONE);
            invalidateToolbarSnapshotOnTablet();
        }
    }

    /**
     * Invalidates old toolbar bitmap snapshot on tablets, so when scrolling it will be shown the
     * right toolbar preview containing the visibility of the icons.
     */
    private void invalidateToolbarSnapshotOnTablet() {
        // mToolbarSnapshotCaptureRunnable is available on tablets only.
        if (!isAttachedToWindow() || mToolbarSnapshotCaptureRunnable == null) {
            return;
        }

        removeCallbacks(mToolbarSnapshotCaptureRunnable);
        post(mToolbarSnapshotCaptureRunnable);
    }

    private void requestToolbarSnapshotCapture() {
        final ToolbarControlContainer toolbarControlContainer =
                getRootView().findViewById(R.id.control_container);
        if (toolbarControlContainer == null) {
            return;
        }

        final ViewResourceAdapter adapter = toolbarControlContainer.getToolbarResourceAdapter();
        if (adapter == null) {
            return;
        }
        adapter.invalidate(null);
        adapter.triggerBitmapCapture();
    }

    private boolean isPlaylistEnabledByPrefsAndFlags() {
        Tab currentTab = getToolbarDataProvider().getTab();
        if (currentTab == null) {
            return false;
        }
        return ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_PLAYLIST)
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.PREF_ENABLE_PLAYLIST, true)
                && !currentTab.isIncognito();
    }

    private void hidePlaylistButton() {
        mShouldShowPlaylistMenu = false;
        try {
            ViewGroup viewGroup =
                    QoraiActivity.getQoraiActivity().getWindow().getDecorView().findViewById(
                            android.R.id.content);
            View playlistButton = viewGroup.findViewById(R.id.playlist_button_id);
            if (playlistButton != null && playlistButton.getVisibility() == View.VISIBLE) {
                playlistButton.setVisibility(View.GONE);
            }
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "hidePlaylistButton " + e);
        }
    }

    private boolean isPlaylistButtonVisible() {
        try {
            ViewGroup viewGroup =
                    QoraiActivity.getQoraiActivity().getWindow().getDecorView().findViewById(
                            android.R.id.content);
            View playlistButton = viewGroup.findViewById(R.id.playlist_button_id);
            return playlistButton != null && playlistButton.getVisibility() == View.VISIBLE;
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "isPlaylistButtonVisible " + e);
            return false;
        }
    }

    private void findMediaFiles() {
        if (mPlaylistService != null && isPlaylistEnabledByPrefsAndFlags()) {
            hidePlaylistButton();
            mPlaylistService.findMediaFilesFromActiveTab();
        }
    }

    private void showPlaylistButton(PlaylistItem[] items) {
        try {
            ViewGroup viewGroup =
                    QoraiActivity.getQoraiActivity().getWindow().getDecorView().findViewById(
                            android.R.id.content);

            PlaylistOptionsListener playlistOptionsListener =
                    new PlaylistOptionsListener() {
                        @Override
                        public void onPlaylistOptionClicked(
                                PlaylistOptionsModel playlistOptionsModel) {
                            try {
                                if (playlistOptionsModel.getOptionType()
                                        == PlaylistOptionsEnum.ADD_MEDIA) {
                                    addMediaToPlaylist(items);
                                } else if (playlistOptionsModel.getOptionType()
                                        == PlaylistOptionsEnum.OPEN_PLAYLIST) {
                                    QoraiActivity.getQoraiActivity()
                                            .openPlaylistActivity(
                                                    getContext(), ConstantUtils.DEFAULT_PLAYLIST);
                                } else if (playlistOptionsModel.getOptionType()
                                        == PlaylistOptionsEnum.PLAYLIST_SETTINGS) {
                                    QoraiActivity.getQoraiActivity().openQoraiPlaylistSettings();
                                }
                            } catch (QoraiActivity.QoraiActivityNotFoundException e) {
                                Log.e(TAG, "showPlaylistButton onOptionClicked " + e);
                            }
                        }
                    };
            if (!isPlaylistButtonVisible()) {
                PlaylistOnboardingActionClickListener playlistOnboardingActionClickListener =
                        new PlaylistOnboardingActionClickListener() {
                            @Override
                            public void onOnboardingActionClick() {
                                addMediaToPlaylist(items);
                            }
                        };

                PlaylistViewUtils.showPlaylistButton(
                        QoraiActivity.getQoraiActivity(),
                        viewGroup,
                        playlistOptionsListener,
                        playlistOnboardingActionClickListener);
            }
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showPlaylistButton " + e);
        }
    }

    private void addMediaToPlaylist(PlaylistItem[] items) {
        if (mPlaylistService == null) {
            return;
        }
        mPlaylistService.getPlaylist(
                ConstantUtils.DEFAULT_PLAYLIST,
                defaultPlaylist -> {
                    Set<String> pageSources = new HashSet<String>();
                    for (PlaylistItem defaultPlaylistItem : defaultPlaylist.items) {
                        pageSources.add(defaultPlaylistItem.pageSource.url);
                    }
                    List<PlaylistItem> playlistItems = new ArrayList();
                    for (PlaylistItem playlistItem : items) {
                        // Check for duplicates in default playlist
                        if (!pageSources.contains(playlistItem.pageSource.url)) {
                            playlistItems.add(playlistItem);
                        }
                    }
                    if (playlistItems.size() > 0) {
                        mPlaylistService.addMediaFiles(
                                playlistItems.toArray(new PlaylistItem[0]),
                                ConstantUtils.DEFAULT_PLAYLIST,
                                true,
                                addedItems -> {
                                    if (addedItems.length > 0) {
                                        showAddedToPlaylistSnackBar();
                                    }
                                });
                    } else {
                        showAlreadyAddedToPlaylistSnackBar();
                    }
                });
    }

    public void addMediaToPlaylist() {
        Tab currentTab = getToolbarDataProvider().getTab();
        if (mPlaylistService == null || currentTab == null) {
            return;
        }
        mPlaylistService.addMediaFilesFromActiveTabToPlaylist(
                ConstantUtils.DEFAULT_PLAYLIST,
                true,
                addedItems -> {
                    if (addedItems.length > 0) {
                        showAddedToPlaylistSnackBar();
                    }
                });
    }

    private void showAddedToPlaylistSnackBar() {
        SnackBarActionModel snackBarActionModel =
                new SnackBarActionModel(
                        getContext().getResources().getString(R.string.view_action),
                        new View.OnClickListener() {
                            @Override
                            public void onClick(View v) {
                                try {
                                    QoraiActivity.getQoraiActivity()
                                            .openPlaylistActivity(
                                                    getContext(), ConstantUtils.DEFAULT_PLAYLIST);
                                } catch (QoraiActivity.QoraiActivityNotFoundException e) {
                                    Log.e(TAG, "showAddedToPlaylistSnackBar onClick ", e);
                                }
                            }
                        });
        try {
            ViewGroup viewGroup =
                    QoraiActivity.getQoraiActivity().getWindow().getDecorView().findViewById(
                            android.R.id.content);
            String playlistName =
                    getContext().getResources().getString(R.string.playlist_play_later);
            PlaylistViewUtils.showSnackBarWithActions(
                    viewGroup,
                    String.format(
                            getContext().getResources().getString(R.string.added_to_playlist),
                            playlistName),
                    snackBarActionModel);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showAddedToPlaylistSnackBar ", e);
        }
    }

    private void showAlreadyAddedToPlaylistSnackBar() {
        SnackBarActionModel snackBarActionModel =
                new SnackBarActionModel(
                        getContext().getResources().getString(R.string.close_text),
                        new View.OnClickListener() {
                            @Override
                            public void onClick(View v) {
                                // Do nothing
                            }
                        });
        try {
            ViewGroup viewGroup =
                    QoraiActivity.getQoraiActivity()
                            .getWindow()
                            .getDecorView()
                            .findViewById(android.R.id.content);
            PlaylistViewUtils.showSnackBarWithActions(
                    viewGroup,
                    getContext().getResources().getString(R.string.already_added_in_playlist),
                    snackBarActionModel);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showAlreadyAddedToPlaylistSnackBar " + e);
        }
    }

    private void checkForTooltip(Tab tab) {
        // We are disabling this feature for now for bottom address bar, until new design is ready
        // https://github.com/qorai/qorai-browser/issues/46252
        if (BottomToolbarConfiguration.isToolbarBottomAnchored()) return;
        try {
            if (!QoraiShieldsUtils.isTooltipShown
                    && !QoraiActivity.getQoraiActivity().mIsDeepLink) {
                if (!QoraiShieldsUtils.hasShieldsTooltipShown(
                            QoraiShieldsUtils.PREF_SHIELDS_TOOLTIP)
                        && mQoraiShieldsHandler.getTrackersBlockedCount(tab.getId())
                                        + mQoraiShieldsHandler.getAdsBlockedCount(tab.getId())
                                > 0) {
                    showTooltip(QoraiShieldsUtils.PREF_SHIELDS_TOOLTIP, tab.getId());
                }
            }
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "checkForTooltip " + e);
        }
    }

    private void showTooltip(String tooltipPref, int tabId) {
        try {
            HighlightView highlightView = new HighlightView(getContext(), null);
            highlightView.setColor(ContextCompat.getColor(
                    getContext(), R.color.onboarding_search_highlight_color));
            ViewGroup viewGroup =
                    QoraiActivity.getQoraiActivity().getWindow().getDecorView().findViewById(
                            android.R.id.content);
            float padding = (float) dpToPx(getContext(), 20);
            mShieldsPopupWindowTooltip =
                    new PopupWindowTooltip.Builder(getContext())
                            .anchorView(mQoraiShieldsButton)
                            .arrowColor(ContextCompat.getColor(
                                    getContext(), R.color.onboarding_arrow_color))
                            .gravity(Gravity.BOTTOM)
                            .dismissOnOutsideTouch(true)
                            .dismissOnInsideTouch(false)
                            .backgroundDimDisabled(true)
                            .padding(padding)
                            .parentPaddingHorizontal(dpToPx(getContext(), 10))
                            .modal(true)
                            .onDismissListener(tooltip -> {
                                if (viewGroup != null && highlightView != null) {
                                    highlightView.stopAnimation();
                                    viewGroup.removeView(highlightView);
                                }
                            })
                            .contentView(R.layout.qorai_shields_tooltip_layout)
                            .build();

            ArrayList<String> blockerNamesList = mQoraiShieldsHandler.getBlockerNamesList(tabId);

            int adsTrackersCount = mQoraiShieldsHandler.getTrackersBlockedCount(tabId)
                    + mQoraiShieldsHandler.getAdsBlockedCount(tabId);

            String displayTrackerName = "";
            if (blockerNamesList.contains(BigtechCompany.Google.name())) {
                displayTrackerName = BigtechCompany.Google.name();
            } else if (blockerNamesList.contains(BigtechCompany.Facebook.name())) {
                displayTrackerName = BigtechCompany.Facebook.name();
            } else if (blockerNamesList.contains(BigtechCompany.Amazon.name())) {
                displayTrackerName = BigtechCompany.Amazon.name();
            }

            String trackerText = "";
            if (!displayTrackerName.isEmpty()) {
                if (adsTrackersCount - 1 == 0) {
                    trackerText =
                            String.format(getContext().getResources().getString(
                                                  R.string.shield_bigtech_tracker_only_blocked),
                                    displayTrackerName);

                } else {
                    trackerText = String.format(getContext().getResources().getString(
                                                        R.string.shield_bigtech_tracker_blocked),
                            displayTrackerName, String.valueOf(adsTrackersCount - 1));
                }
            } else {
                trackerText = String.format(
                        getContext().getResources().getString(R.string.shield_tracker_blocked),
                        String.valueOf(adsTrackersCount));
            }

            TextView tvBlocked = mShieldsPopupWindowTooltip.findViewById(R.id.tv_blocked);
            tvBlocked.setText(trackerText);

            if (mQoraiShieldsButton != null && mQoraiShieldsButton.isShown()) {
                viewGroup.addView(highlightView);
                HighlightItem item = new HighlightItem(mQoraiShieldsButton);

                ImageButton qoraiShieldButton =
                        new ImageButton(getContext(), null, R.style.ToolbarButton);
                qoraiShieldButton.setImageResource(R.drawable.btn_qorai);
                FrameLayout.LayoutParams qoraiShieldParams =
                        new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                                FrameLayout.LayoutParams.WRAP_CONTENT);

                int[] location = new int[2];
                highlightView.getLocationOnScreen(location);
                qoraiShieldParams.leftMargin = item.getScreenLeft() + dpToPx(getContext(), 10);
                qoraiShieldParams.topMargin = item.getScreenTop()
                        + ((item.getScreenBottom() - item.getScreenTop()) / 4) - location[1];
                qoraiShieldButton.setLayoutParams(qoraiShieldParams);
                highlightView.addView(qoraiShieldButton);

                highlightView.setShouldShowHighlight(true);
                highlightView.setHighlightTransparent(true);
                highlightView.setHighlightItem(item);
                highlightView.initializeAnimators();
                highlightView.startAnimation();

                mShieldsPopupWindowTooltip.show();
                QoraiShieldsUtils.setShieldsTooltipShown(tooltipPref, true);
                QoraiShieldsUtils.isTooltipShown = true;
            }

        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showTooltip " + e);
        }
    }

    public void dismissShieldsTooltip() {
        if (mShieldsPopupWindowTooltip != null && mShieldsPopupWindowTooltip.isShowing()) {
            mShieldsPopupWindowTooltip.dismiss();
            mShieldsPopupWindowTooltip = null;
        }
    }

    public void reopenShieldsPanel() {
        if (mQoraiShieldsHandler != null && mQoraiShieldsHandler.isShowing()) {
            mQoraiShieldsHandler.hideQoraiShieldsMenu();
            showShieldsMenu(mQoraiShieldsButton);
        }
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        Context context = getContext();
        if (context instanceof Activity
                && (((Activity) context).isFinishing() || ((Activity) context).isDestroyed())) {
            return;
        }
        dismissShieldsTooltip();
        reopenShieldsPanel();
        // TODO: show wallet panel
    }

    private void addSavedBandwidthToDb(long savings) {
        new AsyncTask<Void>() {
            @Override
            protected Void doInBackground() {
                try {
                    SavedBandwidthTable savedBandwidthTable =
                            new SavedBandwidthTable(
                                    savings, QoraiStatsUtil.getCalculatedDate("yyyy-MM-dd", 0));
                    long unused_rowId = mDatabaseHelper.insertSavedBandwidth(savedBandwidthTable);
                } catch (Exception e) {
                    // Do nothing if url is invalid.
                    // Just return w/o showing shields popup.
                    return null;
                }
                return null;
            }

            @Override
            protected void onPostExecute(Void result) {
                assert ThreadUtils.runningOnUiThread();
                if (isCancelled()) return;
            }
        }.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
    }

    private void addStatsToDb(String statType, String statSite, String url) {
        new AsyncTask<Void>() {
            @Override
            protected Void doInBackground() {
                try {
                    URL urlObject = new URL(url);
                    URL siteObject = new URL(statSite);
                    QoraiStatsTable qoraiStatsTable =
                            new QoraiStatsTable(
                                    url,
                                    urlObject.getHost(),
                                    statType,
                                    statSite,
                                    siteObject.getHost(),
                                    QoraiStatsUtil.getCalculatedDate("yyyy-MM-dd", 0));
                    long unused_rowId = mDatabaseHelper.insertStats(qoraiStatsTable);
                } catch (Exception e) {
                    // Do nothing if url is invalid.
                    // Just return w/o showing shields popup.
                    return null;
                }
                return null;
            }

            @Override
            protected void onPostExecute(Void result) {
                assert ThreadUtils.runningOnUiThread();
                if (isCancelled()) return;
            }
        }.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
    }

    public boolean isWalletIconVisible() {
        if (mWalletLayout == null) {
            return false;
        }
        return mWalletLayout.getVisibility() == View.VISIBLE;
    }

    public void showWalletIcon(boolean show, Tab tab) {
        // The layout could be null in Custom Tabs layout
        if (mWalletLayout == null) {
            return;
        }
        Tab currentTab = tab;
        if (currentTab == null) {
            currentTab = getToolbarDataProvider().getTab();
            if (currentTab == null) {
                return;
            }
        }
        if (show) {
            mWalletLayout.setVisibility(View.VISIBLE);
            mTabsWithWalletIcon.add(currentTab.getId());
        } else {
            mWalletLayout.setVisibility(View.GONE);
            mTabsWithWalletIcon.remove(currentTab.getId());
        }
    }

    public void showWalletIcon(boolean show) {
        showWalletIcon(show, null);
    }

    public void hideRewardsOnboardingIcon() {
        if (mQoraiRewardsOnboardingIcon != null) {
            mQoraiRewardsOnboardingIcon.setVisibility(View.GONE);
        }
        if (mQoraiRewardsNotificationsCount != null) {
            mQoraiRewardsNotificationsCount.setVisibility(View.GONE);
        }
        ChromeSharedPreferences.getInstance()
                .writeBoolean(PREF_WAS_TOOLBAR_QOR_LOGO_BUTTON_PRESSED, true);
    }

    @Override
    public void onClickImpl(View v) {
        if (mQoraiShieldsHandler == null) {
            assert false;
            return;
        }
        if (mQoraiShieldsButton == v && mQoraiShieldsButton != null) {
            showShieldsMenu(mQoraiShieldsButton);
        } else if (mQoraiRewardsButton == v && mQoraiRewardsButton != null) {
            hideRewardsOnboardingIcon();
            OnboardingPrefManager.getInstance().setOnboardingShown(true);
            showRewardsPage();

            if (mQoraiRewardsNotificationsCount.isShown()) {
                ChromeSharedPreferences.getInstance()
                        .writeBoolean(PREF_WAS_TOOLBAR_QOR_LOGO_BUTTON_PRESSED, true);
                mQoraiRewardsNotificationsCount.setVisibility(View.INVISIBLE);
                mIsInitialNotificationPosted = false;
            }
        } else if (mHomeButton == v) {
            // Helps Qorai News know how to behave on home button action
            try {
                QoraiActivity.getQoraiActivity().setComesFromNewTab(true);
            } catch (QoraiActivity.QoraiActivityNotFoundException e) {
                Log.e(TAG, "HomeButton click " + e);
            }
        } else if (mQoraiWalletButton == v && mQoraiWalletButton != null) {
            maybeShowWalletPanel();
        } else if (mYouTubePipButton == v && mYouTubePipButton != null) {
            Tab currentTab = getToolbarDataProvider().getTab();
            if (currentTab != null
                    && QoraiYouTubeScriptInjectorNativeHelper.isPictureInPictureAvailable(
                            currentTab.getWebContents())) {
                if (!PictureInPicture.isEnabled(getContext())) {
                    hideYouTubePipIcon();
                    return;
                }
                QoraiYouTubeScriptInjectorNativeHelper.setFullscreen(currentTab.getWebContents());
            }
        }
    }

    public void showRewardsPage() {
        String rewardsUrl = QoraiActivity.QORAI_REWARDS_SETTINGS_URL + "?bubble";
        if (mPublisherId != null && !mPublisherId.isEmpty()) {
            rewardsUrl += "&creator=" + URLEncoder.encode(mPublisherId);
        }
        FullScreenCustomTabActivity.showPage(getContext(), rewardsUrl);
    }

    private void maybeShowWalletPanel() {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.showWalletPanel(true);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "maybeShowWalletPanel " + e);
        }
    }

    private void showWalletPanelInternal(View v) {
        mDAppsWalletController =
                new DAppsWalletController(getContext(), v, dialog -> mDAppsWalletController = null);
        mDAppsWalletController.showWalletPanel();
    }

    public void showWalletPanel() {
        if (mDAppsWalletController == null) {
            showWalletPanelInternal(this);
        } else if (!mDAppsWalletController.isShowingPanel()) {
            mDAppsWalletController.showWalletPanel();
        }
    }

    @Override
    public void onClick(View v) {
        onClickImpl(v);
    }

    private boolean checkForRewardsOnboarding() {
        return PackageUtils.isFirstInstall(getContext())
                && mQoraiRewardsNativeWorker != null
                && !mQoraiRewardsNativeWorker.isRewardsEnabled()
                && mQoraiRewardsNativeWorker.isSupported()
                && !OnboardingPrefManager.getInstance().isOnboardingShown()
                && (QoraiRewardsHelper.getRewardsOnboardingIconInvisibleTiming() == 0
                        || (QoraiRewardsHelper.getRewardsOnboardingIconInvisibleTiming() > 0
                                && System.currentTimeMillis()
                                        <= QoraiRewardsHelper
                                                .getRewardsOnboardingIconInvisibleTiming()));
    }

    private void showShieldsMenu(View mQoraiShieldsButton) {
        Tab currentTab = getToolbarDataProvider().getTab();
        if (currentTab == null) {
            return;
        }
        try {
            URL url = new URL(currentTab.getUrl().getSpec());
            // Don't show shields popup if protocol is not valid for shields.
            if (!isValidProtocolForShields(url.getProtocol())) {
                return;
            }
            mQoraiShieldsHandler.show(mQoraiShieldsButton, currentTab);
        } catch (Exception e) {
            // Do nothing if url is invalid.
            // Just return w/o showing shields popup.
            return;
        }
    }

    @Override
    public boolean onLongClickImpl(View v) {
        // Use null as the default description since Toast.showAnchoredToast
        // will return false if it is null.
        String description = null;
        Context context = getContext();
        Resources resources = context.getResources();

        if (v == mQoraiShieldsButton) {
            description = resources.getString(R.string.accessibility_toolbar_btn_qorai_shields);
        } else if (v == mQoraiRewardsButton) {
            description = resources.getString(R.string.accessibility_toolbar_btn_qorai_rewards);
        } else if (v == mHomeButton) {
            description = resources.getString(R.string.accessibility_toolbar_btn_home);
        } else if (v == mQoraiWalletButton) {
            description = resources.getString(R.string.accessibility_toolbar_btn_qorai_wallet);
        } else if (v == mYouTubePipButton) {
            description = resources.getString(R.string.accessibility_toolbar_btn_qorai_pip);
        }

        return Toast.showAnchoredToast(context, v, description);
    }

    @Override
    public boolean onLongClick(View v) {
        return onLongClickImpl(v);
    }

    @Override
    public void populateUrlAnimatorSetImpl(
            boolean showExpandedState,
            int urlFocusToolbarButtonsDuration,
            int urlClearFocusTabStackDelayMs,
            List<Animator> animators) {
        if (mQoraiShieldsButton != null) {
            Animator animator;
            if (showExpandedState) {
                float density = getContext().getResources().getDisplayMetrics().density;
                boolean isRtl = getLayoutDirection() == LAYOUT_DIRECTION_RTL;
                float toolbarButtonTranslationX =
                        MathUtils.flipSignIf(URL_FOCUS_TOOLBAR_BUTTONS_TRANSLATION_X_DP, isRtl)
                        * density;
                animator = ObjectAnimator.ofFloat(
                        mQoraiShieldsButton, TRANSLATION_X, toolbarButtonTranslationX);
                animator.setDuration(urlFocusToolbarButtonsDuration);
                animator.setInterpolator(Interpolators.FAST_OUT_LINEAR_IN_INTERPOLATOR);
                animators.add(animator);

                animator = ObjectAnimator.ofFloat(mQoraiShieldsButton, ALPHA, 0);
                animator.setDuration(urlFocusToolbarButtonsDuration);
                animator.setInterpolator(Interpolators.FAST_OUT_LINEAR_IN_INTERPOLATOR);
                animators.add(animator);
            } else {
                animator = ObjectAnimator.ofFloat(mQoraiShieldsButton, TRANSLATION_X, 0);
                animator.setDuration(urlFocusToolbarButtonsDuration);
                animator.setStartDelay(urlClearFocusTabStackDelayMs);
                animator.setInterpolator(Interpolators.FAST_OUT_SLOW_IN_INTERPOLATOR);
                animators.add(animator);

                animator = ObjectAnimator.ofFloat(mQoraiShieldsButton, ALPHA, 1);
                animator.setDuration(urlFocusToolbarButtonsDuration);
                animator.setStartDelay(urlClearFocusTabStackDelayMs);
                animator.setInterpolator(Interpolators.FAST_OUT_SLOW_IN_INTERPOLATOR);
                animators.add(animator);
            }
        }
    }

    @Override
    public void updateModernLocationBarColorImpl(int color) {
        mCurrentToolbarColor = color;
        if (mShieldsLayout != null) {
            mShieldsLayout.getBackground().setColorFilter(color, PorterDuff.Mode.SRC_IN);
        }
        if (mRewardsLayout != null) {
            mRewardsLayout.getBackground().setColorFilter(color, PorterDuff.Mode.SRC_IN);
        }
        if (mWalletLayout != null) {
            mWalletLayout.getBackground().setColorFilter(color, PorterDuff.Mode.SRC_IN);
        }
        if (mYouTubePipLayout != null) {
            mYouTubePipLayout.getBackground().setColorFilter(color, PorterDuff.Mode.SRC_IN);
        }
    }

    /**
     * If |tab| is null, set disabled image to shields button and |urlString| is ignored. If
     * |urlString| is null, url is fetched from |tab|.
     */
    public void updateQoraiShieldsButtonState(Tab tab) {
        if (mQoraiShieldsButton == null) {
            assert false;
            return;
        }

        if (tab == null) {
            mQoraiShieldsButton.setImageResource(R.drawable.btn_qorai_off);
            return;
        }
        mQoraiShieldsButton.setImageResource(
                isShieldsOnForTab(tab) ? R.drawable.btn_qorai : R.drawable.btn_qorai_off);

        if (mRewardsLayout == null) return;
        if (isIncognito()) {
            mRewardsLayout.setVisibility(View.GONE);
            updateShieldsLayoutBackground(true);
        } else if (isNativeLibraryReady()
                && mQoraiRewardsNativeWorker != null
                && mQoraiRewardsNativeWorker.isSupported()
                && NtpUtil.shouldShowRewardsIcon()) {
            mRewardsLayout.setVisibility(View.VISIBLE);
            updateShieldsLayoutBackground(false);
        }
    }

    private boolean isShieldsOnForTab(Tab tab) {
        if (!isNativeLibraryReady()
                || tab == null
                || Profile.fromWebContents(tab.getWebContents()) == null) {
            return false;
        }

        return QoraiShieldsContentSettings.getShields(
                Profile.fromWebContents(tab.getWebContents()),
                tab.getUrl().getSpec(),
                QoraiShieldsContentSettings.RESOURCE_IDENTIFIER_QORAI_SHIELDS);
    }

    private boolean isValidProtocolForShields(String protocol) {
        if (protocol.equals("http") || protocol.equals("https")) {
            return true;
        }

        return false;
    }

    public void dismissWalletPanelOrDialog() {
        if (mDAppsWalletController != null) {
            mDAppsWalletController.dismiss();
            mDAppsWalletController = null;
        }
    }

    public void openRewardsPanel() {
        onClick(mQoraiRewardsButton);
    }

    public boolean isShieldsTooltipShown() {
        if (mShieldsPopupWindowTooltip != null) {
            return mShieldsPopupWindowTooltip.isShowing();
        }
        return false;
    }

    @Override
    public void onCompleteReset(boolean success) {
        if (success) {
            QoraiRewardsHelper.resetRewards();
        }
    }

    @Override
    public void onNotificationAdded(String id, int type, long timestamp, String[] args) {
        if (mQoraiRewardsNativeWorker == null) {
            return;
        }
        mQoraiRewardsNativeWorker.getAllNotifications();
    }

    private boolean mayShowQoraiAdsOnboardingDialog() {
        Context context = getContext();

        if (QoraiAdsSignupDialog.shouldShowNewUserDialog(context)) {
            QoraiAdsSignupDialog.showNewUserDialog(getContext());
            return true;
        } else if (QoraiAdsSignupDialog.shouldShowNewUserDialogIfRewardsIsSwitchedOff(context)) {
            QoraiAdsSignupDialog.showNewUserDialog(getContext());
            return true;
        } else if (QoraiAdsSignupDialog.shouldShowExistingUserDialog(context)) {
            QoraiAdsSignupDialog.showExistingUserDialog(getContext());
            return true;
        }

        return false;
    }

    @Override
    public void onNotificationsCount(int count) {
        if (mQoraiRewardsNotificationsCount != null) {
            if (count != 0) {
                String value = Integer.toString(count);
                if (count > 99) {
                    mQoraiRewardsNotificationsCount.setBackground(
                            ResourcesCompat.getDrawable(getContext().getResources(),
                                    R.drawable.qorai_rewards_rectangle, /* theme= */ null));
                    value = "99+";
                } else {
                    mQoraiRewardsNotificationsCount.setBackground(
                            ResourcesCompat.getDrawable(getContext().getResources(),
                                    R.drawable.qorai_rewards_circle, /* theme= */ null));
                }
                mQoraiRewardsNotificationsCount.setText(value);
                mQoraiRewardsNotificationsCount.setVisibility(View.VISIBLE);
                mIsNotificationPosted = true;
            } else {
                mQoraiRewardsNotificationsCount.setText("");
                mQoraiRewardsNotificationsCount.setBackgroundResource(0);
                mQoraiRewardsNotificationsCount.setVisibility(View.INVISIBLE);
                mIsNotificationPosted = false;
                updateVerifiedPublisherMark();
            }
        }

        if (!PackageUtils.isFirstInstall(getContext())
                && !OnboardingPrefManager.getInstance().isAdsAvailable()) {
            mayShowQoraiAdsOnboardingDialog();
        }

        if (System.currentTimeMillis() > QoraiRewardsHelper.getRewardsOnboardingIconTiming()
                && checkForRewardsOnboarding()) {
            if (mQoraiRewardsOnboardingIcon != null) {
                mQoraiRewardsOnboardingIcon.setVisibility(View.VISIBLE);
            }
            if (mQoraiRewardsNotificationsCount != null) {
                mQoraiRewardsNotificationsCount.setVisibility(View.GONE);
            }

            if (!QoraiRewardsHelper.hasRewardsOnboardingIconInvisibleUpdated()) {
                Calendar calender = Calendar.getInstance();
                calender.setTime(new Date());
                calender.add(Calendar.DATE, DAYS_7);
                QoraiRewardsHelper.setRewardsOnboardingIconInvisibleTiming(
                        calender.getTimeInMillis());
                QoraiRewardsHelper.setRewardsOnboardingIconInvisible(true);
            }
        }
    }

    private boolean isCustomTab() {
        return QoraiReflectionUtil.equalTypes(this.getClass(), CustomTabToolbar.class);
    }

    @Override
    public void onThemeColorChanged(int color, boolean shouldAnimate) {
        if (mWalletIcon != null) {
            ImageViewCompat.setImageTintList(mWalletIcon,
                    !ColorUtils.shouldUseLightForegroundOnBackground(color) ? mDarkModeTint
                                                                            : mLightModeTint);
        }

        final int textBoxColor =
                ThemeUtils.getTextBoxColorForToolbarBackgroundInNonNativePage(
                        getContext(), color, isIncognito(), isCustomTab());
        updateModernLocationBarColorImpl(textBoxColor);
    }

    /**
     * QoraiRewardsNativeWorker.PublisherObserver: Update a 'verified publisher' checkmark on url
     * bar QOR icon only if no notifications are posted.
     */
    @Override
    public void onFrontTabPublisherChanged(boolean verified, String publisherId) {
        mIsPublisherVerified = verified;
        mPublisherId = publisherId;
        updateVerifiedPublisherMark();
    }

    private void updateVerifiedPublisherMark() {
        if (mQoraiRewardsNotificationsCount == null) {
            // Most likely we are on a custom page
            return;
        }
        if (mIsInitialNotificationPosted) {
            return;
        } else if (!mIsNotificationPosted) {
            if (mIsPublisherVerified) {
                mQoraiRewardsNotificationsCount.setVisibility(View.VISIBLE);
                mQoraiRewardsNotificationsCount.setBackground(
                        ResourcesCompat.getDrawable(getContext().getResources(),
                                R.drawable.rewards_verified_tick_icon, /* theme= */ null));
            } else {
                mQoraiRewardsNotificationsCount.setBackgroundResource(0);
                mQoraiRewardsNotificationsCount.setVisibility(View.INVISIBLE);
            }
        }
    }

    public void onBottomControlsVisibilityChanged(boolean isVisible) {
        mIsBottomControlsVisible = isVisible;
        if (QoraiReflectionUtil.equalTypes(this.getClass(), ToolbarPhone.class)
                && getMenuButtonCoordinator() != null) {
            getMenuButtonCoordinator().setVisibility(!isVisible);
            ToggleTabStackButton toggleTabStackButton = findViewById(R.id.tab_switcher_button);
            if (toggleTabStackButton != null) {
                toggleTabStackButton.setVisibility(
                        isTabSwitcherOnBottomControls() ? GONE : VISIBLE);
            }
        }
    }

    private void updateShieldsLayoutBackground(boolean rounded) {
        if (mShieldsLayout == null) {
            return;
        }

        mShieldsLayout.setBackgroundDrawable(
                ApiCompatibilityUtils.getDrawable(getContext().getResources(),
                        rounded ? R.drawable.modern_toolbar_background_grey_end_segment
                                : R.drawable.modern_toolbar_background_grey_middle_segment));

        updateModernLocationBarColorImpl(mCurrentToolbarColor);
    }

    private boolean isTabSwitcherOnBottomControls() {
        return mIsBottomControlsVisible
                && BottomToolbarVariationManager.isTabSwitcherOnBottomControls();
    }

    private boolean isMenuButtonOnBottomControls() {
        return mIsBottomControlsVisible
                && BottomToolbarVariationManager.isMenuButtonOnBottomControls();
    }

    @Override
    public void initialize(
            ToolbarDataProvider toolbarDataProvider,
            ToolbarTabController tabController,
            MenuButtonCoordinator menuButtonCoordinator,
            ToggleTabStackButtonCoordinator tabSwitcherButtonCoordinator,
            HistoryDelegate historyDelegate,
            UserEducationHelper userEducationHelper,
            ObservableSupplier<Tracker> trackerSupplier,
            ToolbarProgressBar progressBar,
            @Nullable ReloadButtonCoordinator reloadButtonCoordinator,
            @Nullable BackButtonCoordinator backButtonCoordinator,
            @Nullable ForwardButtonCoordinator forwardButtonCoordinator,
            @Nullable HomeButtonDisplay homeButtonDisplay,
            @Nullable ExtensionToolbarCoordinator extensionToolbarCoordinator,
            ThemeColorProvider themeColorProvider,
            IncognitoStateProvider incognitoStateProvider) {
        super.initialize(
                toolbarDataProvider,
                tabController,
                menuButtonCoordinator,
                tabSwitcherButtonCoordinator,
                historyDelegate,
                userEducationHelper,
                trackerSupplier,
                progressBar,
                reloadButtonCoordinator,
                backButtonCoordinator,
                forwardButtonCoordinator,
                homeButtonDisplay,
                extensionToolbarCoordinator,
                themeColorProvider,
                incognitoStateProvider);

        QoraiMenuButtonCoordinator.setMenuFromBottom(
                isMenuButtonOnBottomControls() || isMenuOnBottomWithBottomAddressBar());
    }

    public void updateWalletBadgeVisibility(boolean visible) {
        assert mQoraiWalletBadge != null;
        mQoraiWalletBadge.setVisibility(visible ? View.VISIBLE : View.GONE);
    }

    public void updateMenuButtonState() {
        if (BottomToolbarConfiguration.isQoraiBottomControlsEnabled()) {
            QoraiMenuButtonCoordinator.setMenuFromBottom(mIsBottomControlsVisible);
        } else {
            QoraiMenuButtonCoordinator.setMenuFromBottom(isMenuOnBottomWithBottomAddressBar());
        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (QoraiReflectionUtil.equalTypes(this.getClass(), CustomTabToolbar.class)
                || QoraiReflectionUtil.equalTypes(this.getClass(), ToolbarPhone.class)) {
            updateMenuButtonState();
            Tab tab = getToolbarDataProvider() != null ? getToolbarDataProvider().getTab() : null;
            if (tab != null && tab.getWebContents() != null) {
                updateQoraiShieldsButtonState(tab);
            }
        }
        super.onDraw(canvas);
    }

    @Override
    public boolean isLocationBarValid(LocationBarCoordinator locationBar) {
        return locationBar != null && locationBar.getPhoneCoordinator() != null
                && locationBar.getPhoneCoordinator().getViewForDrawing() != null;
    }

    @Override
    public void drawAnimationOverlay(ViewGroup toolbarButtonsContainer, Canvas canvas) {
        if (mWalletLayout != null && mWalletLayout.getVisibility() != View.GONE) {
            canvas.save();
            ViewUtils.translateCanvasToView(toolbarButtonsContainer, mWalletLayout, canvas);
            mWalletLayout.draw(canvas);
            canvas.restore();
        }
        if (mShieldsLayout != null && mShieldsLayout.getVisibility() != View.GONE) {
            canvas.save();
            ViewUtils.translateCanvasToView(toolbarButtonsContainer, mShieldsLayout, canvas);
            mShieldsLayout.draw(canvas);
            canvas.restore();
        }
        if (mRewardsLayout != null && mRewardsLayout.getVisibility() != View.GONE) {
            canvas.save();
            ViewUtils.translateCanvasToView(toolbarButtonsContainer, mRewardsLayout, canvas);
            mRewardsLayout.draw(canvas);
            canvas.restore();
        }
        if (mYouTubePipLayout != null && mYouTubePipLayout.getVisibility() != View.GONE) {
            canvas.save();
            ViewUtils.translateCanvasToView(toolbarButtonsContainer, mYouTubePipLayout, canvas);
            mYouTubePipLayout.draw(canvas);
            canvas.restore();
        }
    }

    @Override
    public void onMediaFilesUpdated(Url pageUrl, PlaylistItem[] playlistItems) {
        Tab currentTab = getToolbarDataProvider().getTab();
        if (currentTab == null || !pageUrl.url.equals(currentTab.getUrl().getSpec())) {
            return;
        }
        if (playlistItems.length > 0 && !UrlUtilities.isNtpUrl(currentTab.getUrl().getSpec())) {
            mShouldShowPlaylistMenu = true;
            if (ChromeSharedPreferences.getInstance()
                    .readBoolean(QoraiPreferenceKeys.PREF_ADD_TO_PLAYLIST_BUTTON, true)) {
                showPlaylistButton(playlistItems);
            }
        }
    }

    private boolean isMenuOnBottomWithBottomAddressBar() {
        // If address bar is not on bottom, then menu is not on bottom too.
        if (!BottomToolbarConfiguration.isToolbarBottomAnchored()) {
            return false;
        }
        // Menu can be on bottom only with ToolbarPhone.
        if (!QoraiReflectionUtil.equalTypes(this.getClass(), ToolbarPhone.class)) {
            return false;
        }
        // In overview mode the menu is on top.
        Context context = getContext();
        if (context instanceof QoraiActivity && ((QoraiActivity) context).isInOverviewMode()) {
            return false;
        }
        return true;
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        maybeHideRewardsLayout(MeasureSpec.getSize(widthMeasureSpec));
    }

    /**
     * Hides the rewards layout if the toolbar width is less than the minimum tablet width and the
     * rewards icon should be shown. Uses the same threshold as the existing toolbar button
     * visibility logic in ToolbarTablet.
     */
    private void maybeHideRewardsLayout(int width) {
        // Only hide the rewards layout on tablet devices, like it is done in the upstream code.
        if (!QoraiReflectionUtil.equalTypes(this.getClass(), ToolbarTablet.class)) {
            return;
        }

        if (mRewardsLayout == null || !NtpUtil.shouldShowRewardsIcon()) {
            return;
        }

        mRewardsLayout.setVisibility(
                width >= DeviceFormFactor.getNonMultiDisplayMinimumTabletWidthPx(getContext())
                        ? View.VISIBLE
                        : View.GONE);
        // Update the shields layout background to match the rewards layout visibility.
        updateShieldsLayoutBackground(mRewardsLayout.getVisibility() == View.GONE);
    }
}
