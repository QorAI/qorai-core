/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.base;

import org.chromium.build.annotations.NullMarked;

/** A list of feature flags exposed to Java. */
@NullMarked
public abstract class QoraiFeatureList {
    public static final String NATIVE_QORAI_WALLET = "NativeQoraiWallet";
    public static final String USE_DEV_UPDATER_URL = "UseDevUpdaterUrl";
    public static final String FORCE_WEB_CONTENTS_DARK_MODE = "WebContentsForceDark";
    public static final String ENABLE_FORCE_DARK = "enable-force-dark";
    public static final String ENABLE_PARALLEL_DOWNLOADING = "enable-parallel-downloading";
    public static final String QORAI_SEARCH_OMNIBOX_BANNER = "QoraiSearchOmniboxBanner";
    public static final String QORAI_BACKGROUND_VIDEO_PLAYBACK = "QoraiBackgroundVideoPlayback";
    public static final String QORAI_PICTURE_IN_PICTURE_FOR_YOUTUBE_VIDEOS =
            "QoraiPictureInPictureForYouTubeVideos";
    public static final String QORAI_ANDROID_SAFE_BROWSING = "QoraiAndroidSafeBrowsing";
    public static final String QORAI_VPN_LINK_SUBSCRIPTION_ANDROID_UI =
            "QoraiVPNLinkSubscriptionAndroidUI";
    public static final String DEBOUNCE = "QoraiDebounce";
    public static final String QORAI_GOOGLE_SIGN_IN_PERMISSION = "QoraiGoogleSignInPermission";
    public static final String QORAI_LOCALHOST_PERMISSION = "QoraiLocalhostPermission";
    public static final String QORAI_PLAYLIST = "Playlist";
    public static final String HTTPS_BY_DEFAULT = "HttpsByDefault";
    public static final String QORAI_FORGET_FIRST_PARTY_STORAGE = "QoraiForgetFirstPartyStorage";
    public static final String QORAI_REQUEST_OTR_TAB = "QoraiRequestOTRTab";
    public static final String AI_CHAT = "AIChat";
    public static final String AI_CHAT_HISTORY = "AIChatHistory";
    public static final String QORAI_SHOW_STRICT_FINGERPRINTING_MODE =
            "QoraiShowStrictFingerprintingMode";
    public static final String QORAI_DAY_ZERO_EXPERIMENT = "QoraiDayZeroExperiment";
    public static final String QORAI_NEW_ANDROID_ONBOARDING = "NewAndroidOnboarding";
    public static final String QORAI_FRESH_NTP_AFTER_IDLE_EXPIREMENT =
            "QoraiFreshNtpAfterIdleExpirement";
    public static final String QORAI_FALLBACK_DOH_PROVIDER = "QoraiFallbackDoHProvider";
    public static final String QORAI_BLOCK_ALL_COOKIES_TOGGLE = "BlockAllCookiesToggle";
    public static final String QORAI_SHIELDS_ELEMENT_PICKER = "QoraiShieldsElementPicker";
    public static final String QORAI_WEB_DISCOVERY_NATIVE = "QoraiWebDiscoveryNative";
    public static final String QORAI_INCOGNITO_SCREENSHOT = "incognito-screenshot";
    public static final String QORAI_NTP_BRANDED_WALLPAPER_SURVEY_PANELIST =
            "QoraiNTPBrandedWallpaperSurveyPanelist";
    public static final String QORAI_ACCOUNT = "QoraiAccount";
    public static final String QORAI_ANDROID_DYNAMIC_COLORS = "QoraiAndroidDynamicColors";
    public static final String QORAI_ORIGIN = "QoraiOrigin";
}
