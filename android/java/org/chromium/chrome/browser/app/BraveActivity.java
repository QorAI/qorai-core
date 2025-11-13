/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.app;

import android.app.Activity;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PictureInPictureParams;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentSender;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.ImageView;

import androidx.annotation.MainThread;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.widget.AppCompatEditText;
import androidx.coordinatorlayout.widget.CoordinatorLayout;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.qorai.playlist.util.ConstantUtils;
import com.qorai.playlist.util.PlaylistPreferenceUtils;
import com.qorai.playlist.util.PlaylistUtils;
import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import com.google.android.play.core.appupdate.AppUpdateInfo;
import com.google.android.play.core.appupdate.AppUpdateManager;
import com.google.android.play.core.appupdate.AppUpdateManagerFactory;
import com.google.android.play.core.install.InstallStateUpdatedListener;
import com.google.android.play.core.install.model.AppUpdateType;
import com.google.android.play.core.install.model.InstallStatus;
import com.google.android.play.core.install.model.UpdateAvailability;
import com.google.android.play.core.tasks.Task;
import com.wireguard.android.backend.GoBackend;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.base.ApplicationStatus;
import org.chromium.base.QoraiFeatureList;
import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.base.QoraiReflectionUtil;
import org.chromium.base.CollectionUtil;
import org.chromium.base.CommandLine;
import org.chromium.base.ContextUtils;
import org.chromium.base.IntentUtils;
import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.UnownedUserDataSupplier;
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;
import org.chromium.qorai.browser.customize_menu.CustomizeQoraiMenu;
import org.chromium.qorai.browser.quick_search_engines.settings.QuickSearchEnginesCallback;
import org.chromium.qorai.browser.quick_search_engines.settings.QuickSearchEnginesFragment;
import org.chromium.qorai.browser.quick_search_engines.settings.QuickSearchEnginesModel;
import org.chromium.qorai.browser.quick_search_engines.utils.QuickSearchEnginesUtil;
import org.chromium.qorai.browser.quick_search_engines.views.QuickSearchEnginesViewAdapter;
import org.chromium.qorai_wallet.mojom.AssetRatioService;
import org.chromium.qorai_wallet.mojom.BlockchainRegistry;
import org.chromium.qorai_wallet.mojom.QoraiWalletService;
import org.chromium.qorai_wallet.mojom.CoinType;
import org.chromium.qorai_wallet.mojom.EthTxManagerProxy;
import org.chromium.qorai_wallet.mojom.JsonRpcService;
import org.chromium.qorai_wallet.mojom.KeyringService;
import org.chromium.qorai_wallet.mojom.NetworkInfo;
import org.chromium.qorai_wallet.mojom.SignDataUnion;
import org.chromium.qorai_wallet.mojom.SolanaTxManagerProxy;
import org.chromium.qorai_wallet.mojom.SwapService;
import org.chromium.qorai_wallet.mojom.TxService;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.QoraiAdFreeCalloutDialogFragment;
import org.chromium.chrome.browser.QoraiHelper;
import org.chromium.chrome.browser.QoraiIntentHandler;
import org.chromium.chrome.browser.QoraiRelaunchUtils;
import org.chromium.chrome.browser.QoraiRewardsHelper;
import org.chromium.chrome.browser.QoraiSyncWorker;
import org.chromium.chrome.browser.ChromeTabbedActivity;
import org.chromium.chrome.browser.DormantUsersEngagementDialogFragment;
import org.chromium.chrome.browser.IntentHandler;
import org.chromium.chrome.browser.InternetConnection;
import org.chromium.chrome.browser.LaunchIntentDispatcher;
import org.chromium.chrome.browser.OpenYtInQoraiDialogFragment;
import org.chromium.chrome.browser.app.domain.WalletModel;
import org.chromium.chrome.browser.billing.InAppPurchaseWrapper;
import org.chromium.chrome.browser.billing.PurchaseModel;
import org.chromium.chrome.browser.bookmarks.TabBookmarker;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraPrefUtils;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraUtils;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraVoiceRecognitionHandler;
import org.chromium.chrome.browser.qorai_news.QoraiNewsUtils;
import org.chromium.chrome.browser.qorai_news.models.FeedItemsCard;
import org.chromium.chrome.browser.qorai_stats.QoraiStatsBottomSheetDialogFragment;
import org.chromium.chrome.browser.qorai_stats.QoraiStatsUtil;
import org.chromium.chrome.browser.browsing_data.BrowsingDataBridge;
import org.chromium.chrome.browser.browsing_data.BrowsingDataType;
import org.chromium.chrome.browser.browsing_data.TimePeriod;
import org.chromium.chrome.browser.compositor.layouts.LayoutManagerChrome;
import org.chromium.chrome.browser.crypto_wallet.AssetRatioServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.BlockchainRegistryFactory;
import org.chromium.chrome.browser.crypto_wallet.QoraiWalletServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.SwapServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.activities.AddAccountActivity;
import org.chromium.chrome.browser.crypto_wallet.activities.QoraiWalletActivity;
import org.chromium.chrome.browser.crypto_wallet.activities.QoraiWalletDAppsActivity;
import org.chromium.chrome.browser.crypto_wallet.model.CryptoAccountTypeInfo;
import org.chromium.chrome.browser.crypto_wallet.util.Utils;
import org.chromium.chrome.browser.customtabs.CustomTabActivity;
import org.chromium.chrome.browser.customtabs.FullScreenCustomTabActivity;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.flags.ChromeSwitches;
import org.chromium.chrome.browser.fullscreen.BrowserControlsManager;
import org.chromium.chrome.browser.fullscreen.FullscreenManager;
import org.chromium.chrome.browser.informers.QoraiSyncAccountDeletedInformer;
import org.chromium.chrome.browser.lifetime.ApplicationLifetime;
import org.chromium.chrome.browser.misc_metrics.MiscAndroidMetricsConnectionErrorHandler;
import org.chromium.chrome.browser.misc_metrics.MiscAndroidMetricsFactory;
import org.chromium.chrome.browser.multiwindow.QoraiMultiWindowUtils;
import org.chromium.chrome.browser.multiwindow.MultiInstanceManager;
import org.chromium.chrome.browser.multiwindow.MultiWindowUtils;
import org.chromium.chrome.browser.notifications.permissions.NotificationPermissionController;
import org.chromium.chrome.browser.notifications.retention.RetentionNotificationUtil;
import org.chromium.chrome.browser.ntp.NewTabPageManager;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.chrome.browser.onboarding.v2.HighlightDialogFragment;
import org.chromium.chrome.browser.playlist.PlaylistHostActivity;
import org.chromium.chrome.browser.playlist.settings.QoraiPlaylistPreferences;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.preferences.QoraiPrefServiceBridge;
import org.chromium.chrome.browser.preferences.ChromePreferenceKeys;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.preferences.Pref;
import org.chromium.chrome.browser.preferences.PrefServiceUtil;
import org.chromium.chrome.browser.preferences.website.QoraiShieldsContentSettings;
import org.chromium.chrome.browser.prefetch.settings.PreloadPagesSettingsBridge;
import org.chromium.chrome.browser.prefetch.settings.PreloadPagesState;
import org.chromium.chrome.browser.privacy.settings.QoraiPrivacySettings;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.profiles.ProfileManager;
import org.chromium.chrome.browser.rate.QoraiRateDialogFragment;
import org.chromium.chrome.browser.rate.RateUtils;
import org.chromium.chrome.browser.rewards.adaptive_captcha.AdaptiveCaptchaHelper;
import org.chromium.chrome.browser.safe_browsing.SafeBrowsingBridge;
import org.chromium.chrome.browser.safe_browsing.SafeBrowsingState;
import org.chromium.chrome.browser.search_engines.TemplateUrlServiceFactory;
import org.chromium.chrome.browser.set_default_browser.QoraiSetDefaultBrowserUtils;
import org.chromium.chrome.browser.settings.QoraiNewsPreferencesV2;
import org.chromium.chrome.browser.settings.QoraiSearchEngineUtils;
import org.chromium.chrome.browser.settings.QoraiWalletPreferences;
import org.chromium.chrome.browser.settings.SettingsNavigationFactory;
import org.chromium.chrome.browser.settings.developer.QoraiQAPreferences;
import org.chromium.chrome.browser.share.ShareDelegate;
import org.chromium.chrome.browser.share.ShareDelegate.ShareOrigin;
import org.chromium.chrome.browser.shields.ContentFilteringFragment;
import org.chromium.chrome.browser.shields.CreateCustomFiltersFragment;
import org.chromium.chrome.browser.site_settings.QoraiWalletEthereumConnectedSites;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabLaunchType;
import org.chromium.chrome.browser.tab.TabSelectionType;
import org.chromium.chrome.browser.tabbed_mode.QoraiTabbedAppMenuPropertiesDelegate;
import org.chromium.chrome.browser.tabmodel.TabClosureParams;
import org.chromium.chrome.browser.tabmodel.TabList;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelUtils;
import org.chromium.chrome.browser.toolbar.QoraiToolbarManager;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;
import org.chromium.chrome.browser.toolbar.top.QoraiToolbarLayoutImpl;
import org.chromium.chrome.browser.ui.RootUiCoordinator;
import org.chromium.chrome.browser.ui.appmenu.AppMenuPropertiesDelegate;
import org.chromium.chrome.browser.ui.messages.snackbar.Snackbar;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager.SnackbarController;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManagerProvider;
import org.chromium.chrome.browser.util.QoraiConstants;
import org.chromium.chrome.browser.util.QoraiDbUtil;
import org.chromium.chrome.browser.util.KeyboardVisibilityHelper;
import org.chromium.chrome.browser.util.LiveDataUtil;
import org.chromium.chrome.browser.util.PackageUtils;
import org.chromium.chrome.browser.util.UsageMonitor;
import org.chromium.chrome.browser.vpn.QoraiVpnNativeWorker;
import org.chromium.chrome.browser.vpn.QoraiVpnObserver;
import org.chromium.chrome.browser.vpn.activities.QoraiVpnProfileActivity;
import org.chromium.chrome.browser.vpn.fragments.LinkVpnSubscriptionDialogFragment;
import org.chromium.chrome.browser.vpn.timer.TimerDialogFragment;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnApiResponseUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnPrefUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnProfileUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnUtils;
import org.chromium.chrome.browser.vpn.wireguard.WireguardConfigUtils;
import org.chromium.chrome.browser.widget.quickactionsearchandbookmark.promo.SearchWidgetPromoPanel;
import org.chromium.chrome.browser.youtube_script_injector.QoraiYouTubeScriptInjectorNativeHelper;
import org.chromium.components.browser_ui.settings.SettingsNavigation;
import org.chromium.components.browser_ui.util.motion.MotionEventInfo;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.chromium.components.embedder_support.util.UrlUtilities;
import org.chromium.components.prefs.PrefChangeRegistrar;
import org.chromium.components.prefs.PrefChangeRegistrar.PrefObserver;
import org.chromium.components.safe_browsing.QoraiSafeBrowsingApiHandler;
import org.chromium.components.search_engines.TemplateUrl;
import org.chromium.components.search_engines.TemplateUrlService;
import org.chromium.components.user_prefs.UserPrefs;
import org.chromium.content_public.browser.LoadUrlParams;
import org.chromium.content_public.browser.MediaSession;
import org.chromium.content_public.browser.WebContents;
import org.chromium.misc_metrics.mojom.MiscAndroidMetrics;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;
import org.chromium.ui.KeyboardUtils;
import org.chromium.ui.widget.Toast;

import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;
import java.util.concurrent.CopyOnWriteArrayList;

