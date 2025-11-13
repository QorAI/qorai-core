/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.tabbed_mode;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageButton;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;
import androidx.appcompat.content.res.AppCompatResources;
import androidx.core.content.ContextCompat;
import androidx.core.graphics.drawable.DrawableCompat;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.base.DeviceInfo;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.qorai.browser.customize_menu.CustomizeQoraiMenu;
import org.chromium.qorai_vpn.mojom.QoraiVpnConstants;
import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.ActivityTabProvider;
import org.chromium.chrome.browser.QoraiRewardsNativeWorker;
import org.chromium.chrome.browser.app.appmenu.AppMenuIconRowFooter;
import org.chromium.chrome.browser.bookmarks.BookmarkModel;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraPrefUtils;
import org.chromium.chrome.browser.feed.webfeed.WebFeedSnackbarController;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.homepage.HomepageManager;
import org.chromium.chrome.browser.incognito.IncognitoUtils;
import org.chromium.chrome.browser.incognito.reauth.IncognitoReauthController;
import org.chromium.chrome.browser.layouts.LayoutStateProvider;
import org.chromium.chrome.browser.multiwindow.QoraiMultiWindowUtils;
import org.chromium.chrome.browser.multiwindow.MultiWindowModeStateDispatcher;
import org.chromium.chrome.browser.multiwindow.MultiWindowUtils;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.readaloud.ReadAloudController;
import org.chromium.chrome.browser.set_default_browser.QoraiSetDefaultBrowserUtils;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tinker_tank.TinkerTankDelegate;
import org.chromium.chrome.browser.toolbar.ToolbarManager;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;
import org.chromium.chrome.browser.toolbar.menu_button.QoraiMenuButtonCoordinator;
import org.chromium.chrome.browser.toolbar.top.QoraiToolbarLayoutImpl;
import org.chromium.chrome.browser.ui.appmenu.AppMenuDelegate;
import org.chromium.chrome.browser.ui.appmenu.AppMenuHandler;
import org.chromium.chrome.browser.ui.appmenu.AppMenuHandler.AppMenuItemType;
import org.chromium.chrome.browser.ui.appmenu.AppMenuItemProperties;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnPrefUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnProfileUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnUtils;
import org.chromium.components.browser_ui.accessibility.PageZoomManager;
import org.chromium.components.dom_distiller.core.DomDistillerFeatures;
import org.chromium.components.embedder_support.util.UrlUtilities;
import org.chromium.components.webapps.WebappsUtils;
import org.chromium.ui.modaldialog.ModalDialogManager;
import org.chromium.ui.modelutil.MVCListAdapter;
import org.chromium.ui.modelutil.PropertyModel;

import java.util.Arrays;
import java.util.List;
import java.util.function.Supplier;

/** Qorai's extension for TabbedAppMenuPropertiesDelegate */
@NullMarked
public class QoraiTabbedAppMenuPropertiesDelegate extends TabbedAppMenuPropertiesDelegate {
    private final AppMenuDelegate mQoraiAppMenuDelegate;
    private final ObservableSupplier<BookmarkModel> mBookmarkModelSupplier;
    private boolean mJunitIsTesting;
    private final Context mQoraiContext;

    public QoraiTabbedAppMenuPropertiesDelegate(
            Context context,
            ActivityTabProvider activityTabProvider,
            MultiWindowModeStateDispatcher multiWindowModeStateDispatcher,
            TabModelSelector tabModelSelector,
            ToolbarManager toolbarManager,
            View decorView,
            AppMenuDelegate appMenuDelegate,
            OneshotSupplier<LayoutStateProvider> layoutStateProvider,
            ObservableSupplier<BookmarkModel> bookmarkModelSupplier,
            WebFeedSnackbarController.FeedLauncher feedLauncher,
            ModalDialogManager modalDialogManager,
            SnackbarManager snackbarManager,
            @NonNull
                    OneshotSupplier<IncognitoReauthController>
                            incognitoReauthControllerOneshotSupplier,
            Supplier<ReadAloudController> readAloudControllerSupplier,
            PageZoomManager pageZoomManager) {
        super(
                context,
                activityTabProvider,
                multiWindowModeStateDispatcher,
                tabModelSelector,
                toolbarManager,
                decorView,
                appMenuDelegate,
                layoutStateProvider,
                bookmarkModelSupplier,
                feedLauncher,
                modalDialogManager,
                snackbarManager,
                incognitoReauthControllerOneshotSupplier,
                readAloudControllerSupplier,
                pageZoomManager);

        mQoraiAppMenuDelegate = appMenuDelegate;
        mBookmarkModelSupplier = bookmarkModelSupplier;
        mQoraiContext = context;
    }

