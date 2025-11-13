/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.base;

import org.chromium.build.annotations.NullMarked;

@NullMarked
public final class QoraiPreferenceKeys {
    public static final String QORAI_BOTTOM_TOOLBAR_ENABLED_KEY =
            "qorai_bottom_toolbar_enabled_key";
    public static final String QORAI_BOTTOM_TOOLBAR_SET_KEY = "qorai_bottom_toolbar_enabled";
    public static final String QORAI_IS_MENU_FROM_BOTTOM = "qorai_is_menu_from_bottom";
    public static final String QORAI_USE_CUSTOM_TABS = "use_custom_tabs";
    public static final String QORAI_APP_OPEN_COUNT = "qorai_app_open_count";
    public static final String QORAI_IS_DEFAULT = "qorai_is_default";
    public static final String QORAI_WAS_DEFAULT_ASK_COUNT = "qorai_was_default_ask_count";
    public static final String QORAI_SET_DEFAULT_BOTTOM_SHEET_COUNT =
            "qorai_set_default_bottom_sheet_count";
    public static final String QORAI_DEFAULT_DONT_ASK = "qorai_default_dont_ask";
    public static final String QORAI_UPDATE_EXTRA_PARAM =
            "org.chromium.chrome.browser.upgrade.UPDATE_NOTIFICATION_NEW";
    public static final String QORAI_NOTIFICATION_PREF_NAME =
            "org.chromium.chrome.browser.upgrade.NotificationUpdateTimeStampPreferences_New";
    public static final String QORAI_MILLISECONDS_NAME =
            "org.chromium.chrome.browser.upgrade.Milliseconds_New";
    public static final String QORAI_DOWNLOADS_AUTOMATICALLY_OPEN_WHEN_POSSIBLE =
            "org.chromium.chrome.browser.downloads.Automatically_Open_When_Possible";
    public static final String QORAI_DOWNLOADS_DOWNLOAD_PROGRESS_NOTIFICATION_BUBBLE =
            "org.chromium.chrome.browser.downloads.Download_Progress_Notification_Bubble";
    public static final String QORAI_DOUBLE_RESTART =
            "org.chromium.chrome.browser.Qorai_Double_Restart";
    public static final String QORAI_TAB_GROUPS_ENABLED =
            "org.chromium.chrome.browser.Qorai_Tab_Groups_Enabled";
    public static final String QORAI_TAB_GROUPS_ENABLED_DEFAULT_VALUE =
            "org.chromium.chrome.browser.Qorai_Tab_Groups_Enabled_Default_Value";
    public static final String QORAI_DISABLE_SHARING_HUB =
            "org.chromium.chrome.browser.Qorai_Disable_Sharing_Hub";
    public static final String QORAI_NEWS_CHANGE_SOURCE = "qorai_news_change_source";
    public static final String QORAI_NEWS_FEED_HASH = "qorai_news_feed_hash";
    public static final String QORAI_NEWS_PREF_SHOW_NEWS = "kNewTabPageShowToday";
    public static final String QORAI_NEWS_PREF_TURN_ON_NEWS = "kQoraiNewsOptedIn";
    public static final String QORAI_USE_BIOMETRICS_FOR_WALLET =
            "org.chromium.chrome.browser.Qorai_Use_Biometrics_For_Wallet";
    public static final String QORAI_BIOMETRICS_FOR_WALLET_IV =
            "org.chromium.chrome.browser.Qorai_Biometrics_For_Wallet_Iv";
    public static final String QORAI_BIOMETRICS_FOR_WALLET_ENCRYPTED =
            "org.chromium.chrome.browser.Qorai_Biometrics_For_Wallet_Encrypted";
    public static final String QORAI_AD_FREE_CALLOUT_DIALOG = "qorai_ad_free_callout_dialog";
    public static final String QORAI_OPENED_YOUTUBE = "qorai_opened_youtube";
    public static final String QORAI_DEFERRED_DEEPLINK_PLAYLIST =
            "qorai_deferred_deeplink_playlist";
    public static final String QORAI_DEFERRED_DEEPLINK_VPN = "qorai_deferred_deeplink_vpn";
    public static final String QORAI_CLOSE_TABS_ON_EXIT = "close_tabs_on_exit";
    public static final String QORAI_CLEAR_ON_EXIT = "clear_on_exit";
    public static final String QORAI_QUICK_ACTION_SEARCH_AND_BOOKMARK_WIDGET_TILES =
            "org.chromium.chrome.browser.widget.quickactionsearchandbookmark.QuickActionSearchAndBookmarkWidgetProvider.TILES";
    public static final String ENABLE_MULTI_WINDOWS = "enable_multi_windows";
    public static final String ENABLE_MULTI_WINDOWS_UPGRADE = "enable_multi_windows_upgrade";

    public static final String QORAI_QORA_AUTOCOMPLETE =
            "org.chromium.chrome.browser.Qorai_Qora_AutoComplete";

    public static final String CUSTOMIZABLE_QORAI_MENU_ITEM_ID_FORMAT =
            "customizable_qorai_menu_item_id_%s";

    // Playlist preference keys
    public static final String PREF_ENABLE_PLAYLIST = "enable_playlist";
    public static final String PREF_ADD_TO_PLAYLIST_BUTTON = "add_to_playlist_button";
    public static final String PREF_REMEMBER_FILE_PLAYBACK_POSITION =
            "remember_file_playback_position";
    public static final String PREF_REMEMBER_LIST_PLAYBACK_POSITION =
            "remember_list_playback_position";
    public static final String PREF_CONTINUOUS_LISTENING = "continuous_listening";
    public static final String PREF_RESET_PLAYLIST = "reset_playlist";

    // These are dynamic keys
    public static final String QORAI_RECYCLERVIEW_POSITION = "recyclerview_visible_position_";
    public static final String QORAI_RECYCLERVIEW_OFFSET_POSITION = "recyclerview_offset_position_";

    public static final String QORAI_IN_APP_UPDATE_TIMING = "in_app_update_timing";

    public static final String DAY_ZERO_EXPT_VARIANT = "day_zero_expt_variant";

    public static final String SHOW_UNDO_WHEN_TABS_CLOSED = "show_undo_when_tabs_closed";

    public static final String OPEN_YT_IN_QORAI_DIALOG = "open_yt_in_qorai_dialog";

    public static final String QORAI_QUICK_SEARCH_ENGINES = "quick_search_engines";
    public static final String QORAI_QUICK_SEARCH_ENGINES_FEATURE = "quick_search_engines_feature";
    public static final String QORAI_QUICK_SEARCH_ENGINES_PREVIOUS_DSE =
            "quick_search_engines_previous_dse";
    public static final String MIGRATE_YAHOO_JP_QSE = "migrate_yahoo_jp_qse";

    public static final String QORAI_SAFE_BROWSING_ERRORS =
            "org.chromium.qorai.browser.Qorai_SAFE_BROWSING_ERRORS";

    public static final String DEFAULT_SEARCH_ENGINE_CHANGED = "default_search_engine_changed";

    public static final String QORAI_DEFAULT_SEARCH_ENGINE_MIGRATED_JP =
            "qorai_default_search_engine_migrated_jp";

    /*
     * Checks if preference key is used in Qorai.
     * It's no op currently. We might reconsider
     * using it in the future for keys sanitation
     */
    public static boolean isQoraiKeyInUse(String key) {
        return true;
    }
}