/** Qorai's extension for ChromeActivity */
@JNINamespace("chrome::android")
@SuppressWarnings("UseSharedPreferencesManagerFromChromeCheck")
public abstract class QoraiActivity extends ChromeActivity
        implements BrowsingDataBridge.OnClearBrowsingDataListener,
                QoraiVpnObserver,
                ConnectionErrorHandler,
                PrefObserver,
                QoraiSafeBrowsingApiHandler.QoraiSafeBrowsingApiHandlerDelegate,
                MiscAndroidMetricsConnectionErrorHandler
                        .MiscAndroidMetricsConnectionErrorHandlerDelegate,
                QuickSearchEnginesCallback,
                KeyboardVisibilityHelper.KeyboardVisibilityListener,
                OnSharedPreferenceChangeListener {
    public static final String QORAI_WALLET_HOST = "wallet";
    public static final String QORAI_WALLET_ORIGIN = "qorai://wallet/";
    public static final String QORAI_WALLET_URL = "qorai://wallet/crypto/portfolio/assets";
    public static final String QORAI_BUY_URL = "qorai://wallet/crypto/fund-wallet";
    public static final String QORAI_SEND_URL = "qorai://wallet/send";
    public static final String QORAI_SWAP_URL = "qorai://wallet/swap";
    public static final String QORAI_DEPOSIT_URL = "qorai://wallet/crypto/deposit-funds";
    public static final String QORAI_REWARDS_SETTINGS_URL = "qorai://rewards/";
    public static final String QORAI_REWARDS_SETTINGS_WALLET_VERIFICATION_URL =
            "qorai://rewards/#verify";
    public static final String QORAI_REWARDS_WALLET_RECONNECT_URL = "qorai://rewards/reconnect";
    public static final String QORAI_REWARDS_SETTINGS_MONTHLY_URL = "qorai://rewards/#monthly";
    public static final String REWARDS_AC_SETTINGS_URL = "qorai://rewards/contribute";
    public static final String QORAI_REWARDS_RESET_PAGE = "qorai://rewards/#reset";
    public static final String QORAI_AI_CHAT_URL = "chrome-untrusted://chat/tab";
    public static final String REWARDS_LEARN_MORE_URL =
            "https://qorai.com/faq-rewards/#unclaimed-funds";
    public static final String QORAI_TERMS_PAGE =
            "https://basicattentiontoken.org/user-terms-of-service/";
    public static final String QORAI_PRIVACY_POLICY = "https://qorai.com/privacy/browser/#rewards";
    public static final String OPEN_URL = "open_url";
    public static final String QORAI_WEBCOMPAT_INFO_WIKI_URL =
            "https://github.com/qorai/qorai-browser/wiki/Web-compatibility-reports";
    private static final String KEY_RESUME_MEDIA_SESSION =
            "org.chromium.chrome.browser.app.KEY_RESUME_MEDIA_SESSION";

    private static final int DAYS_4 = 4;
    private static final int DAYS_7 = 7;

    private static final int MONTH_1 = 1;

    public static final int MAX_FAILED_CAPTCHA_ATTEMPTS = 10;

    public static final int APP_OPEN_COUNT_FOR_WIDGET_PROMO = 25;

    public static final String GOOGLE_SEARCH_ENGINE_KEYWORD = ":g";
    public static final String YOUTUBE_SEARCH_ENGINE_KEYWORD = ":yt";
    public static final String QORAI_SEARCH_ENGINE_KEYWORD = ":br";
    public static final String BING_SEARCH_ENGINE_KEYWORD = ":b";
    public static final String STARTPAGE_SEARCH_ENGINE_KEYWORD = ":sp";

    private static final boolean ENABLE_IN_APP_UPDATE =
            Build.VERSION.SDK_INT < Build.VERSION_CODES.UPSIDE_DOWN_CAKE;

    /** Settings for sending local notification reminders. */
    public static final String CHANNEL_ID = "com.qorai.browser";

    // Explicitly declare this variable to avoid build errors.
    // It will be removed in asm and parent variable will be used instead.
    private UnownedUserDataSupplier<BrowserControlsManager> mBrowserControlsManagerSupplier;

    private static final List<String> sYandexRegions =
            Arrays.asList("AM", "AZ", "BY", "KG", "KZ", "MD", "RU", "TJ", "TM", "UZ");

    private static final int PIP_UPDATE_DELAY_MS = 500;
    private boolean mIsVerification;
    public boolean mIsDeepLink;
    private QoraiWalletService mQoraiWalletService;
    private KeyringService mKeyringService;
    private JsonRpcService mJsonRpcService;
    private MiscAndroidMetrics mMiscAndroidMetrics;
    private SwapService mSwapService;
    @Nullable private WalletModel mWalletModel;
    private BlockchainRegistry mBlockchainRegistry;
    private TxService mTxService;
    private EthTxManagerProxy mEthTxManagerProxy;
    private SolanaTxManagerProxy mSolanaTxManagerProxy;
    private AssetRatioService mAssetRatioService;
    public boolean mLoadedFeed;
    public boolean mComesFromNewTab;
    public CopyOnWriteArrayList<FeedItemsCard> mNewsItemsFeedCards;
    private boolean mIsProcessingPendingDappsTxRequest;
    private int mLastTabId;
    private boolean mNativeInitialized;
    private boolean mSafeBrowsingFlagEnabled;
    private NewTabPageManager mNewTabPageManager;
    private UsageMonitor mUsageMonitor;
    private NotificationPermissionController mNotificationPermissionController;
    private MiscAndroidMetricsConnectionErrorHandler mMiscAndroidMetricsConnectionErrorHandler;
    private AppUpdateManager mAppUpdateManager;
    private boolean mWalletBadgeVisible;
    private boolean mSpoofCustomTab;
    // Boolean flag that indicates if the media session must be resumed
    // when switching in picture-in-picture mode.
    private boolean mResumeMediaSession;

    private View mQuickSearchEnginesView;

    private SearchWidgetPromoPanel mSearchWidgetPromoPanel;

    /** Serves as a general exception for failed attempts to get QoraiActivity. */
    public static class QoraiActivityNotFoundException extends Exception {
        public QoraiActivityNotFoundException(String message) {
            super(message);
        }
    }

    public QoraiActivity() {}

    @Override
    protected void onPostCreate() {
        super.onPostCreate();
        final Bundle savedInstanceState = getSavedInstanceState();
        if (savedInstanceState != null) {
            mResumeMediaSession = savedInstanceState.getBoolean(KEY_RESUME_MEDIA_SESSION, false);
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putBoolean(KEY_RESUME_MEDIA_SESSION, mResumeMediaSession);
    }

    @Override
    public void onResumeWithNative() {
        super.onResumeWithNative();
        QoraiActivityJni.get().restartStatsUpdater();
        if (QoraiVpnUtils.isVpnFeatureSupported(QoraiActivity.this)) {
            QoraiVpnNativeWorker.getInstance().addObserver(this);
            QoraiVpnUtils.reportBackgroundUsageP3A();
        }

        // The check on mNativeInitialized is mostly to ensure that mojo
        // services for wallet are initialized.
        // TODO(sergz): verify do we need it in that phase or not.
        if (mNativeInitialized) {
            QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
            if (layout != null && layout.isWalletIconVisible()) {
                updateWalletBadgeVisibility();
            }

            // If a full screen custom tab was closed and bottom controls are enabled,
            // show the bottom toolbar controls again
            if (FullScreenCustomTabActivity.sIsFullScreenCustomTabActivityClosed
                    && BottomToolbarConfiguration.isQoraiBottomControlsEnabled()) {
                layout.onBottomControlsVisibilityChanged(true);
            }
            // Reset the flag tracking whether a full screen custom tab was closed
            FullScreenCustomTabActivity.sIsFullScreenCustomTabActivityClosed = false;
        }

        QoraiSafeBrowsingApiHandler.getInstance()
                .setDelegate(QoraiActivityJni.get().getSafeBrowsingApiKey(), this);

        // We can store a state of that flag as a browser has to be restarted
        // when the flag state is changed in any case
        mSafeBrowsingFlagEnabled =
                ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_ANDROID_SAFE_BROWSING);

        executeInitSafeBrowsing(0);

        if (ENABLE_IN_APP_UPDATE) {
            if (mAppUpdateManager == null) {
                mAppUpdateManager = AppUpdateManagerFactory.create(QoraiActivity.this);
            }
            mAppUpdateManager
                    .getAppUpdateInfo()
                    .addOnSuccessListener(
                            appUpdateInfo -> {
                                if (appUpdateInfo.installStatus() == InstallStatus.DOWNLOADED) {
                                    completeUpdateSnackbar();
                                }
                            });
        }
        // Executes Qora voice prompt if it was triggered from quick search app widget
        maybeExecuteQoraVoicePrompt();
    }

    @Override
    public void onPauseWithNative() {
        if (mUsageMonitor != null) {
            mUsageMonitor.stop();
        }
        if (QoraiVpnUtils.isVpnFeatureSupported(QoraiActivity.this)) {
            QoraiVpnNativeWorker.getInstance().removeObserver(this);
        }
        super.onPauseWithNative();
    }

    @Override
    public boolean onMenuOrKeyboardAction(
            int id, boolean fromMenu, @Nullable MotionEventInfo triggeringMotion) {
        final Tab currentTab = getActivityTab();
        // Handle items replaced by Qorai.
        if (id == R.id.info_menu_id && currentTab != null) {
            ShareDelegate shareDelegate = (ShareDelegate) getShareDelegateSupplier().get();
            shareDelegate.share(currentTab, false, ShareOrigin.OVERFLOW_MENU);
            return true;
        } else if (id == R.id.reload_menu_id) {
            setComesFromNewTab(true);
        } else if (id == R.id.preferences_id) {
            final AppMenuPropertiesDelegate delegate = createAppMenuPropertiesDelegate();
            assert delegate instanceof QoraiTabbedAppMenuPropertiesDelegate;
            final QoraiTabbedAppMenuPropertiesDelegate qoraiTabbedAppMenuPropertiesDelegate =
                    (QoraiTabbedAppMenuPropertiesDelegate) delegate;

            final Bundle bundle =
                    CustomizeQoraiMenu.populateBundle(
                            getResources(),
                            new Bundle(),
                            qoraiTabbedAppMenuPropertiesDelegate.buildMainMenuModelList(),
                            qoraiTabbedAppMenuPropertiesDelegate.buildPageActionsModelList());
            SettingsNavigation settingsNavigation =
                    SettingsNavigationFactory.createSettingsNavigation();
            // Follow upstream code and pass null as fragment to show
            // that defaults to main settings screen.
            settingsNavigation.startSettings(this, null, bundle);
            return true;
        }

        if (super.onMenuOrKeyboardAction(id, fromMenu, triggeringMotion)) {
            return true;
        }

        // Handle items added by Qorai.
        if (currentTab == null) {
            return false;
        } else if (id == R.id.exit_id) {
            exitQorai();
        } else if (id == R.id.set_default_browser) {
            QoraiSetDefaultBrowserUtils.openDefaultAppsSettings(QoraiActivity.this);
        } else if (id == R.id.qorai_rewards_id) {
            showRewardsPage();
        } else if (id == R.id.qorai_wallet_id) {
            openQoraiWallet(false, false, false);
        } else if (id == R.id.qorai_playlist_id) {
            openPlaylist(true);
        } else if (id == R.id.add_to_playlist_id) {
            QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
            layout.addMediaToPlaylist();
        } else if (id == R.id.qorai_news_id) {
            openQoraiNewsSettings();
        } else if (id == R.id.request_qorai_vpn_id || id == R.id.request_qorai_vpn_check_id) {
            if (!InternetConnection.isNetworkAvailable(QoraiActivity.this)) {
                Toast.makeText(QoraiActivity.this, R.string.no_internet, Toast.LENGTH_SHORT).show();
            } else {
                if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(QoraiActivity.this)) {
                    TimerDialogFragment timerDialogFragment = new TimerDialogFragment();
                    timerDialogFragment.show(getSupportFragmentManager(), TimerDialogFragment.TAG);
                } else {
                    if (QoraiVpnNativeWorker.getInstance().isPurchasedUser()) {
                        QoraiVpnPrefUtils.setSubscriptionPurchase(true);
                        if (WireguardConfigUtils.isConfigExist(QoraiActivity.this)) {
                            QoraiVpnProfileUtils.getInstance().startVpn(QoraiActivity.this);
                        } else {
                            QoraiVpnUtils.openQoraiVpnProfileActivity(QoraiActivity.this);
                        }
                    } else {
                        QoraiVpnUtils.showProgressDialog(
                                QoraiActivity.this,
                                getResources().getString(R.string.vpn_connect_text));
                        if (QoraiVpnPrefUtils.isSubscriptionPurchase()) {
                            verifySubscription();
                        } else {
                            QoraiVpnUtils.dismissProgressDialog();
                            QoraiVpnUtils.openQoraiVpnPlansActivity(QoraiActivity.this);
                        }
                    }
                }
            }
        } else if (id == R.id.request_vpn_location_id || id == R.id.request_vpn_location_icon_id) {
            QoraiVpnUtils.openVpnServerSelectionActivity(QoraiActivity.this);
        } else if (id == R.id.qorai_qora_id) {
            openQoraiQora();
        } else if (id == CustomizeQoraiMenu.QORAI_CUSTOMIZE_ITEM_ID) {
            final AppMenuPropertiesDelegate delegate = createAppMenuPropertiesDelegate();
            assert delegate instanceof QoraiTabbedAppMenuPropertiesDelegate;
            final QoraiTabbedAppMenuPropertiesDelegate qoraiTabbedAppMenuPropertiesDelegate =
                    (QoraiTabbedAppMenuPropertiesDelegate) delegate;
            // Get full menu items and pass them to settings.
            CustomizeQoraiMenu.openCustomizeMenuSettings(
                    this,
                    qoraiTabbedAppMenuPropertiesDelegate.buildMainMenuModelList(),
                    qoraiTabbedAppMenuPropertiesDelegate.buildPageActionsModelList());
        } else {
            return false;
        }
        return true;
    }

    // Handles only wallet related mojo failures. Don't add handlers for mojo connections that
    // are not related to wallet functionality.
    @Override
    public void onConnectionError(MojoException e) {
        cleanUpWalletNativeServices();
        initWalletNativeServices();
    }

    @Override
    protected void onDestroyInternal() {
        if (mNotificationPermissionController != null) {
            NotificationPermissionController.detach(mNotificationPermissionController);
            mNotificationPermissionController = null;
        }

        QoraiSafeBrowsingApiHandler.getInstance().shutdownSafeBrowsing();
        if (ENABLE_IN_APP_UPDATE && mAppUpdateManager != null) {
            mAppUpdateManager.unregisterListener(mInstallStateUpdatedListener);
        }
        super.onDestroyInternal();
        cleanUpWalletNativeServices();
        cleanUpMiscAndroidMetrics();
    }

    @Override
    public void onPictureInPictureModeChanged(boolean inPicture, Configuration newConfig) {
        super.onPictureInPictureModeChanged(inPicture, newConfig);
        if (mResumeMediaSession) {
            mResumeMediaSession = false;
            MediaSession mediaSession = MediaSession.fromWebContents(getCurrentWebContents());
            if (mediaSession != null) {
                mediaSession.resume();
            }
            // Adopting the same workaround adopted upstream, to check the full implementation
            // see FullscreenVideoPictureInPictureController class.
            // Post a delayed handler to update the Pip status, once things have had some
            // time to settle. When switching into fullscreen mode sometimes the transition is
            // called before relayout has happened, causing the source rectangle for the Pip
            // transition to be wrong. This causes the Pip window to look like it moves to the
            // wrong part of the screen and partially clipped before snapping to its normal place.
            PostTask.postDelayedTask(
                    TaskTraits.UI_BEST_EFFORT,
                    (Runnable)
                            () ->
                                    setPictureInPictureParams(
                                            new PictureInPictureParams.Builder().build()),
                    PIP_UPDATE_DELAY_MS);
        }
        if (!inPicture
                && getCurrentWebContents() != null
                && QoraiYouTubeScriptInjectorNativeHelper.isPictureInPictureAvailable(
                        getCurrentWebContents())) {
            // PiP has been dismissed when watching a YT video, then pause it.
            MediaSession mediaSession = MediaSession.fromWebContents(getCurrentWebContents());
            if (mediaSession != null) {
                mediaSession.suspend();
            }
            FullscreenManager fullscreenManager = getFullscreenManager();
            if (fullscreenManager.getPersistentFullscreenMode()) {
                fullscreenManager.exitPersistentFullscreenMode();
            }
        }
    }

    /**
     * Gets Wallet model for Qorai activity. It may be {@code null} if native initialization has not
     * completed yet.
     */
    @Nullable
    public WalletModel getWalletModel() {
        return mWalletModel;
    }

    private void setWalletBadgeVisibility(boolean visible) {
        mWalletBadgeVisible = visible;
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.updateWalletBadgeVisibility(visible);
    }

    private void maybeShowPendingTransactions() {
        if (mWalletModel != null) {
            // Trigger observer to refresh the transactions and process any pending request.
            mWalletModel.getCryptoModel().refreshTransactions();
        }
    }

    private void maybeShowSignSolTransactionsRequestLayout(
            @NonNull final Runnable openWalletPanelRunnable) {
        assert mQoraiWalletService != null;
        mQoraiWalletService.getPendingSignSolTransactionsRequests(
                requests -> {
                    if (requests != null && requests.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType.SIGN_SOL_TRANSACTIONS);
                        return;
                    }
                    maybeShowSignMessageErrorsLayout(openWalletPanelRunnable);
                });
    }

    private void maybeShowSignMessageErrorsLayout(@NonNull final Runnable openWalletPanelRunnable) {
        assert mQoraiWalletService != null;
        mQoraiWalletService.getPendingSignMessageErrors(
                errors -> {
                    if (errors != null && errors.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType.SIGN_MESSAGE_ERROR);
                    }
                });
        maybeShowSignMessageRequestLayout(openWalletPanelRunnable);
    }

    private void maybeShowSignMessageRequestLayout(
            @NonNull final Runnable openWalletPanelRunnable) {
        assert mQoraiWalletService != null;
        mQoraiWalletService.getPendingSignMessageRequests(
                requests -> {
                    if (requests != null && requests.length != 0) {
                        QoraiWalletDAppsActivity.ActivityType activityType =
                                (requests[0].signData.which() == SignDataUnion.Tag.EthSiweData)
                                        ? QoraiWalletDAppsActivity.ActivityType.SIWE_MESSAGE
                                        : QoraiWalletDAppsActivity.ActivityType.SIGN_MESSAGE;
                        openQoraiWalletDAppsActivity(activityType);
                        return;
                    }
                    maybeShowChainRequestLayout(openWalletPanelRunnable);
                });
    }

    private void maybeShowChainRequestLayout(@NonNull final Runnable openWalletPanelRunnable) {
        assert mJsonRpcService != null;
        mJsonRpcService.getPendingAddChainRequests(
                networks -> {
                    if (networks != null && networks.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType.ADD_ETHEREUM_CHAIN);

                        return;
                    }
                    maybeShowSwitchChainRequestLayout(openWalletPanelRunnable);
                });
    }

    private void maybeShowSwitchChainRequestLayout(
            @NonNull final Runnable openWalletPanelRunnable) {
        assert mJsonRpcService != null;
        mJsonRpcService.getPendingSwitchChainRequests(
                requests -> {
                    if (requests != null && requests.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType.SWITCH_ETHEREUM_CHAIN);

                        return;
                    }
                    maybeShowAddSuggestTokenRequestLayout(openWalletPanelRunnable);
                });
    }

    private void maybeShowAddSuggestTokenRequestLayout(
            @NonNull final Runnable openWalletPanelRunnable) {
        assert mQoraiWalletService != null;
        mQoraiWalletService.getPendingAddSuggestTokenRequests(
                requests -> {
                    if (requests != null && requests.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType.ADD_TOKEN);

                        return;
                    }
                    maybeShowGetEncryptionPublicKeyRequestLayout(openWalletPanelRunnable);
                });
    }

    private void maybeShowGetEncryptionPublicKeyRequestLayout(
            @NonNull final Runnable openWalletPanelRunnable) {
        assert mQoraiWalletService != null;
        mQoraiWalletService.getPendingGetEncryptionPublicKeyRequests(
                requests -> {
                    if (requests != null && requests.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType
                                        .GET_ENCRYPTION_PUBLIC_KEY_REQUEST);

                        return;
                    }
                    maybeShowDecryptRequestLayout(openWalletPanelRunnable);
                });
    }

    private void maybeShowDecryptRequestLayout(@NonNull final Runnable openWalletPanelRunnable) {
        assert mQoraiWalletService != null;
        mQoraiWalletService.getPendingDecryptRequests(
                requests -> {
                    if (requests != null && requests.length != 0) {
                        openQoraiWalletDAppsActivity(
                                QoraiWalletDAppsActivity.ActivityType.DECRYPT_REQUEST);

                        return;
                    }
                    openWalletPanelRunnable.run();
                });
    }

    public void dismissWalletPanelOrDialog() {
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.dismissWalletPanelOrDialog();
    }

    public void showWalletPanel(final boolean ignoreWeb3NotificationPreference) {
        showWalletPanel(true, ignoreWeb3NotificationPreference);
    }

    public void showWalletPanel(
            final boolean showPendingTransactions, final boolean ignoreWeb3NotificationPreference) {
        final QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.showWalletIcon(true);
        if (!ignoreWeb3NotificationPreference
                && !QoraiWalletPreferences.getPrefWeb3NotificationsEnabled()) {
            return;
        }
        assert mKeyringService != null;
        mKeyringService.isLocked(
                locked -> {
                    if (locked) {
                        if (showPendingTransactions) {
                            layout.showWalletPanel();
                        }
                        return;
                    }
                    mKeyringService.hasPendingUnlockRequest(
                            pending -> {
                                if (pending) {
                                    layout.showWalletPanel();
                                    return;
                                }
                                // Create a runnable that opens the Wallet
                                // if the pending requests reach the end of the chain
                                // without returning earlier.
                                final Runnable openWalletPanelRunnable =
                                        () -> {
                                            if (showPendingTransactions && mWalletBadgeVisible) {
                                                maybeShowPendingTransactions();
                                            } else {
                                                getQoraiToolbarLayout().showWalletPanel();
                                            }
                                        };
                                maybeShowSignSolTransactionsRequestLayout(openWalletPanelRunnable);
                            });
                });
    }

    public void showWalletOnboarding() {
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.showWalletIcon(true);
        if (!QoraiWalletPreferences.getPrefWeb3NotificationsEnabled()) {
            return;
        }
        layout.showWalletPanel();
    }

    public void walletInteractionDetected(WebContents webContents) {
        Tab tab = getActivityTab();
        if (tab == null
                || !webContents.getLastCommittedUrl().equals(
                        tab.getWebContents().getLastCommittedUrl())) {
            return;
        }
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.showWalletIcon(true);
        updateWalletBadgeVisibility();
    }

    public void showAccountCreation(@CoinType.EnumType int coinType) {
        if (mWalletModel != null) {
            mWalletModel.getDappsModel().addAccountCreationRequest(coinType);
        }
    }

    private void updateWalletBadgeVisibility() {
        if (mWalletModel != null) {
            mWalletModel.getDappsModel().updateWalletBadgeVisibility();
        }
    }

    private void verifySubscription() {
        MutableLiveData<PurchaseModel> _activePurchases = new MutableLiveData();
        LiveData<PurchaseModel> activePurchases = _activePurchases;
        InAppPurchaseWrapper.getInstance()
                .queryPurchases(_activePurchases, InAppPurchaseWrapper.SubscriptionProduct.VPN);
        LiveDataUtil.observeOnce(
                activePurchases,
                activePurchaseModel -> {
                    if (activePurchaseModel != null) {
                        QoraiVpnNativeWorker.getInstance()
                                .verifyPurchaseToken(
                                        activePurchaseModel.getPurchaseToken(),
                                        activePurchaseModel.getProductId(),
                                        QoraiVpnUtils.SUBSCRIPTION_PARAM_TEXT,
                                        getPackageName());
                    } else {
                        QoraiVpnApiResponseUtils.queryPurchaseFailed(QoraiActivity.this);
                        if (!mIsVerification) {
                            QoraiVpnUtils.openQoraiVpnPlansActivity(QoraiActivity.this);
                        }
                    }
                });
    }

    @Override
    public boolean onOptionsItemSelected(
            int itemId, @Nullable Bundle menuItemData, @Nullable MotionEventInfo triggeringMotion) {
        if (itemId == R.id.new_tab_menu_id) {
            LayoutManagerChrome layoutManager =
                    (LayoutManagerChrome)
                            QoraiReflectionUtil.getField(
                                    ChromeTabbedActivity.class, "mLayoutManager", this);
            if (layoutManager != null
                    && layoutManager.getHubLayoutForTesting() != null
                    && !layoutManager.getHubLayoutForTesting().isActive()
                    && mMiscAndroidMetrics != null) {
                mMiscAndroidMetrics.recordAppMenuNewTab();
            }
        } else if (itemId == R.id.home_menu_id) {
            if (getToolbarManager() instanceof QoraiToolbarManager) {
                ((QoraiToolbarManager) getToolbarManager()).openHomepage();
            }
        }
        return super.onOptionsItemSelected(itemId, menuItemData, triggeringMotion);
    }

    @Override
    public void onVerifyPurchaseToken(
            String jsonResponse, String purchaseToken, String productId, boolean isSuccess) {
        if (isSuccess) {
            Long purchaseExpiry = QoraiVpnUtils.getPurchaseExpiryDate(jsonResponse);
            int paymentState = QoraiVpnUtils.getPaymentState(jsonResponse);
            if (purchaseExpiry > 0 && purchaseExpiry >= System.currentTimeMillis()) {
                QoraiVpnPrefUtils.setPurchaseToken(purchaseToken);
                QoraiVpnPrefUtils.setProductId(productId);
                QoraiVpnPrefUtils.setPurchaseExpiry(purchaseExpiry);
                QoraiVpnPrefUtils.setSubscriptionPurchase(true);
                QoraiVpnPrefUtils.setPaymentState(paymentState);
                if (QoraiVpnPrefUtils.isResetConfiguration()) {
                    QoraiVpnUtils.dismissProgressDialog();
                    QoraiVpnUtils.openQoraiVpnProfileActivity(QoraiActivity.this);
                } else {
                    if (!mIsVerification) {
                        checkForVpn();
                    } else {
                        mIsVerification = false;
                        if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(
                                    QoraiActivity.this)
                                && !TextUtils.isEmpty(QoraiVpnPrefUtils.getHostname())
                                && !TextUtils.isEmpty(QoraiVpnPrefUtils.getClientId())
                                && !TextUtils.isEmpty(QoraiVpnPrefUtils.getSubscriberCredential())
                                && !TextUtils.isEmpty(QoraiVpnPrefUtils.getApiAuthToken())) {
                            QoraiVpnNativeWorker.getInstance().verifyCredentials(
                                    QoraiVpnPrefUtils.getHostname(),
                                    QoraiVpnPrefUtils.getClientId(),
                                    QoraiVpnPrefUtils.getSubscriberCredential(),
                                    QoraiVpnPrefUtils.getApiAuthToken());
                        }
                    }
                    QoraiVpnUtils.dismissProgressDialog();
                }
            } else {
                QoraiVpnApiResponseUtils.queryPurchaseFailed(QoraiActivity.this);
                if (!mIsVerification) {
                    QoraiVpnUtils.openQoraiVpnPlansActivity(QoraiActivity.this);
                }
                mIsVerification = false;
            }
        } else {
            QoraiVpnApiResponseUtils.queryPurchaseFailed(QoraiActivity.this);
            if (!mIsVerification) {
                QoraiVpnUtils.openQoraiVpnPlansActivity(QoraiActivity.this);
            }
            mIsVerification = false;
        }
    };

    private void checkForVpn() {
        QoraiVpnNativeWorker.getInstance().reportForegroundP3A();
        new Thread() {
            @Override
            public void run() {
                Intent intent = GoBackend.VpnService.prepare(QoraiActivity.this);
                if (intent != null
                        || !WireguardConfigUtils.isConfigExist(getApplicationContext())) {
                    QoraiVpnUtils.dismissProgressDialog();
                    QoraiVpnUtils.openQoraiVpnProfileActivity(QoraiActivity.this);
                    return;
                }
                QoraiVpnProfileUtils.getInstance().startVpn(QoraiActivity.this);
            }
        }.start();
    }

    @Override
    public void onVerifyCredentials(String jsonVerifyCredentials, boolean isSuccess) {
        if (!isSuccess) {
            if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(QoraiActivity.this)) {
                QoraiVpnProfileUtils.getInstance().stopVpn(QoraiActivity.this);
            }
            Intent qoraiVpnProfileIntent =
                    new Intent(QoraiActivity.this, QoraiVpnProfileActivity.class);
            qoraiVpnProfileIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            qoraiVpnProfileIntent.putExtra(QoraiVpnUtils.VERIFY_CREDENTIALS_FAILED, true);
            qoraiVpnProfileIntent.setAction(Intent.ACTION_VIEW);
            startActivity(qoraiVpnProfileIntent);
        }
    }

    @Override
    public void initializeState() {
        super.initializeState();
        if (isNoRestoreState()) {
            CommandLine.getInstance().appendSwitch(ChromeSwitches.NO_RESTORE_STATE);
        }

        if (isClearBrowsingDataOnExit()) {
            List<Integer> dataTypes =
                    Arrays.asList(
                            BrowsingDataType.HISTORY,
                            BrowsingDataType.SITE_DATA,
                            BrowsingDataType.CACHE);

            int[] dataTypesArray = CollectionUtil.integerCollectionToIntArray(dataTypes);

            // has onBrowsingDataCleared() as an @Override callback from implementing
            // BrowsingDataBridge.OnClearBrowsingDataListener
            BrowsingDataBridge.getForProfile(getCurrentProfile())
                    .clearBrowsingData(this, dataTypesArray, TimePeriod.ALL_TIME);
        }

        setLoadedFeed(false);
        setComesFromNewTab(false);
        setNewsItemsFeedCards(null);
        QoraiSearchEngineUtils.initializeQoraiSearchEngineStates(getTabModelSelector());
        Intent intent = getIntent();
        if (intent != null
                && intent.getBooleanExtra(QoraiWalletActivity.RESTART_WALLET_ACTIVITY, false)) {
            openQoraiWallet(
                    false,
                    intent.getBooleanExtra(
                            QoraiWalletActivity.RESTART_WALLET_ACTIVITY_SETUP, false),
                    intent.getBooleanExtra(
                            QoraiWalletActivity.RESTART_WALLET_ACTIVITY_RESTORE, false));
        }
    }

    public int getLastTabId() {
        return mLastTabId;
    }

    public void setLastTabId(int lastTabId) {
        this.mLastTabId = lastTabId;
    }

    public boolean isLoadedFeed() {
        return mLoadedFeed;
    }

    public void setLoadedFeed(boolean loadedFeed) {
        this.mLoadedFeed = loadedFeed;
    }

    public CopyOnWriteArrayList<FeedItemsCard> getNewsItemsFeedCards() {
        return mNewsItemsFeedCards;
    }

    public void setNewsItemsFeedCards(CopyOnWriteArrayList<FeedItemsCard> newsItemsFeedCards) {
        this.mNewsItemsFeedCards = newsItemsFeedCards;
    }

    public void setComesFromNewTab(boolean comesFromNewTab) {
        this.mComesFromNewTab = comesFromNewTab;
    }

    public boolean isComesFromNewTab() {
        return mComesFromNewTab;
    }

    @Override
    public void onBrowsingDataCleared() {}

    @Override
    public void onResume() {
        super.onResume();
        mIsProcessingPendingDappsTxRequest = false;

        PostTask.postTask(
                TaskTraits.BEST_EFFORT_MAY_BLOCK, () -> { QoraiStatsUtil.removeShareStatsFile(); });

        // We need to enable widget promo for later release
        /* int appOpenCountForWidgetPromo = SharedPreferencesManager.getInstance().readInt(
                QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT_FOR_WIDGET_PROMO);
        if (appOpenCountForWidgetPromo < APP_OPEN_COUNT_FOR_WIDGET_PROMO) {
            SharedPreferencesManager.getInstance().writeInt(
                    QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT_FOR_WIDGET_PROMO,
                    appOpenCountForWidgetPromo + 1);
        } */
        if (mUsageMonitor != null) {
            mUsageMonitor.start();
        }
    }

    @Override
    public void performPostInflationStartup() {
        super.performPostInflationStartup();

        createNotificationChannel();
    }

    @Override
    protected void initializeStartupMetrics() {
        super.initializeStartupMetrics();

        // Disable FRE for arm64 builds where ChromeActivity is the one that
        // triggers FRE instead of ChromeLauncherActivity on arm32 build.
        QoraiHelper.disableFREDRP();
    }

    @Override
    public void onPreferenceChange() {
        String captchaID =
                UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                        .getString(QoraiPref.SCHEDULED_CAPTCHA_ID);
        String paymentID =
                UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                        .getString(QoraiPref.SCHEDULED_CAPTCHA_PAYMENT_ID);
        if (QoraiQAPreferences.shouldVlogRewards()) {
            Log.e(
                    AdaptiveCaptchaHelper.TAG,
                    "captchaID : " + captchaID + " Payment ID : " + paymentID);
        }
        maybeSolveAdaptiveCaptcha();
    }

    @Override
    public void turnSafeBrowsingOff() {
        SafeBrowsingBridge safeBrowsingBridge = new SafeBrowsingBridge(getCurrentProfile());
        safeBrowsingBridge.setSafeBrowsingState(SafeBrowsingState.NO_SAFE_BROWSING);
    }

    // Shows SafeBrowsing errors if the switch in Developer Options is on
    @Override
    public void maybeShowSafeBrowsingError(String error) {
        if (ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiPreferenceKeys.QORAI_SAFE_BROWSING_ERRORS, false)) {
            Toast.makeText(QoraiActivity.this, error, Toast.LENGTH_LONG).show();
        }
    }

    @Override
    public boolean isSafeBrowsingEnabled() {
        return mSafeBrowsingFlagEnabled;
    }

    @Override
    public Activity getActivity() {
        return this;
    }

    public void maybeSolveAdaptiveCaptcha() {
        String captchaID =
                UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                        .getString(QoraiPref.SCHEDULED_CAPTCHA_ID);
        String paymentID =
                UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                        .getString(QoraiPref.SCHEDULED_CAPTCHA_PAYMENT_ID);
        if (!TextUtils.isEmpty(captchaID) && !TextUtils.isEmpty(paymentID)) {
            AdaptiveCaptchaHelper.startAttestation(captchaID, paymentID);
        }
    }

    @Override
    public void finishNativeInitialization() {
        super.finishNativeInitialization();

        boolean isFirstInstall = PackageUtils.isFirstInstall(this);

        String countryCode = Locale.getDefault().getCountry();

        QoraiVpnNativeWorker.getInstance().reloadPurchasedState();

        QoraiHelper.maybeMigrateSettings();

        PrefChangeRegistrar mPrefChangeRegistrar = PrefServiceUtil.createFor(getCurrentProfile());
        mPrefChangeRegistrar.addObserver(QoraiPref.SCHEDULED_CAPTCHA_ID, this);

        if (UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                        .getInteger(QoraiPref.SCHEDULED_CAPTCHA_FAILED_ATTEMPTS)
                >= MAX_FAILED_CAPTCHA_ATTEMPTS) {
            UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                    .setBoolean(QoraiPref.SCHEDULED_CAPTCHA_PAUSED, true);
        }

        if (QoraiQAPreferences.shouldVlogRewards()) {
            Log.e(
                    AdaptiveCaptchaHelper.TAG,
                    "Failed attempts : "
                            + UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                                    .getInteger(QoraiPref.SCHEDULED_CAPTCHA_FAILED_ATTEMPTS));
        }
        if (!UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                .getBoolean(QoraiPref.SCHEDULED_CAPTCHA_PAUSED)) {
            maybeSolveAdaptiveCaptcha();
        }

        if (ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiPreferenceKeys.QORAI_DOUBLE_RESTART, false)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPreferenceKeys.QORAI_DOUBLE_RESTART, false);
            QoraiRelaunchUtils.restart();
            return;
        }

        // Make sure this option is disabled
        if (PreloadPagesSettingsBridge.getState(getCurrentProfile())
                != PreloadPagesState.NO_PRELOADING) {
            PreloadPagesSettingsBridge.setState(
                    getCurrentProfile(), PreloadPagesState.NO_PRELOADING);
        }

        if (QoraiRewardsHelper.hasRewardsEnvChange()) {
            QoraiPrefServiceBridge.getInstance().resetPromotionLastFetchStamp();
            QoraiRewardsHelper.setRewardsEnvChange(false);
        }

        int appOpenCount =
                ChromeSharedPreferences.getInstance()
                        .readInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT);
        ChromeSharedPreferences.getInstance()
                .writeInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT, appOpenCount + 1);

        if (isFirstInstall && appOpenCount == 0) {
            checkForYandexSE();
            enableSearchSuggestions();
            setQoraiAsDefaultPrivateMode();
        }

        if (!isFirstInstall
                && countryCode.equals(QoraiConstants.JAPAN_COUNTRY_CODE)
                && !ChromeSharedPreferences.getInstance()
                        .readBoolean(
                                QoraiPreferenceKeys.QORAI_DEFAULT_SEARCH_ENGINE_MIGRATED_JP,
                                false)) {
            applyChangesForYahooJp();
        }

        QoraiSetDefaultBrowserUtils.checkForQoraiSetDefaultBrowser(
                appOpenCount, QoraiActivity.this);

        Context app = ContextUtils.getApplicationContext();
        if (null != app
                && QoraiReflectionUtil.equalTypes(this.getClass(), ChromeTabbedActivity.class)) {
            // Trigger QoraiSyncWorker CTOR to make migration from sync v1 if sync is enabled
            QoraiSyncWorker.get();
        }

        initMiscAndroidMetrics();
        checkForNotificationData();

        if (RateUtils.getInstance().isLastSessionShown()) {
            RateUtils.getInstance().setPrefNextRateDate();
            RateUtils.getInstance().setLastSessionShown(false);
        }

        if (!RateUtils.getInstance().getPrefRateEnabled()) {
            RateUtils.getInstance().setPrefRateEnabled(true);
            RateUtils.getInstance().setPrefNextRateDate();
        }
        RateUtils.getInstance().setTodayDate();

        if (RateUtils.getInstance().shouldShowRateDialog(this)) {
            showQoraiRateDialog();
            RateUtils.getInstance().setLastSessionShown(true);
        }

        // TODO commenting out below code as we may use it in next release

        // if (PackageUtils.isFirstInstall(this)
        //         &&
        //
        // SharedPreferencesManager.getInstance().readInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT)
        //         == 1) {
        //     Calendar calender = Calendar.getInstance();
        //     calender.setTime(new Date());
        //     calender.add(Calendar.DATE, DAYS_4);
        //     OnboardingPrefManager.getInstance().setNextOnboardingDate(
        //         calender.getTimeInMillis());
        // }

        // OnboardingActivity onboardingActivity = null;
        // for (Activity ref : ApplicationStatus.getRunningActivities()) {
        //     if (!(ref instanceof OnboardingActivity)) continue;

        //     onboardingActivity = (OnboardingActivity) ref;
        // }

        // if (onboardingActivity == null
        //         && OnboardingPrefManager.getInstance().showOnboardingForSkip(this)) {
        //     OnboardingPrefManager.getInstance().showOnboarding(this);
        //     OnboardingPrefManager.getInstance().setOnboardingShownForSkip(true);
        // }

        QoraiSyncAccountDeletedInformer.show();

        if (!OnboardingPrefManager.getInstance().isOneTimeNotificationStarted() && isFirstInstall) {
            RetentionNotificationUtil.scheduleNotification(this, RetentionNotificationUtil.HOUR_3);
            RetentionNotificationUtil.scheduleNotification(this, RetentionNotificationUtil.HOUR_24);
            RetentionNotificationUtil.scheduleNotification(this, RetentionNotificationUtil.DAY_6);
            RetentionNotificationUtil.scheduleNotification(this, RetentionNotificationUtil.DAY_10);
            RetentionNotificationUtil.scheduleNotification(this, RetentionNotificationUtil.DAY_30);
            RetentionNotificationUtil.scheduleNotification(this, RetentionNotificationUtil.DAY_35);
            OnboardingPrefManager.getInstance().setOneTimeNotificationStarted(true);
        }

        if (isFirstInstall
                && ChromeSharedPreferences.getInstance()
                                .readInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT)
                        == 1) {
            Calendar calender = Calendar.getInstance();
            calender.setTime(new Date());
            calender.add(Calendar.DATE, DAYS_4);
            QoraiRewardsHelper.setNextRewardsOnboardingModalDate(calender.getTimeInMillis());
        }

        checkFingerPrintingOnUpgrade(isFirstInstall);
        checkForVpnCallout();

        if (ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_VPN_LINK_SUBSCRIPTION_ANDROID_UI)
                && QoraiVpnPrefUtils.isSubscriptionPurchase()
                && !QoraiVpnPrefUtils.isLinkSubscriptionDialogShown()) {
            showLinkVpnSubscriptionDialog();
        }
        if (isFirstInstall
                && (OnboardingPrefManager.getInstance().isDormantUsersEngagementEnabled()
                        || getPackageName().equals(QoraiConstants.QORAI_PRODUCTION_PACKAGE_NAME))) {
            OnboardingPrefManager.getInstance().setDormantUsersPrefs();
            if (!OnboardingPrefManager.getInstance().isDormantUsersNotificationsStarted()) {
                RetentionNotificationUtil.scheduleDormantUsersNotifications(this);
                OnboardingPrefManager.getInstance().setDormantUsersNotificationsStarted(true);
            }
        }
        initWalletNativeServices();

        mNativeInitialized = true;

        if (countryCode.equals(QoraiConstants.INDIA_COUNTRY_CODE)
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.QORAI_AD_FREE_CALLOUT_DIALOG, true)
                && getActivityTab() != null
                && getActivityTab().getUrl().getSpec() != null
                && UrlUtilities.isNtpUrl(getActivityTab().getUrl().getSpec())
                && (ChromeSharedPreferences.getInstance()
                                .readBoolean(QoraiPreferenceKeys.QORAI_OPENED_YOUTUBE, false)
                        || ChromeSharedPreferences.getInstance()
                                        .readInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT)
                                >= 7)) {
            showAdFreeCalloutDialog();
        }

        initQoraiNews();
        if (ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiPreferenceKeys.QORAI_DEFERRED_DEEPLINK_PLAYLIST, false)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPreferenceKeys.QORAI_DEFERRED_DEEPLINK_PLAYLIST, false);
            openPlaylist(false);
        } else if (ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiPreferenceKeys.QORAI_DEFERRED_DEEPLINK_VPN, false)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPreferenceKeys.QORAI_DEFERRED_DEEPLINK_VPN, false);
            handleDeepLinkVpn();
        }

        // Added to reset app links settings for upgrade case
        if (!isFirstInstall
                && !ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPrivacySettings.PREF_APP_LINKS, true)
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPrivacySettings.PREF_APP_LINKS_RESET, true)) {
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPrivacySettings.PREF_APP_LINKS, true);
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPrivacySettings.PREF_APP_LINKS_RESET, false);
        }

        if (isFirstInstall
                && ChromeSharedPreferences.getInstance()
                                .readInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT)
                        == 1) {
            Calendar calendar = Calendar.getInstance();
            calendar.setTime(new Date());
            calendar.add(Calendar.DATE, DAYS_7);
            QoraiRewardsHelper.setRewardsOnboardingIconTiming(calendar.getTimeInMillis());

            if (ENABLE_IN_APP_UPDATE) {
                setInAppUpdateTiming();
            }
        }

        // Check multiwindow toggle for upgrade case
        if (!isFirstInstall
                && !QoraiMultiWindowUtils.isCheckUpgradeEnableMultiWindows()
                && MultiWindowUtils.getInstanceCount() > 1
                && !QoraiMultiWindowUtils.shouldEnableMultiWindows()) {
            QoraiMultiWindowUtils.setCheckUpgradeEnableMultiWindows(true);
            QoraiMultiWindowUtils.updateEnableMultiWindows(true);
        } else if (!QoraiMultiWindowUtils.isCheckUpgradeEnableMultiWindows()) {
            QoraiMultiWindowUtils.setCheckUpgradeEnableMultiWindows(true);
        }

        if (ENABLE_IN_APP_UPDATE
                && System.currentTimeMillis()
                        > ChromeSharedPreferences.getInstance()
                                .readLong(QoraiPreferenceKeys.QORAI_IN_APP_UPDATE_TIMING, 0)) {
            checkAppUpdate();
        }

        if (!isFirstInstall
                && !QoraiPrefServiceBridge.getInstance().getPlayYTVideoInBrowserEnabled()
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.OPEN_YT_IN_QORAI_DIALOG, true)) {
            openYtInQoraiDialog();
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiPreferenceKeys.OPEN_YT_IN_QORAI_DIALOG, false);
        }

        // Quick search engines views changes
        new KeyboardVisibilityHelper(QoraiActivity.this, QoraiActivity.this);
        AppCompatEditText urlBar = findViewById(R.id.url_bar);
        if (urlBar != null) {
            urlBar.addTextChangedListener(
                    new TextWatcher() {
                        @Override
                        public void beforeTextChanged(
                                CharSequence s, int start, int count, int after) {}

                        @Override
                        public void onTextChanged(
                                CharSequence query, int start, int before, int count) {
                            if (query.toString().isEmpty()) {
                                removeQuickActionSearchEnginesView();
                            } else {
                                if (getQoraiToolbarLayout().isUrlBarFocused()
                                        && KeyboardUtils.isAndroidSoftKeyboardShowing(urlBar)) {
                                    View rootView = findViewById(android.R.id.content);
                                    Rect r = new Rect();
                                    rootView.getWindowVisibleDisplayFrame(r);
                                    int screenHeight = rootView.getRootView().getHeight();
                                    int visibleHeight = r.bottom;
                                    int heightDifference = screenHeight - visibleHeight;
                                    showQuickActionSearchEnginesView(heightDifference);
                                } else {
                                    removeQuickActionSearchEnginesView();
                                }
                            }
                        }

                        @Override
                        public void afterTextChanged(Editable s) {}
                    });
            if (ChromeSharedPreferences.getInstance()
                    .readBoolean(OnboardingPrefManager.SHOULD_SHOW_SEARCH_WIDGET_PROMO, false)) {
                mSearchWidgetPromoPanel = new SearchWidgetPromoPanel(QoraiActivity.this);
                mSearchWidgetPromoPanel.showIfNeeded(urlBar);
                ChromeSharedPreferences.getInstance()
                        .writeBoolean(OnboardingPrefManager.SHOULD_SHOW_SEARCH_WIDGET_PROMO, false);
            }
        }

        ContextUtils.getAppSharedPreferences().registerOnSharedPreferenceChangeListener(this);
    }

    private void applyChangesForYahooJp() {
        boolean isDefaultSearchEngineChanged =
                ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.DEFAULT_SEARCH_ENGINE_CHANGED, false);
        TemplateUrlService templateUrlService =
                TemplateUrlServiceFactory.getForProfile(getCurrentProfile());
        Runnable onTemplateUrlServiceReady =
                () -> {
                    if (isActivityFinishingOrDestroyed()) return;
                    TemplateUrl yahooJpTemplateUrl =
                            QoraiSearchEngineUtils.getTemplateUrlByShortName(
                                    getCurrentProfile(), OnboardingPrefManager.YAHOO_JP);
                    if (yahooJpTemplateUrl != null
                            && !isDefaultSearchEngineChanged
                            && templateUrlService.isDefaultSearchEngineGoogle()) {
                        QoraiSearchEngineUtils.setDSEPrefs(yahooJpTemplateUrl, getCurrentProfile());
                        ChromeSharedPreferences.getInstance()
                                .writeBoolean(
                                        QoraiPreferenceKeys.QORAI_DEFAULT_SEARCH_ENGINE_MIGRATED_JP,
                                        true);
                    }
                };
        templateUrlService.runWhenLoaded(onTemplateUrlServiceReady);
    }

    private void setQoraiAsDefaultPrivateMode() {
        Runnable onTemplateUrlServiceReady =
                () -> {
                    if (isActivityFinishingOrDestroyed()) return;
                    TemplateUrl qoraiTemplateUrl =
                            QoraiSearchEngineUtils.getTemplateUrlByShortName(
                                    getCurrentProfile(), OnboardingPrefManager.QORAI);
                    if (qoraiTemplateUrl != null) {
                        QoraiSearchEngineUtils.setDSEPrefs(
                                qoraiTemplateUrl,
                                getCurrentProfile()
                                        .getPrimaryOtrProfile(/* createIfNeeded= */ true));
                    }
                };
        TemplateUrlServiceFactory.getForProfile(getCurrentProfile())
                .runWhenLoaded(onTemplateUrlServiceReady);
    }

    private void enableSearchSuggestions() {
        TemplateUrl defaultSearchEngineTemplateUrl =
                QoraiSearchEngineUtils.getTemplateUrlByShortName(
                        getCurrentProfile(),
                        QoraiSearchEngineUtils.getDSEShortName(getCurrentProfile(), false));
        if (defaultSearchEngineTemplateUrl != null
                && QORAI_SEARCH_ENGINE_KEYWORD.equals(
                        defaultSearchEngineTemplateUrl.getKeyword())) {
            UserPrefs.get(getCurrentProfile()).setBoolean(Pref.SEARCH_SUGGEST_ENABLED, true);
        }
    }

    private void setInAppUpdateTiming() {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(new Date());
        calendar.add(Calendar.MONTH, MONTH_1);
        ChromeSharedPreferences.getInstance()
                .writeLong(
                        QoraiPreferenceKeys.QORAI_IN_APP_UPDATE_TIMING, calendar.getTimeInMillis());
    }

    private void completeUpdateSnackbar() {
        Snackbar snackbar =
                Snackbar.make(
                                getResources().getString(R.string.in_app_update_text),
                                new SnackbarController() {
                                    @Override
                                    public void onDismissNoAction(Object actionData) {}

                                    @Override
                                    public void onAction(Object actionData) {
                                        if (mAppUpdateManager != null) {
                                            mAppUpdateManager.completeUpdate();
                                            mAppUpdateManager.unregisterListener(
                                                    mInstallStateUpdatedListener);
                                        }
                                    }
                                },
                                Snackbar.TYPE_ACTION,
                                Snackbar.UMA_UNKNOWN)
                        .setAction(getResources().getString(R.string.update), null)
                        .setDefaultLines(false)
                        .setDuration(10000);
        Tab currentTab = getActivityTabProvider().get();
        if (currentTab != null) {
            SnackbarManager snackbarManager =
                    SnackbarManagerProvider.from(currentTab.getWindowAndroid());
            snackbarManager.showSnackbar(snackbar);
        }
    }

    private final InstallStateUpdatedListener mInstallStateUpdatedListener =
            installState -> {
                if (installState.installStatus() == InstallStatus.DOWNLOADED) {
                    completeUpdateSnackbar();
                }
            };

    private void checkAppUpdate() {
        mAppUpdateManager = AppUpdateManagerFactory.create(QoraiActivity.this);
        mAppUpdateManager.registerListener(mInstallStateUpdatedListener);

        Task<AppUpdateInfo> appUpdateInfoTask = mAppUpdateManager.getAppUpdateInfo();

        appUpdateInfoTask.addOnSuccessListener(
                appUpdateInfo -> {
                    if (appUpdateInfo.updateAvailability() == UpdateAvailability.UPDATE_AVAILABLE) {
                        if (appUpdateInfo.updatePriority() >= 4 /* high priority */
                                && appUpdateInfo.isUpdateTypeAllowed(AppUpdateType.IMMEDIATE)) {
                            startAppUpdateFlow(appUpdateInfo, AppUpdateType.IMMEDIATE);
                        } else {
                            startAppUpdateFlow(appUpdateInfo, AppUpdateType.FLEXIBLE);
                        }
                    }
                });
    }

    private void startAppUpdateFlow(AppUpdateInfo appUpdateInfo, int appUpdateType) {
        try {
            mAppUpdateManager.startUpdateFlowForResult(
                    appUpdateInfo, appUpdateType, QoraiActivity.this, 1);
            setInAppUpdateTiming();
        } catch (IntentSender.SendIntentException e) {
            throw new RuntimeException(e);
        }
    }

    private void handleDeepLinkVpn() {
        mIsDeepLink = true;
        QoraiVpnUtils.openQoraiVpnPlansActivity(this);
    }

    private void checkForVpnCallout() {
        String countryCode = Locale.getDefault().getCountry();

        if (!countryCode.equals(QoraiConstants.INDIA_COUNTRY_CODE)
                && QoraiVpnUtils.isVpnFeatureSupported(QoraiActivity.this)) {
            if (!TextUtils.isEmpty(QoraiVpnPrefUtils.getPurchaseToken())
                    && !TextUtils.isEmpty(QoraiVpnPrefUtils.getProductId())) {
                mIsVerification = true;
                QoraiVpnNativeWorker.getInstance().verifyPurchaseToken(
                        QoraiVpnPrefUtils.getPurchaseToken(), QoraiVpnPrefUtils.getProductId(),
                        QoraiVpnUtils.SUBSCRIPTION_PARAM_TEXT, getPackageName());
            }
        }
    }

    private void initQoraiNews() {
        ThreadUtils.assertOnUiThread();
        if (QoraiPrefServiceBridge.getInstance().getShowNews()
                && QoraiPrefServiceBridge.getInstance().getNewsOptIn()) {
            QoraiNewsUtils.getQoraiNewsSettingsDataPerProfile(mTabModelProfileSupplier.get());
        }
    }

    public void setDormantUsersPrefs() {
        OnboardingPrefManager.getInstance().setDormantUsersPrefs();
        RetentionNotificationUtil.scheduleDormantUsersNotifications(this);
    }

    private void openPlaylist(boolean shouldHandlePlaylistActivity) {
        if (!shouldHandlePlaylistActivity) mIsDeepLink = true;

        if (ChromeSharedPreferences.getInstance()
                .readBoolean(PlaylistPreferenceUtils.SHOULD_SHOW_PLAYLIST_ONBOARDING, true)) {
            PlaylistUtils.openPlaylistMenuOnboardingActivity(QoraiActivity.this);
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(PlaylistPreferenceUtils.SHOULD_SHOW_PLAYLIST_ONBOARDING, false);
        } else if (shouldHandlePlaylistActivity) {
            openPlaylistActivity(QoraiActivity.this, ConstantUtils.ALL_PLAYLIST);
        }
    }

    public void openPlaylistActivity(Context context, String playlistId) {
        Intent playlistActivityIntent = new Intent(context, PlaylistHostActivity.class);
        playlistActivityIntent.putExtra(ConstantUtils.PLAYLIST_ID, playlistId);
        playlistActivityIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        playlistActivityIntent.setAction(Intent.ACTION_VIEW);
        context.startActivity(playlistActivityIntent);
    }

    private void showLinkVpnSubscriptionDialog() {
        LinkVpnSubscriptionDialogFragment linkVpnSubscriptionDialogFragment =
                new LinkVpnSubscriptionDialogFragment();
        linkVpnSubscriptionDialogFragment.setCancelable(false);
        linkVpnSubscriptionDialogFragment.show(
                getSupportFragmentManager(), "LinkVpnSubscriptionDialogFragment");
    }

    private void showAdFreeCalloutDialog() {
        ChromeSharedPreferences.getInstance()
                .writeBoolean(QoraiPreferenceKeys.QORAI_AD_FREE_CALLOUT_DIALOG, false);

        QoraiAdFreeCalloutDialogFragment qoraiAdFreeCalloutDialogFragment =
                new QoraiAdFreeCalloutDialogFragment();
        qoraiAdFreeCalloutDialogFragment.show(
                getSupportFragmentManager(), "QoraiAdFreeCalloutDialogFragment");
    }

    public void setNewTabPageManager(NewTabPageManager manager) {
        mNewTabPageManager = manager;
    }

    public void focusSearchBox() {
        if (mNewTabPageManager != null) {
            mNewTabPageManager.focusSearchBox(false, null);
        }
    }

    private void checkFingerPrintingOnUpgrade(boolean isFirstInstall) {
        if (!isFirstInstall
                && ChromeSharedPreferences.getInstance()
                                .readInt(QoraiPreferenceKeys.QORAI_APP_OPEN_COUNT)
                        == 0) {
            boolean value =
                    ChromeSharedPreferences.getInstance()
                            .readBoolean(QoraiPrivacySettings.PREF_FINGERPRINTING_PROTECTION, true);
            if (value) {
                QoraiShieldsContentSettings.setShieldsValue(
                        ProfileManager.getLastUsedRegularProfile(),
                        "",
                        QoraiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING,
                        QoraiShieldsContentSettings.DEFAULT,
                        false);
            } else {
                QoraiShieldsContentSettings.setShieldsValue(
                        ProfileManager.getLastUsedRegularProfile(),
                        "",
                        QoraiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING,
                        QoraiShieldsContentSettings.ALLOW_RESOURCE,
                        false);
            }
        }
    }

    public void openQuickSearchEnginesSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, QuickSearchEnginesFragment.class);
    }

    public void openQoraiPlaylistSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, QoraiPlaylistPreferences.class);
    }

    public void openQoraiNewsSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, QoraiNewsPreferencesV2.class);
    }

    public void openQoraiContentFilteringSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, ContentFilteringFragment.class);
    }

    public int getQoraiThemeBackgroundColor() {
        return ContextUtils.getApplicationContext()
                .getColor(R.color.toolbar_background_color_for_ntp);
    }

    public void openQoraiCreateCustomFiltersSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, CreateCustomFiltersFragment.class);
    }

    public void openQoraiWalletSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, QoraiWalletPreferences.class);
    }

    public void openQoraiConnectedSitesSettings() {
        SettingsNavigation settingsLauncher = SettingsNavigationFactory.createSettingsNavigation();
        settingsLauncher.startSettings(this, QoraiWalletEthereumConnectedSites.class);
    }

    public void openQoraiWallet(boolean fromDapp, boolean setupAction, boolean restoreAction) {
        Intent qoraiWalletIntent = new Intent(this, QoraiWalletActivity.class);
        qoraiWalletIntent.putExtra(QoraiWalletActivity.IS_FROM_DAPPS, fromDapp);
        qoraiWalletIntent.putExtra(QoraiWalletActivity.RESTART_WALLET_ACTIVITY_SETUP, setupAction);
        qoraiWalletIntent.putExtra(
                QoraiWalletActivity.RESTART_WALLET_ACTIVITY_RESTORE, restoreAction);
        qoraiWalletIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        qoraiWalletIntent.setAction(Intent.ACTION_VIEW);
        startActivity(qoraiWalletIntent);
    }

    public void openQoraiWalletBackup() {
        Intent qoraiWalletIntent = new Intent(this, QoraiWalletActivity.class);
        qoraiWalletIntent.putExtra(QoraiWalletActivity.SHOW_WALLET_ACTIVITY_BACKUP, true);
        qoraiWalletIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        qoraiWalletIntent.setAction(Intent.ACTION_VIEW);
        startActivity(qoraiWalletIntent);
    }

    public void viewOnBlockExplorer(
            String address, @CoinType.EnumType int coinType, NetworkInfo networkInfo) {
        Utils.openAddress("/address/" + address, this, coinType, networkInfo);
    }

    public void openQoraiWalletDAppsActivity(
            final QoraiWalletDAppsActivity.ActivityType activityType) {
        final Intent qoraiWalletIntent = QoraiWalletDAppsActivity.getIntent(this, activityType);
        startActivity(qoraiWalletIntent);
    }

    public MiscAndroidMetrics getMiscAndroidMetrics() {
        return mMiscAndroidMetrics;
    }

    private void checkForYandexSE() {
        String countryCode = Locale.getDefault().getCountry();
        if (sYandexRegions.contains(countryCode)) {
            Profile lastUsedRegularProfile = ProfileManager.getLastUsedRegularProfile();
            TemplateUrl yandexTemplateUrl =
                    QoraiSearchEngineUtils.getTemplateUrlByShortName(
                            lastUsedRegularProfile, OnboardingPrefManager.YANDEX);
            if (yandexTemplateUrl != null) {
                QoraiSearchEngineUtils.setDSEPrefs(yandexTemplateUrl, lastUsedRegularProfile);
            }
        }
    }

    private void checkForNotificationData() {
        Intent notifIntent = getIntent();
        if (notifIntent != null && notifIntent.getStringExtra(RetentionNotificationUtil.NOTIFICATION_TYPE) != null) {
            String notificationType = notifIntent.getStringExtra(RetentionNotificationUtil.NOTIFICATION_TYPE);
            switch (notificationType) {
                case RetentionNotificationUtil.HOUR_3:
                case RetentionNotificationUtil.HOUR_24:
                case RetentionNotificationUtil.EVERY_SUNDAY:
                    checkForQoraiStats();
                    break;
                case RetentionNotificationUtil.DAY_6:
                    if (getActivityTab() != null
                            && getActivityTab().getUrl().getSpec() != null
                            && !UrlUtilities.isNtpUrl(getActivityTab().getUrl().getSpec())) {
                        getTabCreator(false).launchUrl(
                                UrlConstants.NTP_URL, TabLaunchType.FROM_CHROME_UI);
                    }
                    break;
                case RetentionNotificationUtil.DAY_10:
                case RetentionNotificationUtil.DAY_30:
                case RetentionNotificationUtil.DAY_35:
                    openRewardsPanel();
                    break;
                case RetentionNotificationUtil.DORMANT_USERS_DAY_14:
                case RetentionNotificationUtil.DORMANT_USERS_DAY_25:
                case RetentionNotificationUtil.DORMANT_USERS_DAY_40:
                    showDormantUsersEngagementDialog(notificationType);
                    break;
            }
        }
    }

    public void checkForQoraiStats() {
        if (OnboardingPrefManager.getInstance().isQoraiStatsEnabled()) {
            QoraiStatsUtil.showQoraiStats();
        } else {
            if (getActivityTab() != null
                    && getActivityTab().getUrl().getSpec() != null
                    && !UrlUtilities.isNtpUrl(getActivityTab().getUrl().getSpec())) {
                OnboardingPrefManager.getInstance().setFromNotification(true);
                if (getTabCreator(false) != null) {
                    getTabCreator(false).launchUrl(
                            UrlConstants.NTP_URL, TabLaunchType.FROM_CHROME_UI);
                }
            } else {
                showOnboardingV2(false);
            }
        }
    }

    public void showOnboardingV2(boolean fromStats) {
        try {
            OnboardingPrefManager.getInstance().setNewOnboardingShown(true);
            FragmentManager fm = getSupportFragmentManager();
            HighlightDialogFragment fragment = (HighlightDialogFragment) fm.findFragmentByTag(
                    HighlightDialogFragment.TAG_FRAGMENT);
            FragmentTransaction transaction = fm.beginTransaction();

            if (fragment != null) {
                transaction.remove(fragment);
            }

            fragment = new HighlightDialogFragment();
            Bundle fragmentBundle = new Bundle();
            fragmentBundle.putBoolean(OnboardingPrefManager.FROM_STATS, fromStats);
            fragment.setArguments(fragmentBundle);
            transaction.add(fragment, HighlightDialogFragment.TAG_FRAGMENT);
            transaction.commitAllowingStateLoss();
        } catch (IllegalStateException e) {
            Log.e("HighlightDialogFragment", e.getMessage());
        }
    }

    public void hideRewardsOnboardingIcon() {
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.hideRewardsOnboardingIcon();
    }

    private void createNotificationChannel() {
        // Create the NotificationChannel, but only on API 26+ because
        // the NotificationChannel class is new and not in the support library
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel(
                    CHANNEL_ID, getString(R.string.qorai_browser), importance);
            channel.setDescription(
                    getString(R.string.qorai_browser_notification_channel_description));
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }

    private boolean isNoRestoreState() {
        return ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiPreferenceKeys.QORAI_CLOSE_TABS_ON_EXIT, false);
    }

    private boolean isClearBrowsingDataOnExit() {
        return ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiPreferenceKeys.QORAI_CLEAR_ON_EXIT, false);
    }

    public void dismissShieldsTooltip() {
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.dismissShieldsTooltip();
    }

    public void openRewardsPanel() {
        QoraiToolbarLayoutImpl layout = getQoraiToolbarLayout();
        layout.openRewardsPanel();
    }

    public Profile getCurrentProfile() {
        Tab tab = getActivityTab();
        if (tab == null) {
            return ProfileManager.getLastUsedRegularProfile();
        }

        return Profile.fromWebContents(tab.getWebContents());
    }

    /** Close all tabs (including active tab) whose URL origin matches with a given origin. */
    public void closeAllTabsByOrigin(@NonNull final String origin) {
        final TabModel tabModel = getCurrentTabModel();

        Set<Integer> tabIndexes = getTabIndexesByUrlOrigin(tabModel, origin);
        for (Integer index : tabIndexes) {
            Tab tab = tabModel.getTabAt(index);
            if (tab != null) {
                tab.setClosing(true);
                tabModel.getTabRemover().closeTabs(TabClosureParams.closeTab(tab).build(), false);
            }
        }
    }

    /**
     * Selects an existing tab if it matches a given origin, marks it as active and returns it.
     *
     * @return Active tab if it exists, {@code null} otherwise.
     */
    public Tab selectExistingUrlOriginTab(@NonNull final String origin) {
        TabModel tabModel = getCurrentTabModel();
        Set<Integer> tabIndexes = getTabIndexesByUrlOrigin(tabModel, origin);

        // Find if tab exists, including tab already active.
        if (!tabIndexes.isEmpty()) {
            int index = tabIndexes.iterator().next();
            Tab tab = tabModel.getTabAt(tabIndexes.iterator().next());
            // Set active tab
            tabModel.setIndex(index, TabSelectionType.FROM_USER);
            return tab;
        } else {
            return null;
        }
    }

    /**
     * Find the {@link Tab} indexes whose URL starts with the specified base URL.
     *
     * @param model The {@link TabModel} to act on.
     * @param origin The URL origin to search for.
     * @return A set of indexes pointing to the matching {@link Tab}s or empty set if no matches are
     *     found.
     */
    @NonNull
    private static Set<Integer> getTabIndexesByUrlOrigin(
            @NonNull final TabList model, @NonNull final String origin) {
        final Set<Integer> result = new HashSet<>();
        int count = model.getCount();

        for (int i = 0; i < count; i++) {
            if (model.getTabAt(i).getUrl().getOrigin().getSpec().contentEquals(origin)) {
                result.add(i);
            }
        }
        return result;
    }

    public Tab selectExistingTab(String url) {
        Tab tab = getActivityTab();
        if (tab != null && tab.getUrl().getSpec().equals(url)) {
            return tab;
        }

        TabModel tabModel = getCurrentTabModel();
        int tabIndex = TabModelUtils.getTabIndexByUrl(tabModel, url);

        // Find if tab exists
        if (tabIndex != TabModel.INVALID_TAB_INDEX) {
            tab = tabModel.getTabAt(tabIndex);
            // Set active tab
            tabModel.setIndex(tabIndex, TabSelectionType.FROM_USER);
            return tab;
        } else {
            return null;
        }
    }

    public Tab openNewOrSelectExistingTab(String url, boolean refresh) {
        Tab tab = selectExistingTab(url);
        if (tab != null) {
            if (refresh) {
                tab.reload();
            }
            return tab;
        } else { // Open a new tab
            return getTabCreator(false).launchUrl(url, TabLaunchType.FROM_CHROME_UI);
        }
    }

    public void openNewOrRefreshExistingTab(
            @NonNull final String origin, @NonNull final String url) {
        Tab tab = selectExistingUrlOriginTab(origin);
        if (tab != null) {
            tab.reload();
        } else {
            // Open a new tab.
            getTabCreator(false).launchUrl(url, TabLaunchType.FROM_CHROME_UI);
        }
    }

    public Tab openNewOrSelectExistingTab(String url) {
        return openNewOrSelectExistingTab(url, false);
    }

    private void clearWalletModelServices() {
        if (mWalletModel == null) {
            return;
        }

        mWalletModel.resetServices(
                getApplicationContext(), null, null, null, null, null, null, null, null, null);
    }

    public void setupWalletModel() {
        PostTask.postTask(
                TaskTraits.UI_DEFAULT,
                () -> {
                    if (mWalletModel == null) {
                        mWalletModel =
                                new WalletModel(
                                        getApplicationContext(),
                                        mKeyringService,
                                        mBlockchainRegistry,
                                        mJsonRpcService,
                                        mTxService,
                                        mEthTxManagerProxy,
                                        mSolanaTxManagerProxy,
                                        mAssetRatioService,
                                        mQoraiWalletService,
                                        mSwapService);
                    } else {
                        mWalletModel.resetServices(
                                getApplicationContext(),
                                mKeyringService,
                                mBlockchainRegistry,
                                mJsonRpcService,
                                mTxService,
                                mEthTxManagerProxy,
                                mSolanaTxManagerProxy,
                                mAssetRatioService,
                                mQoraiWalletService,
                                mSwapService);
                    }
                    setupObservers();
                });
    }

    @MainThread
    private void setupObservers() {
        ThreadUtils.assertOnUiThread();
        clearObservers();
        mWalletModel.getCryptoModel().getPendingTxHelper().mSelectedPendingRequest.observe(
                this, transactionInfo -> {
                    if (transactionInfo == null) {
                        return;
                    }
                    // don't show dapps panel if the wallet is locked and requests are being
                    // processed by the approve dialog already
                    mKeyringService.isLocked(locked -> {
                        if (locked) {
                            return;
                        }

                        if (!mIsProcessingPendingDappsTxRequest) {
                            mIsProcessingPendingDappsTxRequest = true;
                            openQoraiWalletDAppsActivity(
                                    QoraiWalletDAppsActivity.ActivityType.CONFIRM_TRANSACTION);
                        }

                        // update badge if there's a pending tx
                        updateWalletBadgeVisibility();
                    });
                });

        mWalletModel.getDappsModel().mWalletIconNotificationVisible.observe(
                this, this::setWalletBadgeVisibility);

        mWalletModel.getDappsModel().mPendingWalletAccountCreationRequest.observe(this, request -> {
            if (request == null) return;
            mWalletModel.getKeyringModel().isWalletLocked(isLocked -> {
                if (!QoraiWalletPreferences.getPrefWeb3NotificationsEnabled()) return;
                if (isLocked) {
                    Tab tab = getActivityTab();
                    if (tab != null) {
                        walletInteractionDetected(tab.getWebContents());
                    }
                    showWalletPanel(false);
                    return;
                }
                for (CryptoAccountTypeInfo info :
                        mWalletModel.getCryptoModel().getSupportedCryptoAccountTypes()) {
                    if (info.getCoinType() == request.getCoinType()) {
                        Intent intent = AddAccountActivity.createIntentToAddAccount(
                                this, info.getCoinType());
                        startActivity(intent);
                        mWalletModel.getDappsModel().removeProcessedAccountCreationRequest(request);
                        break;
                    }
                }
            });
        });

        mWalletModel.getCryptoModel().getNetworkModel().mNeedToCreateAccountForNetwork.observe(
                this, networkInfo -> {
                    if (networkInfo == null) return;

                    MaterialAlertDialogBuilder builder =
                            new MaterialAlertDialogBuilder(
                                    this, R.style.QoraiWalletAlertDialogTheme)
                                    .setMessage(getString(
                                            R.string.qorai_wallet_create_account_description,
                                            networkInfo.symbolName))
                                    .setPositiveButton(R.string.qorai_action_yes,
                                            (dialog, which) -> {
                                                mWalletModel.createAccountAndSetDefaultNetwork(
                                                        networkInfo);
                                            })
                                    .setNegativeButton(
                                            R.string.qorai_action_no, (dialog, which) -> {
                                                mWalletModel.getCryptoModel()
                                                        .getNetworkModel()
                                                        .clearCreateAccountState();
                                                dialog.dismiss();
                                            });
                    builder.show();
                });
    }

    @MainThread
    private void clearObservers() {
        ThreadUtils.assertOnUiThread();
        mWalletModel.getCryptoModel().getPendingTxHelper().mSelectedPendingRequest.removeObservers(
                this);
        mWalletModel.getDappsModel().mWalletIconNotificationVisible.removeObservers(this);
        mWalletModel.getCryptoModel()
                .getNetworkModel()
                .mNeedToCreateAccountForNetwork.removeObservers(this);
    }

    private void showQoraiRateDialog() {
        QoraiRateDialogFragment rateDialogFragment = QoraiRateDialogFragment.newInstance(false);
        rateDialogFragment.show(getSupportFragmentManager(), QoraiRateDialogFragment.TAG_FRAGMENT);
    }

    private void openYtInQoraiDialog() {
        OpenYtInQoraiDialogFragment mOpenYtInQoraiDialogFragment =
                new OpenYtInQoraiDialogFragment();
        mOpenYtInQoraiDialogFragment.show(
                getSupportFragmentManager(), "OpenYtInQoraiDialogFragment");
    }

    public void showDormantUsersEngagementDialog(String notificationType) {
        if (!QoraiSetDefaultBrowserUtils.isQoraiSetAsDefaultBrowser(QoraiActivity.this)) {
            DormantUsersEngagementDialogFragment dormantUsersEngagementDialogFragment =
                    new DormantUsersEngagementDialogFragment();
            dormantUsersEngagementDialogFragment.setNotificationType(notificationType);
            dormantUsersEngagementDialogFragment.show(
                    getSupportFragmentManager(), "DormantUsersEngagementDialogFragment");
            setDormantUsersPrefs();
        }
    }

    private static Activity getActivityOfType(Class<?> classOfActivity) {
        for (Activity ref : ApplicationStatus.getRunningActivities()) {
            if (!classOfActivity.isInstance(ref)) continue;

            return ref;
        }

        return null;
    }

    public void openQoraiQora() {
        QoraiQoraUtils.verifySubscription(null);
        Tab currentTab = getActivityTabProvider().get();
        if (currentTab != null) {
            QoraiQoraUtils.openQoraUrlForTab(currentTab.getWebContents());
        }
    }

    public void showRewardsPage() {
        getQoraiToolbarLayout().showRewardsPage();
    }

    /**
     * Sets a flag to resume the currently active media session when entering picture-in-picture
     * mode, so the user won't have to manually resume the video after the transition.
     */
    public void resumeMediaSession(final boolean resume) {
        mResumeMediaSession = resume;
    }

    public static ChromeTabbedActivity getChromeTabbedActivity() {
        return (ChromeTabbedActivity) getActivityOfType(ChromeTabbedActivity.class);
    }

    public static CustomTabActivity getCustomTabActivity() {
        return (CustomTabActivity) getActivityOfType(CustomTabActivity.class);
    }

    @NonNull
    public static QoraiActivity getQoraiActivity() throws QoraiActivityNotFoundException {
        QoraiActivity activity = (QoraiActivity) getActivityOfType(QoraiActivity.class);
        if (activity != null) {
            return activity;
        }

        throw new QoraiActivityNotFoundException("QoraiActivity Not Found");
    }

    @NonNull
    public static QoraiActivity getQoraiActivityFromTaskId(int taskId)
            throws QoraiActivityNotFoundException {

        for (Activity ref : ApplicationStatus.getRunningActivities()) {
            if (!QoraiActivity.class.isInstance(ref) || ref.getTaskId() != taskId) continue;

            return (QoraiActivity) ref;
        }

        throw new QoraiActivityNotFoundException("QoraiActivity Not Found");
    }

    @Override
    public void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        if (intent != null) {
            String openUrl = intent.getStringExtra(QoraiActivity.OPEN_URL);
            if (!TextUtils.isEmpty(openUrl)) {
                try {
                    openNewOrSelectExistingTab(openUrl);
                } catch (NullPointerException e) {
                    Log.e("QoraiActivity", "opening new tab " + e.getMessage());
                }
            }
        }
        checkForNotificationData();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == RESULT_OK
                && (requestCode == QoraiConstants.VERIFY_WALLET_ACTIVITY_REQUEST_CODE
                        || requestCode == QoraiConstants.USER_WALLET_ACTIVITY_REQUEST_CODE
                        || requestCode == QoraiConstants.SITE_BANNER_REQUEST_CODE)) {
            if (data != null) {
                String open_url = data.getStringExtra(QoraiActivity.OPEN_URL);
                if (!TextUtils.isEmpty(open_url)) {
                    openNewOrSelectExistingTab(open_url);
                }
            }
        } else if (resultCode == RESULT_OK
                && requestCode == QoraiConstants.DEFAULT_BROWSER_ROLE_REQUEST_CODE) {
            // We don't need to anything with the result here.
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onRequestPermissionsResult(
            int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        FragmentManager fm = getSupportFragmentManager();
        QoraiStatsBottomSheetDialogFragment fragment =
                (QoraiStatsBottomSheetDialogFragment) fm.findFragmentByTag(
                        QoraiStatsUtil.STATS_FRAGMENT_TAG);
        if (fragment != null) {
            fragment.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }

        if (requestCode == QoraiStatsUtil.SHARE_STATS_WRITE_EXTERNAL_STORAGE_PERM
                && grantResults.length != 0
                && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            QoraiStatsUtil.shareStats(R.layout.qorai_stats_share_layout);
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    @Override
    public void performPreInflationStartup() {
        QoraiDbUtil dbUtil = QoraiDbUtil.getInstance();
        if (dbUtil.dbOperationRequested()) {
            AlertDialog dialog =
                    new AlertDialog.Builder(this)
                            .setMessage(dbUtil.performDbExportOnStart()
                                            ? getString(
                                                    R.string.qorai_db_processing_export_alert_info)
                                            : getString(
                                                    R.string.qorai_db_processing_import_alert_info))
                            .setCancelable(false)
                            .create();
            dialog.setCanceledOnTouchOutside(false);
            if (dbUtil.performDbExportOnStart()) {
                dbUtil.setPerformDbExportOnStart(false);
                dbUtil.exportRewardsDb(dialog);
            } else if (dbUtil.performDbImportOnStart() && !dbUtil.dbImportFile().isEmpty()) {
                dbUtil.setPerformDbImportOnStart(false);
                dbUtil.importRewardsDb(dialog, dbUtil.dbImportFile());
            }
            dbUtil.cleanUpDbOperationRequest();
        }
        super.performPreInflationStartup();
    }

    @Override
    protected @LaunchIntentDispatcher.Action int maybeDispatchLaunchIntent(
            Intent intent, Bundle savedInstanceState) {
        boolean notificationUpdate = IntentUtils.safeGetBooleanExtra(
                intent, QoraiPreferenceKeys.QORAI_UPDATE_EXTRA_PARAM, false);
        if (notificationUpdate) {
            setUpdatePreferences();
        }

        return super.maybeDispatchLaunchIntent(intent, savedInstanceState);
    }

    private void setUpdatePreferences() {
        Calendar currentTime = Calendar.getInstance();
        long milliSeconds = currentTime.getTimeInMillis();

        SharedPreferences sharedPref = getApplicationContext().getSharedPreferences(
                QoraiPreferenceKeys.QORAI_NOTIFICATION_PREF_NAME, 0);
        SharedPreferences.Editor editor = sharedPref.edit();

        editor.putLong(QoraiPreferenceKeys.QORAI_MILLISECONDS_NAME, milliSeconds);
        editor.apply();
    }

    public ObservableSupplier<BrowserControlsManager> getBrowserControlsManagerSupplier() {
        return mBrowserControlsManagerSupplier;
    }

    @NativeMethods
    interface Natives {
        void restartStatsUpdater();
        String getSafeBrowsingApiKey();
    }

    private void initQoraiWalletService() {
        if (mQoraiWalletService != null) {
            return;
        }

        mQoraiWalletService = QoraiWalletServiceFactory.getInstance().getQoraiWalletService(this);
    }

    private void initKeyringService() {
        if (mKeyringService != null) {
            return;
        }

        mKeyringService = QoraiWalletServiceFactory.getInstance().getKeyringService(this);
    }

    private void initJsonRpcService() {
        if (mJsonRpcService != null) {
            return;
        }

        mJsonRpcService = QoraiWalletServiceFactory.getInstance().getJsonRpcService(this);
    }

    private void initTxService() {
        if (mTxService != null) {
            return;
        }

        mTxService = QoraiWalletServiceFactory.getInstance().getTxService(this);
    }

    private void initEthTxManagerProxy() {
        if (mEthTxManagerProxy != null) {
            return;
        }

        mEthTxManagerProxy = QoraiWalletServiceFactory.getInstance().getEthTxManagerProxy(this);
    }

    private void initSolanaTxManagerProxy() {
        if (mSolanaTxManagerProxy != null) {
            return;
        }

        mSolanaTxManagerProxy =
                QoraiWalletServiceFactory.getInstance().getSolanaTxManagerProxy(this);
    }

    private void initBlockchainRegistry() {
        if (mBlockchainRegistry != null) {
            return;
        }

        mBlockchainRegistry = BlockchainRegistryFactory.getInstance().getBlockchainRegistry(this);
    }

    private void initAssetRatioService() {
        if (mAssetRatioService != null) {
            return;
        }

        mAssetRatioService = AssetRatioServiceFactory.getInstance().getAssetRatioService(this);
    }

    @Override
    public void initMiscAndroidMetricsFromAWorkerThread() {
        runOnUiThread(
                () -> {
                    initMiscAndroidMetrics();
                });
    }

    private void initMiscAndroidMetrics() {
        ThreadUtils.assertOnUiThread();
        if (mMiscAndroidMetrics != null) {
            return;
        }
        if (mMiscAndroidMetricsConnectionErrorHandler == null) {
            mMiscAndroidMetricsConnectionErrorHandler =
                    new MiscAndroidMetricsConnectionErrorHandler(this);
        }

        MiscAndroidMetricsFactory.getInstance()
                .getMetricsService(mMiscAndroidMetricsConnectionErrorHandler)
                .then(
                        miscAndroidMetrics -> {
                            mMiscAndroidMetrics = miscAndroidMetrics;
                            mMiscAndroidMetrics.recordPrivacyHubEnabledStatus(
                                    OnboardingPrefManager.getInstance().isQoraiStatsEnabled());
                            mMiscAndroidMetrics.recordSetAsDefault(
                                    QoraiSetDefaultBrowserUtils.isAppSetAsDefaultBrowser(
                                            QoraiActivity.this));
                            if (mUsageMonitor == null) {
                                mUsageMonitor = UsageMonitor.getInstance(mMiscAndroidMetrics);
                            }
                            mUsageMonitor.start();
                        });
    }

    private void initSwapService() {
        if (mSwapService != null) {
            return;
        }
        mSwapService = SwapServiceFactory.getInstance().getSwapService(this);
    }

    private void initWalletNativeServices() {
        initBlockchainRegistry();
        initTxService();
        initEthTxManagerProxy();
        initSolanaTxManagerProxy();
        initAssetRatioService();
        initQoraiWalletService();
        initKeyringService();
        initJsonRpcService();
        initSwapService();
        setupWalletModel();
    }

    private void cleanUpWalletNativeServices() {
        clearWalletModelServices();
        if (mKeyringService != null) mKeyringService.close();
        if (mAssetRatioService != null) mAssetRatioService.close();
        if (mBlockchainRegistry != null) mBlockchainRegistry.close();
        if (mJsonRpcService != null) mJsonRpcService.close();
        if (mTxService != null) mTxService.close();
        if (mEthTxManagerProxy != null) mEthTxManagerProxy.close();
        if (mSolanaTxManagerProxy != null) mSolanaTxManagerProxy.close();
        if (mQoraiWalletService != null) mQoraiWalletService.close();
        mKeyringService = null;
        mBlockchainRegistry = null;
        mJsonRpcService = null;
        mTxService = null;
        mEthTxManagerProxy = null;
        mSolanaTxManagerProxy = null;
        mAssetRatioService = null;
        mQoraiWalletService = null;
    }

    @Override
    public void cleanUpMiscAndroidMetrics() {
        if (mUsageMonitor != null) {
            mUsageMonitor.stop();
        }
        if (mMiscAndroidMetrics != null) mMiscAndroidMetrics.close();
        mMiscAndroidMetrics = null;
    }

    @NonNull
    private QoraiToolbarLayoutImpl getQoraiToolbarLayout() {
        QoraiToolbarLayoutImpl layout = findViewById(R.id.toolbar);
        assert layout != null;
        return layout;
    }

    public void addOrEditBookmark(final Tab tabToBookmark) {
        RateUtils.getInstance().setPrefAddedBookmarkCount();
        ((TabBookmarker) mTabBookmarkerSupplier.get()).addOrEditBookmark(tabToBookmark);
    }

    public void showBookmarkManager(Profile profile, Tab currentTab) {
        if (mBookmarkManagerOpenerSupplier.get() != null) {
            mBookmarkManagerOpenerSupplier.get().showBookmarkManager(this, currentTab, profile);
        }
    }

    // We call that method with an interval
    // QoraiSafeBrowsingApiHandler.SAFE_BROWSING_INIT_INTERVAL_MS,
    // as upstream does, to keep the GmsCore process alive.
    private void executeInitSafeBrowsing(long delay) {
        // SafeBrowsingBridge.getSafeBrowsingState() has to be executed on a main thread
        PostTask.postDelayedTask(
                TaskTraits.UI_DEFAULT,
                () -> {
                    SafeBrowsingBridge safeBrowsingBridge =
                            new SafeBrowsingBridge(getCurrentProfile());
                    if (safeBrowsingBridge.getSafeBrowsingState()
                            != SafeBrowsingState.NO_SAFE_BROWSING) {
                        // initSafeBrowsing could be executed on a background thread
                        PostTask.postTask(
                                TaskTraits.USER_VISIBLE_MAY_BLOCK,
                                () -> {
                                    QoraiSafeBrowsingApiHandler.getInstance().initSafeBrowsing();
                                });
                    }
                    executeInitSafeBrowsing(
                            QoraiSafeBrowsingApiHandler.SAFE_BROWSING_INIT_INTERVAL_MS);
                },
                delay);
    }

    public void updateBottomSheetPosition(int orientation) {
        if (BottomToolbarConfiguration.isQoraiBottomControlsEnabled()) {
            // Ensure the bottom sheet's container is adjusted to the height of the bottom toolbar.
            ViewGroup sheetContainer = findViewById(R.id.sheet_container);
            assert sheetContainer != null;

            if (sheetContainer != null) {
                CoordinatorLayout.LayoutParams params =
                        (CoordinatorLayout.LayoutParams) sheetContainer.getLayoutParams();
                params.bottomMargin =
                        orientation == Configuration.ORIENTATION_LANDSCAPE
                                ? 0
                                : getResources()
                                        .getDimensionPixelSize(R.dimen.bottom_controls_height);
                sheetContainer.setLayoutParams(params);
            }
        }
    }

    /**
     * Calls to {@link ChromeTabbedActivity#maybeHandleUrlIntent} will be redirected here via
     * bytecode changes.
     */
    public boolean maybeHandleUrlIntent(Intent intent) {
        String appLinkAction = intent.getAction();
        Uri appLinkData = intent.getData();

        if (Intent.ACTION_VIEW.equals(appLinkAction) && appLinkData != null) {
            String lastPathSegment = appLinkData.getLastPathSegment();
            if (lastPathSegment != null
                    && (lastPathSegment.equalsIgnoreCase(QoraiConstants.DEEPLINK_ANDROID_PLAYLIST)
                            || lastPathSegment.equalsIgnoreCase(
                                    QoraiConstants.DEEPLINK_ANDROID_VPN))) {
                return false;
            }
        }
        // Call ChromeTabbedActivity's version.
        return (boolean)
                QoraiReflectionUtil.invokeMethod(
                        ChromeTabbedActivity.class,
                        this,
                        "maybeHandleUrlIntent",
                        Intent.class,
                        intent);
    }

    public RootUiCoordinator getRootUiCoordinator() {
        return mRootUiCoordinator;
    }

    public MultiInstanceManager getMultiInstanceManager() {
        return (MultiInstanceManager)
                QoraiReflectionUtil.getField(
                        ChromeTabbedActivity.class, "mMultiInstanceManager", this);
    }

    private void exitQorai() {
        LayoutInflater inflater =
                (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View view = inflater.inflate(R.layout.qorai_exit_confirmation, null);
        DialogInterface.OnClickListener onClickListener =
                (dialog, button) -> {
                    if (button == AlertDialog.BUTTON_POSITIVE) {
                        ApplicationLifetime.terminate(false);
                    } else {
                        dialog.dismiss();
                    }
                };

        AlertDialog.Builder alert =
                new AlertDialog.Builder(this, R.style.ThemeOverlay_BrowserUI_AlertDialog);
        AlertDialog alertDialog =
                alert.setTitle(R.string.menu_exit)
                        .setView(view)
                        .setPositiveButton(R.string.qorai_action_yes, onClickListener)
                        .setNegativeButton(R.string.qorai_action_no, onClickListener)
                        .create();
        alertDialog.getDelegate().setHandleNativeActionModesEnabled(false);
        alertDialog.show();
    }

    /*
     * Whether we want to pretend to be a custom tab. May be usefull to avoid certain patches,
     * when we want to have the same behaviour as in custom tabs.
     */
    public void spoofCustomTab(boolean spoof) {
        mSpoofCustomTab = spoof;
    }

    @Override
    public boolean isCustomTab() {
        if (mSpoofCustomTab) {
            return true;
        }

        return super.isCustomTab();
    }

    public void showQuickActionSearchEnginesView(int keypadHeight) {
        if (mQuickSearchEnginesView != null
                || !QuickSearchEnginesUtil.getQuickSearchEnginesFeature()) {
            return;
        }
        mQuickSearchEnginesView =
                getLayoutInflater().inflate(R.layout.quick_search_engines_view, null);
        RecyclerView recyclerView =
                (RecyclerView)
                        mQuickSearchEnginesView.findViewById(
                                R.id.quick_search_engines_recyclerview);
        LinearLayoutManager linearLayoutManager =
                new LinearLayoutManager(QoraiActivity.this, LinearLayoutManager.HORIZONTAL, false);
        recyclerView.setLayoutManager(linearLayoutManager);

        ImageView quickSearchEnginesSettings =
                (ImageView)
                        mQuickSearchEnginesView.findViewById(R.id.quick_search_engines_settings);
        quickSearchEnginesSettings.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        openQuickSearchEnginesSettings();
                    }
                });

        Runnable onQuickSearchEnginesReady =
                () -> {
                    if (isActivityFinishingOrDestroyed()) return;

                    quickSearchEnginesReady(recyclerView, keypadHeight);
                };
        TemplateUrlServiceFactory.getForProfile(getCurrentProfile())
                .runWhenLoaded(onQuickSearchEnginesReady);
    }

    private void quickSearchEnginesReady(RecyclerView recyclerView, int keypadHeight) {
        List<QuickSearchEnginesModel> searchEngines =
                QuickSearchEnginesUtil.getQuickSearchEnginesForView(getCurrentProfile());

        QuickSearchEnginesModel defaultQuickSearchEnginesModel =
                QuickSearchEnginesUtil.getDefaultSearchEngine(getCurrentProfile());
        searchEngines.add(0, defaultQuickSearchEnginesModel);

        if (!getCurrentProfile().isOffTheRecord()
                && QoraiQoraPrefUtils.shouldShowQoraQuickSearchEngine()) {
            QuickSearchEnginesModel qoraQuickSearchEnginesModel =
                    new QuickSearchEnginesModel(
                            "",
                            "",
                            "",
                            true,
                            QuickSearchEnginesModel.QuickSearchEnginesModelType.AI_ASSISTANT);
            searchEngines.add(0, qoraQuickSearchEnginesModel);
        }

        QuickSearchEnginesViewAdapter adapter =
                new QuickSearchEnginesViewAdapter(QoraiActivity.this, searchEngines, this);
        recyclerView.setAdapter(adapter);
        if (mQuickSearchEnginesView.getParent() == null) {
            WindowManager.LayoutParams params =
                    new WindowManager.LayoutParams(
                            WindowManager.LayoutParams.MATCH_PARENT,
                            WindowManager.LayoutParams.WRAP_CONTENT,
                            WindowManager.LayoutParams.TYPE_APPLICATION_PANEL,
                            WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE,
                            WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            params.gravity = Gravity.BOTTOM;
            params.y = keypadHeight; // Position the view above the keyboard

            WindowManager windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
            windowManager.addView(mQuickSearchEnginesView, params);
        }
    }

    public void removeQuickActionSearchEnginesView() {
        if (mQuickSearchEnginesView != null && mQuickSearchEnginesView.getParent() != null) {
            WindowManager windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
            windowManager.removeView(mQuickSearchEnginesView);
            mQuickSearchEnginesView = null;
        }
    }

    private void maybeExecuteQoraVoicePrompt() {
        Intent intent = getIntent();
        WebContents webContents = getCurrentWebContents();
        if (intent != null
                && IntentUtils.safeGetBooleanExtra(
                        intent, IntentHandler.EXTRA_INVOKED_FROM_APP_WIDGET, false)
                && IntentUtils.safeGetBooleanExtra(
                        intent, QoraiIntentHandler.EXTRA_INVOKED_FROM_APP_WIDGET_QORA, false)
                && !IntentUtils.safeGetBooleanExtra(
                        intent, QoraiIntentHandler.EXTRA_QORA_VOICE_PROMPT_INVOKED, false)
                && webContents != null) {
            // Marks that Qora prompt was invoked to avoid re-invoke on resume
            intent.putExtra(QoraiIntentHandler.EXTRA_QORA_VOICE_PROMPT_INVOKED, true);
            new QoraiQoraVoiceRecognitionHandler(
                            webContents.getTopLevelNativeWindow(), webContents, "")
                    .startVoiceRecognition();
        }
    }

    // QuickSearchCallback
    @Override
    public void onSearchEngineClick(int position, QuickSearchEnginesModel quickSearchEnginesModel) {
        if (getActivityTab() == null) {
            return;
        }
        String query = getQoraiToolbarLayout().getLocationBarQuery();
        if (position == 0
                && quickSearchEnginesModel.getType()
                        == QuickSearchEnginesModel.QuickSearchEnginesModelType.AI_ASSISTANT) {
            QoraiQoraUtils.openQoraQuery(getActivityTab().getWebContents(), "", query, true);
        } else {
            String quickSearchEngineUrl =
                    GOOGLE_SEARCH_ENGINE_KEYWORD.equals(quickSearchEnginesModel.getKeyword())
                            ? QuickSearchEnginesUtil.GOOGLE_SEARCH_ENGINE_URL
                            : quickSearchEnginesModel.getUrl();
            LoadUrlParams loadUrlParams =
                    new LoadUrlParams(
                            quickSearchEngineUrl
                                    .replace("{searchTerms}", query)
                                    .replace("{inputEncoding}", "UTF-8"));
            getActivityTab().loadUrl(loadUrlParams);
        }
        getQoraiToolbarLayout().clearOmniboxFocus();
    }

    @Override
    public void loadSearchEngineLogo(
            ImageView logoView, QuickSearchEnginesModel quickSearchEnginesModel) {
        QuickSearchEnginesUtil.loadSearchEngineLogo(
                getCurrentProfile(), logoView, quickSearchEnginesModel.getKeyword());
    }

    @Override
    public void onKeyboardOpened(int keyboardHeight) {
        runOnUiThread(
                () -> {
                    if (!isFinishing()
                            && !isDestroyed()
                            && getQoraiToolbarLayout().isUrlBarFocused()
                            && !getQoraiToolbarLayout().getLocationBarQuery().isEmpty()) {
                        showQuickActionSearchEnginesView(keyboardHeight);
                    }
                });
    }

    @Override
    public void onKeyboardClosed() {
        removeQuickActionSearchEnginesView();
    }

    @Override
    public void onSharedPreferenceChanged(
            SharedPreferences sharedPreferences, @Nullable String key) {
        if (ChromePreferenceKeys.TOOLBAR_TOP_ANCHORED.equals(key)) {
            Activity currentActivity = ApplicationStatus.getLastTrackedFocusedActivity();
            if (currentActivity == null) {
                currentActivity = this;
            }
            QoraiRelaunchUtils.askForRelaunch(currentActivity);
        }
    }

    @Override
    public void onNewIntentWithNative(Intent intent) {
        // If intent comes from our own package, check if we need to redirect upstream's urls (for
        // help, support, etc.).
        if (intent != null
                && intent.getAction() != null
                && Intent.ACTION_VIEW.equals(intent.getAction())
                && intent.getPackage() != null
                && intent.getPackage().equals(getPackageName())) {
            String url = IntentHandler.getUrlFromIntent(intent);
            if (url != null) {
                if (url.equals(QoraiIntentHandler.CONNECTION_INFO_HELP_URL)) {
                    intent.setData(Uri.parse(QoraiIntentHandler.QORAI_CONNECTION_INFO_HELP_URL));
                } else if (url.equals(QoraiIntentHandler.FALLBACK_SUPPORT_URL)) {
                    intent.setData(Uri.parse(QoraiIntentHandler.QORAI_FALLBACK_SUPPORT_URL));
                }
            }
        }
    }
}