    private void onFooterViewInflated(AppMenuHandler appMenuHandler, View view) {
        // If it's still null, just hide the whole view
        if (mBookmarkModelSupplier.get() == null) {
            if (view != null) {
                view.setVisibility(View.GONE);
            }
            // Normally it should not happen
            assert false;
            return;
        }

        if (view instanceof AppMenuIconRowFooter) {
            ((AppMenuIconRowFooter) view)
                    .initialize(
                            appMenuHandler,
                            mBookmarkModelSupplier.get(),
                            mActivityTabProvider.get(),
                            mQoraiAppMenuDelegate);
        }

        // Hide bookmark button if bottom toolbar is enabled and address bar is on top.
        ImageButton bookmarkButton = view.findViewById(R.id.bookmark_this_page_id);
        if (bookmarkButton != null
                && BottomToolbarConfiguration.isQoraiBottomControlsEnabled()
                && BottomToolbarConfiguration.isToolbarTopAnchored()) {
            bookmarkButton.setVisibility(View.GONE);
        }

        boolean showForwardButton = BottomToolbarConfiguration.isToolbarTopAnchored();
        ImageButton forwardButton = view.findViewById(R.id.forward_menu_id);
        if (forwardButton != null) {
            showForwardButton = showForwardButton || forwardButton.isEnabled();
            forwardButton.setVisibility(showForwardButton ? View.VISIBLE : View.GONE);
        }

        ImageButton shareButton = view.findViewById(R.id.share_menu_id);
        boolean showShareButton =
                BottomToolbarConfiguration.isToolbarTopAnchored() || !showForwardButton;
        if (shareButton != null) {
            Tab currentTab = mActivityTabProvider.get();
            if (currentTab != null && UrlUtilities.isNtpUrl(currentTab.getUrl().getSpec())) {
                shareButton.setEnabled(false);
            }
            shareButton.setVisibility(showShareButton ? View.VISIBLE : View.GONE);
        }

        ImageButton homeButton = view.findViewById(R.id.home_menu_id);
        if (homeButton != null && HomepageManager.getInstance() != null) {
            homeButton.setVisibility(
                    BottomToolbarConfiguration.isToolbarBottomAnchored()
                                    && HomepageManager.getInstance().isHomepageEnabled()
                            ? View.VISIBLE
                            : View.GONE);
        }
    }

    @Override
    public @Nullable View buildFooterView(AppMenuHandler appMenuHandler) {
        if (isMenuButtonInBottomToolbar() && shouldShowPageMenu()) {
            View footer =
                    LayoutInflater.from(mQoraiContext).inflate(R.layout.icon_row_menu_footer, null);

            this.onFooterViewInflated(appMenuHandler, footer);

            return footer;
        }
        return null;
    }

    private boolean isMenuButtonInBottomToolbar() {
        return QoraiMenuButtonCoordinator.isMenuFromBottom();
    }

    private void maybeReplaceIcons(MVCListAdapter.ModelList modelList) {
        if (!shouldShowIconBeforeItem()) return;

        for (int i = 0; i < modelList.size(); ++i) {
            MVCListAdapter.ListItem item = modelList.get(i);
            Integer itemId = item.model.get(AppMenuItemProperties.MENU_ITEM_ID);
            if (itemId == null) continue;

            if (itemId == R.id.new_tab_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(mQoraiContext, R.drawable.ic_new_tab_page));
            } else if (itemId == R.id.new_incognito_tab_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(
                                mQoraiContext, R.drawable.qorai_menu_new_private_tab));
            } else if (itemId == R.id.new_tab_group_menu_id
                    || itemId == R.id.add_to_group_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(mQoraiContext, R.drawable.browser_group));
            } else if (itemId == R.id.all_bookmarks_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(
                                mQoraiContext, R.drawable.qorai_menu_bookmarks));
            } else if (itemId == R.id.recent_tabs_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(
                                mQoraiContext, R.drawable.qorai_menu_recent_tabs));
            } else if (itemId == R.id.open_history_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(
                                mQoraiContext, R.drawable.qorai_menu_history));
            } else if (itemId == R.id.downloads_menu_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(
                                mQoraiContext, R.drawable.qorai_menu_downloads));
            } else if (itemId == R.id.preferences_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(
                                mQoraiContext, R.drawable.qorai_menu_settings));
            } else if (itemId == R.id.download_page_id) {
                item.model.set(
                        AppMenuItemProperties.ICON,
                        AppCompatResources.getDrawable(mQoraiContext, R.drawable.ic_download));
            }
        }
    }

    @Override
    public boolean shouldShowNewWindow() {
        return QoraiMultiWindowUtils.shouldEnableMultiWindows() && super.shouldShowNewWindow();
    }

    @Override
    protected boolean shouldShowMoveToOtherWindow() {
        return QoraiMultiWindowUtils.shouldEnableMultiWindows()
                && super.shouldShowMoveToOtherWindow();
    }

    /**
     * Builds the complete list of main menu items for the Customize menu settings screen.
     *
     * <p>This method creates a comprehensive list of all available main menu items that users can
     * customize through the menu settings. The list includes items like "New Tab", "History",
     * "Downloads", "Qorai Wallet", etc., based on feature availability and device configuration.
     *
     * <p><strong>Note on Icons:</strong> The returned menu items do not include drawable icons
     * because {@link android.graphics.drawable.Drawable} objects cannot be parceled across activity
     * boundaries. Instead, the settings screen uses {@link
     * CustomizeQoraiMenu#getDrawableResFromMenuItemId(int)} to map menu item IDs to their
     * corresponding drawable resource IDs for display.
     *
     * @return a ModelList containing all customizable main menu items with their IDs and titles
     */
    public MVCListAdapter.ModelList buildMainMenuModelList() {
        MVCListAdapter.ModelList modelList = new MVCListAdapter.ModelList();

        // New Tab
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.new_tab_menu_id, R.string.menu_new_tab, 0)));

        // New Incognito Tab
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.new_incognito_tab_menu_id,
                                R.string.menu_new_incognito_tab,
                                0)));

        // Add to Group
        if (ChromeFeatureList.sTabGroupParityBottomSheetAndroid.isEnabled()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.add_to_group_menu_id, R.string.menu_add_tab_to_group, 0)));
        }

        if (ChromeFeatureList.sAndroidPinnedTabs.isEnabled()) {
            // Pin
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.pin_tab_menu_id, R.string.menu_pin_tab, 0)));

            // Unpin
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.unpin_tab_menu_id, R.string.menu_unpin_tab, 0)));
        }

        // New Window
        if (!DeviceInfo.isAutomotive()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.new_window_menu_id, R.string.menu_new_window, 0)));
        }

        // New Incognito Window
        if (IncognitoUtils.shouldOpenIncognitoAsWindow() && !DeviceInfo.isAutomotive()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.new_incognito_window_menu_id,
                                    R.string.menu_new_incognito_window,
                                    0)));
        }

        // Move to other window
        if (MultiWindowUtils.instanceSwitcherEnabled()
                && MultiWindowUtils.isMultiInstanceApi31Enabled()
                && !DeviceInfo.isAutomotive()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.move_to_other_window_menu_id,
                                    R.string.menu_move_to_other_window,
                                    0)));
        }

        // Manage windows

        // Remove the windows count placeholder.
        String manageWindows =
                mContext.getString(R.string.menu_manage_all_windows, 0)
                        .replaceAll("\\s*\\(\\d+\\)$", "");

        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildBaseModelForTextItem(R.id.manage_all_windows_menu_id)
                                .with(AppMenuItemProperties.TITLE, manageWindows)
                                .build()));

        // Open History
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.open_history_menu_id, R.string.menu_history, 0)));

        // Tinker Tank
        if (TinkerTankDelegate.isEnabled()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.tinker_tank_menu_id, R.string.menu_tinker_tank, 0)));
        }

        // Downloads
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.downloads_menu_id, R.string.menu_downloads, 0)));

        // Bookmarks
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.all_bookmarks_menu_id, R.string.menu_bookmarks, 0)));

        // Recent Tabs
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.recent_tabs_menu_id, R.string.menu_recent_tabs, 0)));

        // Add Qorai specific items.
        if (ChromeFeatureList.isEnabled(QoraiFeatureList.NATIVE_QORAI_WALLET)) {
            modelList.add(buildQoraiWalletItem());
        }
        if (ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_PLAYLIST)) {
            modelList.add(buildQoraiPlaylistItem());
            modelList.add(buildQoraiAddToPlaylistItem());
        }
        if (QoraiQoraPrefUtils.isQoraEnabled()) {
            modelList.add(buildQoraiQoraItem());
        }

        modelList.add(buildSetDefaultBrowserItem());

        if (QoraiVpnUtils.isVpnFeatureSupported(mContext)) {
            modelList.add(buildQoraiVpnItem());
            if (QoraiVpnPrefUtils.isSubscriptionPurchase()
                    && !TextUtils.isEmpty(QoraiVpnPrefUtils.getRegionIsoCode())) {
                modelList.add(buildQoraiVpnLocationIconItem());
            }
        }
        QoraiRewardsNativeWorker qoraiRewardsNativeWorker = QoraiRewardsNativeWorker.getInstance();
        if (qoraiRewardsNativeWorker != null && qoraiRewardsNativeWorker.isSupported()) {
            modelList.add(buildQoraiRewardsItem());
        }

        modelList.add(buildQoraiNewsItem());
        modelList.add(buildExitItem());
        return modelList;
    }

    /**
     * Builds the complete list of page action items for the Customize menu settings screen.
     *
     * <p>This method creates a comprehensive list of all available page action menu items that
     * users can customize through the menu settings. Page actions are context-sensitive menu items
     * that operate on the current page, such as "Share", "Download Page", "Print", "Find in Page",
     * "Translate", etc., based on feature availability and current page context.
     *
     * <p><strong>Note on Icons:</strong> The returned menu items do not include drawable icons
     * because {@link android.graphics.drawable.Drawable} objects cannot be parceled across activity
     * boundaries. Instead, the settings screen uses {@link
     * CustomizeQoraiMenu#getDrawableResFromMenuItemId(int)} to map menu item IDs to their
     * corresponding drawable resource IDs for display.
     *
     * @return a ModelList containing all customizable page action menu items with their IDs and
     *     titles
     */
    public MVCListAdapter.ModelList buildPageActionsModelList() {
        // Page Zoom
        final MVCListAdapter.ModelList modelList = new MVCListAdapter.ModelList();
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.page_zoom_id, R.string.page_zoom_menu_title, 0)));
        // Share
        if (mIsTablet) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.share_menu_id, R.string.menu_share_page, 0)));
        }

        // Download Page
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.download_page_id, R.string.menu_download_page, 0)));

        // Print
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(R.id.print_id, R.string.menu_print, 0)));

        // Price Tracking enable
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.enable_price_tracking_menu_id,
                                R.string.enable_price_tracking_menu_item,
                                0)));

        // Price Tracking disable
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.disable_price_tracking_menu_id,
                                R.string.disable_price_tracking_menu_item,
                                0)));

        // AI / AI PDF
        if (ChromeFeatureList.isEnabled(
                ChromeFeatureList.ADAPTIVE_BUTTON_IN_TOP_TOOLBAR_PAGE_SUMMARY)) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.ai_web_menu_id, R.string.menu_summarize_with_ai, 0)));
        }

        // Find in page
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.find_in_page_id, R.string.menu_find_in_page, 0)));

        // Translate
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.translate_id, R.string.menu_translate, 0)));

        // Read aloud
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.readaloud_menu_id, R.string.menu_listen_to_this_page, 0)));

        // Reader mode
        if (DomDistillerFeatures.showAlwaysOnEntryPoint()
                || DomDistillerFeatures.sReaderModeDistillInApp.isEnabled()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.reader_mode_menu_id, R.string.show_reading_mode_text, 0)));
        }

        // Open with…
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.open_with_id, R.string.menu_open_with, 0)));

        // Universal Install / Open Web APK
        if (WebappsUtils.isAddToHomeIntentSupported()) {
            // This is the 'webapp is already installed' case, so we offer to open the webapp.
            String appName = mContext.getString(R.string.webapp);
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuItemType.STANDARD,
                            buildBaseModelForTextItem(R.id.open_webapk_id)
                                    .with(
                                            AppMenuItemProperties.TITLE,
                                            mContext.getString(R.string.menu_open_webapk, appName))
                                    .build()));

            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.universal_install, R.string.menu_add_to_homescreen, 0)));
        }

        // RDS
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.reader_mode_prefs_id, R.string.menu_reader_mode_prefs, 0)));

        // Auto Dark
        if (ChromeFeatureList.isEnabled(
                ChromeFeatureList.DARKEN_WEBSITES_CHECKBOX_IN_THEMES_SETTING)) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.auto_dark_web_contents_id,
                                    R.string.menu_auto_dark_web_contents,
                                    0)));
        }

        // Paint Preview
        if (ChromeFeatureList.sPaintPreviewDemo.isEnabled()) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.paint_preview_show_id,
                                    R.string.menu_paint_preview_show,
                                    0)));
        }

        // Get Image Descriptions
        modelList.add(
                new MVCListAdapter.ListItem(
                        AppMenuHandler.AppMenuItemType.STANDARD,
                        buildModelForStandardMenuItem(
                                R.id.get_image_descriptions_id,
                                R.string.menu_get_image_descriptions,
                                0)));

        // Listen to the Feed
        if (ChromeFeatureList.isEnabled(ChromeFeatureList.FEED_AUDIO_OVERVIEWS)) {
            modelList.add(
                    new MVCListAdapter.ListItem(
                            AppMenuHandler.AppMenuItemType.STANDARD,
                            buildModelForStandardMenuItem(
                                    R.id.listen_to_feed_id, R.string.menu_listen_to_feed, 0)));
        }

        return modelList;
    }

    @Override
    public MVCListAdapter.ModelList buildMenuModelList() {
        MVCListAdapter.ModelList modelList = super.buildMenuModelList();

        int menuGroup = getMenuGroup();
        if (menuGroup == MenuGroup.PAGE_MENU) {
            populateQoraiPageModeMenu(modelList);
        }
        // Apply Qorai icons.
        maybeReplaceIcons(modelList);

        // Customize menu item visibility.
        CustomizeQoraiMenu.applyCustomization(mContext.getResources(), modelList);

        return modelList;
    }

    private void populateQoraiPageModeMenu(MVCListAdapter.ModelList modelList) {
        // Remove items that we don't use in Qorai.
        maybeRemoveMenuItems(
                modelList,
                R.id.quick_delete_menu_id,
                R.id.quick_delete_divider_line_id,
                R.id.ntp_customization_id,
                R.id.help_id);
        if (!mIsTablet) {
            maybeRemoveMenuItems(modelList, R.id.share_menu_id);
        }

        // Add Qorai specific items.
        if (ChromeFeatureList.isEnabled(QoraiFeatureList.NATIVE_QORAI_WALLET)) {
            addMenuItemAfter(
                    modelList, buildQoraiWalletItem(), Arrays.asList(R.id.all_bookmarks_menu_id));
        }
        if (ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_PLAYLIST)
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.PREF_ENABLE_PLAYLIST, true)) {
            addMenuItemAfter(
                    modelList,
                    buildQoraiPlaylistItem(),
                    Arrays.asList(R.id.qorai_wallet_id, R.id.all_bookmarks_menu_id));
        }
        if (ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_PLAYLIST)
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.PREF_ENABLE_PLAYLIST, true)
                && !ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.PREF_ADD_TO_PLAYLIST_BUTTON, true)
                && QoraiToolbarLayoutImpl.mShouldShowPlaylistMenu) {
            addMenuItemAfter(
                    modelList,
                    buildQoraiAddToPlaylistItem(),
                    Arrays.asList(
                            R.id.qorai_playlist_id,
                            R.id.qorai_wallet_id,
                            R.id.all_bookmarks_menu_id));
        }
        if (QoraiQoraPrefUtils.isQoraEnabled()) {
            Tab tab = mActivityTabProvider.get();
            if (tab != null && !tab.isIncognito()) {
                addMenuItemAfter(
                        modelList,
                        buildQoraiQoraItem(),
                        Arrays.asList(
                                R.id.add_to_playlist_id,
                                R.id.qorai_playlist_id,
                                R.id.qorai_wallet_id,
                                R.id.all_bookmarks_menu_id));
            }
        }
        if (!QoraiSetDefaultBrowserUtils.isQoraiSetAsDefaultBrowser(mQoraiContext)) {
            modelList.add(buildSetDefaultBrowserItem());
        }
        if (!mJunitIsTesting) {
            if (QoraiVpnUtils.isVpnFeatureSupported(mQoraiContext)) {
                modelList.add(buildQoraiVpnItem());
                if (QoraiVpnPrefUtils.isSubscriptionPurchase()
                        && !TextUtils.isEmpty(QoraiVpnPrefUtils.getRegionIsoCode())) {
                    modelList.add(buildQoraiVpnLocationIconItem());
                }
            }
            QoraiRewardsNativeWorker qoraiRewardsNativeWorker =
                    QoraiRewardsNativeWorker.getInstance();
            if (qoraiRewardsNativeWorker != null && qoraiRewardsNativeWorker.isSupported()) {
                modelList.add(buildQoraiRewardsItem());
            }
        }
        modelList.add(buildQoraiNewsItem());
        modelList.add(buildCustomMenuItem());
        modelList.add(buildExitItem());
    }

    private void maybeRemoveMenuItems(MVCListAdapter.ModelList modelList, int... itemIds) {
        for (int itemId : itemIds) {
            for (int i = 0; i < modelList.size(); ++i) {
                MVCListAdapter.ListItem item = modelList.get(i);
                if (item.model.get(AppMenuItemProperties.MENU_ITEM_ID) == itemId) {
                    modelList.removeAt(i);
                    break;
                }
            }
        }
    }

    /**
     * Adds a new menu item after the last item with an ID in the previousItemIds list.
     *
     * @param modelList The model list to which the item will be added.
     * @param itemToAdd The item to add to the model list.
     * @param previousItemIds A list of IDs of items that should precede the new item.
     */
    private void addMenuItemAfter(
            MVCListAdapter.ModelList modelList,
            MVCListAdapter.ListItem itemToAdd,
            List<Integer> previousItemIds) {
        for (int i = modelList.size() - 1; i >= 0; i--) {
            MVCListAdapter.ListItem item = modelList.get(i);
            if (previousItemIds.contains(item.model.get(AppMenuItemProperties.MENU_ITEM_ID))) {
                modelList.add(i + 1, itemToAdd);
                return;
            }
        }
        // If the previous item is not found, just add it to the end.
        modelList.add(itemToAdd);
    }

    @Override
    boolean shouldShowIconRow() {
        if (isMenuButtonInBottomToolbar()) {
            return false;
        }

        return super.shouldShowIconRow();
    }

    private MVCListAdapter.ListItem buildSetDefaultBrowserItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.set_default_browser,
                        R.string.menu_set_default_browser,
                        shouldShowIconBeforeItem() ? R.drawable.qorai_menu_set_as_default : 0));
    }

    private MVCListAdapter.ListItem buildCustomMenuItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        CustomizeQoraiMenu.QORAI_CUSTOMIZE_ITEM_ID,
                        R.string.customize_menu_title,
                        shouldShowIconBeforeItem()
                                ? org.chromium.qorai.browser.customize_menu.R.drawable
                                        .ic_window_screwdriver
                                : 0));
    }

    private MVCListAdapter.ListItem buildExitItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.exit_id,
                        R.string.menu_exit,
                        shouldShowIconBeforeItem() ? R.drawable.qorai_menu_exit : 0));
    }

    private MVCListAdapter.ListItem buildQoraiRewardsItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.qorai_rewards_id,
                        R.string.menu_qorai_rewards,
                        shouldShowIconBeforeItem() ? R.drawable.qorai_menu_rewards : 0));
    }

    private MVCListAdapter.ListItem buildQoraiWalletItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.qorai_wallet_id,
                        R.string.menu_qorai_wallet,
                        shouldShowIconBeforeItem() ? R.drawable.ic_crypto_wallets : 0));
    }

    private MVCListAdapter.ListItem buildQoraiPlaylistItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.qorai_playlist_id,
                        R.string.qorai_playlist,
                        shouldShowIconBeforeItem() ? R.drawable.ic_open_playlist : 0));
    }

    private MVCListAdapter.ListItem buildQoraiAddToPlaylistItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.add_to_playlist_id,
                        R.string.playlist_add_to_playlist,
                        shouldShowIconBeforeItem() ? R.drawable.ic_baseline_add_24 : 0));
    }

    private MVCListAdapter.ListItem buildQoraiNewsItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.qorai_news_id,
                        R.string.qorai_news_title,
                        shouldShowIconBeforeItem() ? R.drawable.ic_news : 0));
    }

    private MVCListAdapter.ListItem buildQoraiQoraItem() {
        return new MVCListAdapter.ListItem(
                AppMenuHandler.AppMenuItemType.STANDARD,
                buildModelForStandardMenuItem(
                        R.id.qorai_qora_id,
                        R.string.menu_qoraiqora,
                        shouldShowIconBeforeItem() ? R.drawable.ic_qorai_ai : 0));
    }

    private MVCListAdapter.ListItem buildQoraiVpnItem() {
        return new MVCListAdapter.ListItem(
                AppMenuItemType.TITLE_BUTTON,
                buildModelForMenuItemWithCheckbox(
                        R.id.request_qorai_vpn_id,
                        R.string.qorai_vpn,
                        shouldShowIconBeforeItem() ? R.drawable.ic_vpn : 0,
                        R.id.request_qorai_vpn_check_id,
                        QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(mQoraiContext)));
    }

    private MVCListAdapter.ListItem buildQoraiVpnLocationIconItem() {
        String serverLocation = " %s  %s - %s";
        String regionName =
                QoraiVpnPrefUtils.getRegionPrecision()
                                .equals(QoraiVpnConstants.REGION_PRECISION_COUNTRY)
                        ? mQoraiContext.getString(R.string.optimal_text)
                        : QoraiVpnPrefUtils.getRegionNamePretty();
        Drawable secondaryActionIcon =
                AppCompatResources.getDrawable(mQoraiContext, R.drawable.ic_chevron_right);
        secondaryActionIcon = DrawableCompat.wrap(secondaryActionIcon);
        DrawableCompat.setTint(
                secondaryActionIcon,
                ContextCompat.getColor(mQoraiContext, R.color.vpn_timer_icon_color));
        PropertyModel model =
                buildModelForMenuItemWithSecondaryButton(
                        R.id.request_vpn_location_id,
                        R.string.change_location,
                        0 /* iconResId */,
                        R.id.request_vpn_location_icon_id,
                        "" /* secondaryActionTitle */,
                        secondaryActionIcon);
        model.set(
                AppMenuItemProperties.TITLE,
                String.format(
                        serverLocation,
                        QoraiVpnUtils.countryCodeToEmoji(QoraiVpnPrefUtils.getRegionIsoCode()),
                        QoraiVpnPrefUtils.getRegionIsoCode(),
                        regionName));
        return new MVCListAdapter.ListItem(AppMenuItemType.TITLE_BUTTON, model);
    }

    @Override
    protected PropertyModel buildPageInfoModel(@Nullable Tab currentTab) {
        // Instead of the info button, we show the share button in Qorai.
        PropertyModel shareButton =
                buildModelForIcon(
                        R.id.info_menu_id, R.string.share, R.string.share, R.drawable.share_icon);
        shareButton.set(
                AppMenuItemProperties.ENABLED,
                (currentTab != null && !UrlUtilities.isNtpUrl(currentTab.getUrl().getSpec())));
        return shareButton;
    }

    /**
     * Method to ensure that the object is created for junit tests to avoid calling the native
     * portion of code.
     *
     * @param isJunitTesting flag indicating whether the native code should be avoided.
     */
    @VisibleForTesting
    public void setIsJunitTesting(boolean isJunitTesting) {
        mJunitIsTesting = isJunitTesting;
    }
}
