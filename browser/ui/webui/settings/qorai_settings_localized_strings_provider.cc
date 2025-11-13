/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_settings_localized_strings_provider.h"

#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "qorai/browser/shell_integrations/buildflags/buildflags.h"
#include "qorai/browser/ui/webui/qorai_settings_ui.h"
#include "qorai/browser/ui/webui/settings/qorai_privacy_handler.h"
#include "qorai/components/ai_chat/core/browser/model_validator.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_locale_utils.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/qorai_wayback_machine/pref_names.h"
#include "qorai/components/commander/common/features.h"
#include "qorai/components/commands/common/features.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/url_constants.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/containers/buildflags/buildflags.h"
#include "qorai/components/email_aliases/features.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/request_otr/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/version_info/version_info.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "qorai/grit/qorai_generated_resources_webui_strings.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/media/router/media_router_feature.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/webui_url_constants.h"
#include "chrome/grit/branded_strings.h"
#include "chrome/grit/generated_resources.h"
#include "components/google/core/common/google_util.h"
#include "components/grit/qorai_components_strings.h"
#include "components/grit/qorai_components_webui_strings.h"
#include "components/prefs/pref_service.h"
#include "components/signin/public/base/signin_pref_names.h"
#include "content/public/browser/web_ui_data_source.h"
#include "extensions/buildflags/buildflags.h"
#include "extensions/common/extension_urls.h"
#include "net/base/features.h"
#include "ui/base/l10n/l10n_util.h"

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/tor/tor_profile_service_factory.h"
#endif

namespace settings {

namespace {

constexpr char16_t kWebRTCLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/"
    u"360017989132-How-do-I-change-my-Privacy-Settings-#webrtc";
constexpr char16_t kQoraiBuildInstructionsUrl[] =
    u"https://github.com/qorai/qorai-browser/wiki";
constexpr char16_t kQoraiLicenseUrl[] = u"https://mozilla.org/MPL/2.0/";
constexpr char16_t kQoraiReleaseTagPrefix[] =
    u"https://github.com/qorai/qorai-browser/releases/tag/v";
#if BUILDFLAG(ENABLE_CONTAINERS)
constexpr char16_t kContainersLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/39077103885325";
#endif
constexpr char16_t kGoogleLoginLearnMoreURL[] =
    u"https://github.com/qorai/qorai-browser/wiki/"
    u"Allow-Google-login---Third-Parties-and-Extensions";
constexpr char16_t kUnstoppableDomainsLearnMoreURL[] =
    u"https://github.com/qorai/qorai-browser/wiki/"
    u"Resolve-Methods-for-Unstoppable-Domains";
constexpr char16_t kEnsOffchainLookupLearnMoreURL[] =
    u"https://github.com/qorai/qorai-browser/wiki/ENS-offchain-lookup";
constexpr char16_t kQoraiSyncGuideUrl[] =
    u"https://support.qorai.app/hc/en-us/articles/360047642371-Sync-FAQ";
constexpr char16_t kDeAmpLearnMoreUrl[] =
    u"https://support.qorai.app/hc/en-us/articles/8611298579981";
constexpr char16_t kDebounceLearnMoreUrl[] =
    u"https://qorai.com/privacy-updates/11-debouncing/";
constexpr char16_t kEnableNftDiscoveryLearnMoreUrl[] =
    u"https://github.com/qorai/qorai-browser/wiki/"
    u"NFT-Discovery";
constexpr char16_t kBlockAllCookiesLearnMoreUrl[] =
    u"https://github.com/qorai/qorai-browser/wiki/"
    u"Block-all-cookies-global-Shields-setting";
constexpr char16_t kQoraCustomModelsLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/"
    u"34070140231821-How-do-I-use-the-Bring-Your-Own-Model-BYOM-with-Qorai-Qora";

constexpr char16_t kTabOrganizationLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/"
    u"35200007195917-How-to-use-Tab-Focus-Mode";

constexpr char16_t kQoraMemoryLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/38441287509261";

constexpr char16_t kQoraPrivacyPolicyURL[] =
    u"https://qorai.com/privacy/browser/#qorai-qora";

constexpr char16_t kAdBlockOnlyModeLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/38076796692109";

constexpr char16_t kSurveyPanelistLearnMoreURL[] =
    u"https://support.qorai.app/hc/en-us/articles/36550092449165";

constexpr char16_t kExtensionsV2LearnMoreURL[] =
    u"https://qorai.com/blog/qorai-shields-manifest-v3/";

void QoraiAddCommonStrings(content::WebUIDataSource* html_source,
                           Profile* profile) {
  webui::LocalizedString localized_strings[] = {
      {"importExtensions", IDS_SETTINGS_IMPORT_EXTENSIONS_CHECKBOX},
      {"importPayments", IDS_SETTINGS_IMPORT_PAYMENTS_CHECKBOX},
      {"siteSettingsAutoplay", IDS_SETTINGS_SITE_SETTINGS_AUTOPLAY},
      {"siteSettingsCategoryAutoplay", IDS_SETTINGS_SITE_SETTINGS_AUTOPLAY},
      {"siteSettingsAutoplayAllow", IDS_SETTINGS_SITE_SETTINGS_AUTOPLAY_ALLOW},
      {"siteSettingsAutoplayBlock", IDS_SETTINGS_SITE_SETTINGS_AUTOPLAY_BLOCK},

      {"siteSettingsEthereum", IDS_SETTINGS_SITE_SETTINGS_ETHEREUM},
      {"siteSettingsCategoryEthereum", IDS_SETTINGS_SITE_SETTINGS_ETHEREUM},
      {"siteSettingsEthereumAsk", IDS_SETTINGS_SITE_SETTINGS_ETHEREUM_ASK},
      {"siteSettingsEthereumBlock", IDS_SETTINGS_SITE_SETTINGS_ETHEREUM_BLOCK},
      {"siteSettingsSolana", IDS_SETTINGS_SITE_SETTINGS_SOLANA},
      {"siteSettingsCategorySolana", IDS_SETTINGS_SITE_SETTINGS_SOLANA},
      {"siteSettingsSolanaAsk", IDS_SETTINGS_SITE_SETTINGS_SOLANA_ASK},
      {"siteSettingsSolanaBlock", IDS_SETTINGS_SITE_SETTINGS_SOLANA_BLOCK},
      {"siteSettingsCardano", IDS_SETTINGS_SITE_SETTINGS_CARDANO},
      {"siteSettingsCardanoAsk", IDS_SETTINGS_SITE_SETTINGS_CARDANO_ASK},
      {"siteSettingsCardanoBlock", IDS_SETTINGS_SITE_SETTINGS_CARDANO_BLOCK},

      {"siteSettingsGoogleSignIn", IDS_SETTINGS_SITE_SETTINGS_GOOGLE_SIGN_IN},
      {"siteSettingsCategoryGoogleSignIn",
       IDS_SETTINGS_SITE_SETTINGS_GOOGLE_SIGN_IN},
      {"siteSettingsGoogleSignInAsk",
       IDS_SETTINGS_SITE_SETTINGS_GOOGLE_SIGN_IN_ASK},
      {"siteSettingsGoogleSignInBlock",
       IDS_SETTINGS_SITE_SETTINGS_GOOGLE_SIGN_IN_BLOCK},
      {"siteSettingsGoogleSignInBlockExceptions",
       IDS_SETTINGS_SITE_SETTINGS_GOOGLE_SIGN_IN_BLOCK_EXCEPTIONS},
      {"siteSettingsGoogleSignInAllowExceptions",
       IDS_SETTINGS_SITE_SETTINGS_GOOGLE_SIGN_IN_ALLOW_EXCEPTIONS},

      {"siteSettingsQoraiOpenAIChat",
       IDS_SETTINGS_SITE_SETTINGS_QORAI_OPEN_AI_CHAT},
      {"siteSettingsQoraiOpenAIChatAsk",
       IDS_SETTINGS_SITE_SETTINGS_QORAI_OPEN_AI_CHAT_ASK},
      {"siteSettingsQoraiOpenAIChatBlock",
       IDS_SETTINGS_SITE_SETTINGS_QORAI_OPEN_AI_CHAT_BLOCK},

      {"siteSettingsLocalhostAccess",
       IDS_SETTINGS_SITE_SETTINGS_LOCALHOST_ACCESS},
      {"siteSettingsCategoryLocalhostAccess",
       IDS_SETTINGS_SITE_SETTINGS_LOCALHOST_ACCESS},
      {"siteSettingsLocalhostAccessAsk",
       IDS_SETTINGS_SITE_SETTINGS_LOCALHOST_ACCESS_ASK},
      {"siteSettingsLocalhostAccessBlock",
       IDS_SETTINGS_SITE_SETTINGS_LOCALHOST_ACCESS_BLOCK},
      {"siteSettingsLocalhostAccessBlockExceptions",
       IDS_SETTINGS_SITE_SETTINGS_LOCALHOST_ACCESS_BLOCK_EXCEPTIONS},
      {"siteSettingsLocalhostAccessAllowExceptions",
       IDS_SETTINGS_SITE_SETTINGS_LOCALHOST_ACCESS_ALLOW_EXCEPTIONS},
      {"qoraiGetStartedTitle", IDS_SETTINGS_QORAI_GET_STARTED_TITLE},
      {"qoraiOriginTitle", IDS_SETTINGS_QORAI_ORIGIN_TITLE},
      {"qoraiOriginHeadingTitle", IDS_SETTINGS_QORAI_ORIGIN_HEADING_TITLE},
      {"qoraiOriginHeadingDescription1",
       IDS_SETTINGS_QORAI_ORIGIN_HEADING_DESCRIPTION1},
      {"qoraiOriginHeadingDescription2",
       IDS_SETTINGS_QORAI_ORIGIN_HEADING_DESCRIPTION2},
      {"qoraiOriginSectionAdsTitle",
       IDS_SETTINGS_QORAI_ORIGIN_ADS_SECTION_TITLE},
      {"qoraiOriginRewardsToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_REWARDS_TOGGLE_TITLE},
      {"qoraiOriginSectionAnalyticsTitle",
       IDS_SETTINGS_QORAI_ORIGIN_ANALYTICS_SECTION_TITLE},
      {"qoraiOriginSectionFeaturesTitle",
       IDS_SETTINGS_QORAI_ORIGIN_FEATURES_SECTION_TITLE},
      {"qoraiOriginQoraAiToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_QORA_AI_TOGGLE_TITLE},
      {"qoraiOriginNewsToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_NEWS_TOGGLE_TITLE},
      {"qoraiOriginTalkToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_TALK_TOGGLE_TITLE},
      {"qoraiOriginWaybackMachineToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_WAYBACK_MACHINE_TOGGLE_TITLE},
      {"qoraiOriginSpeedReaderToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_SPEED_READER_TOGGLE_TITLE},
      {"qoraiOriginWebDiscoveryProjectToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_WEB_DISCOVERY_PROJECT_TOGGLE_TITLE},
      {"qoraiOriginP3AToggleTitle", IDS_SETTINGS_QORAI_ORIGIN_P3A_TOGGLE_TITLE},
      {"qoraiOriginStatsReportingToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_STATS_REPORTING_TOGGLE_TITLE},
      {"qoraiOriginTorWindowsToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_TOR_WINDOWS_TOGGLE_TITLE},
      {"qoraiOriginVpnToggleTitle", IDS_SETTINGS_QORAI_ORIGIN_VPN_TOGGLE_TITLE},
      {"qoraiOriginWalletToggleTitle",
       IDS_SETTINGS_QORAI_ORIGIN_WALLET_TOGGLE_TITLE},
      {"qoraiOriginResetToDefaultsTitle",
       IDS_SETTINGS_QORAI_ORIGIN_RESET_TO_DEFAULTS_TITLE},
      {"siteSettingsShields", IDS_SETTINGS_SITE_SETTINGS_SHIELDS},
      {"siteSettingsShieldsStatus", IDS_SETTINGS_SITE_SETTINGS_SHIELDS_STATUS},
      {"siteSettingsShieldsUp", IDS_SETTINGS_SITE_SETTINGS_SHIELDS_UP},
      {"siteSettingsShieldsDown", IDS_SETTINGS_SITE_SETTINGS_SHIELDS_DOWN},
      {"siteSettingsShieldsDescription",
       IDS_SETTINGS_SITE_SETTINGS_SHIELDS_DESCRIPTION},
      {"appearanceSettingsQoraiTheme",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_THEMES},
      {"appearanceSettingsThemesGalleryUrl",
       IDS_SETTINGS_APPEARANCE_SETTINGS_THEMES_GALLERY_URL},
      {"appearanceSettingsOpenWebStore",
       IDS_SETTINGS_APPEARANCE_SETTINGS_OPEN_WEB_STORE},
      {"appearanceSettingsShowBookmarksButton",
       IDS_SETTINGS_APPEARANCE_SETTINGS_SHOW_BOOKMARKS_BUTTON},
      {"appearanceSettingsLocationBarIsWide",
       IDS_SETTINGS_APPEARANCE_SETTINGS_LOCATION_BAR_IS_WIDE},
      {"appearanceSettingsWebViewRoundedCorners",
       IDS_SETTINGS_APPEARANCE_SETTINGS_WEB_VIEW_ROUNDED_CORNERS},
      {"appearanceSettingsShowQoraiNewsButtonLabel",
       IDS_SETTINGS_SHOW_QORAI_NEWS_BUTTON_LABEL},
      {"appearanceSettingsShowQoraButtonLabel",
       IDS_SETTINGS_SHOW_QORA_BUTTON_LABEL},
      {"appearanceSettingsBookmarBar", IDS_SETTINGS_SHOW_BOOKMARK_BAR},
      {"appearanceSettingsBookmarBarAlways",
       IDS_SETTINGS_ALWAYS_SHOW_BOOKMARK_BAR_ALWAYS},
      {"appearanceSettingsBookmarBarNTP",
       IDS_SETTINGS_ALWAYS_SHOW_BOOKMARK_BAR_ON_NTP},
      {"appearanceSettingsBookmarBarNever",
       IDS_SETTINGS_NEVER_SHOW_BOOKMARK_BAR},
      {"appearanceSettingsBookmarBarAlwaysDesc",
       IDS_SETTINGS_ALWAYS_SHOW_BOOKMARK_BAR_ALWAYS_DESC},
      {"appearanceSettingsBookmarBarNTPDesc",
       IDS_SETTINGS_ALWAYS_SHOW_BOOKMARK_BAR_ON_NTP_DESC},
      {"appearanceSettingsBookmarBarNeverDesc",
       IDS_SETTINGS_NEVER_SHOW_BOOKMARK_BAR_DESC},
      {"appearanceSettingsShowAutocompleteInAddressBar",
       IDS_SETTINGS_APPEARANCE_SETTINGS_SHOW_AUTOCOMPLETE_IN_ADDRESS_BAR},
      {"appearanceSettingsUseOnDeviceSuggestions",
       IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_ON_DEVICE},
      {"appearanceSettingsUseHistorySuggestions",
       IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_HISTORY},
      {"appearanceSettingsUseBookmarkSuggestions",
       IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_BOOKMARKS},
      {"appearanceSettingsUseCommanderSuggestions",
       IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_COMMANDER},
      {"appearanceSettingsUseQoraSuggestions",
       IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_QORA},
      {"appearanceSettingsGetMoreThemes",
       IDS_SETTINGS_APPEARANCE_SETTINGS_GET_MORE_THEMES},
      {"appearanceQoraiDefaultImagesOptionLabel",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_DEFAULT_IMAGES_OPTION_LABEL},
#if defined(TOOLKIT_VIEWS)
      {"appearanceSettingsToolbarSection",
       IDS_SETTINGS_APPEARANCE_SETTINGS_TOOLBAR_SECTION},
      {"appearanceSettingsTabsSection",
       IDS_SETTINGS_APPEARANCE_SETTINGS_TABS_SECTION},
      {"appearanceSettingsTabsUseVerticalTabs",
       IDS_SETTINGS_APPEARANCE_SETTINGS_TABS_SHOW_VERTICAL_TABS},
      {"appearanceSettingsTabsShowWindowTitle",
       IDS_SETTINGS_APPEARANCE_SETTINGS_TABS_SHOW_TITLE_BAR},
      {"appearanceSettingsTabsFloatOnMouseOver",
       IDS_SETTINGS_APPEARANCE_SETTINGS_TABS_USE_FLOATING_VERTICAL_TABS},
      {"appearanceSettingsTabHoverMode",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_HOVER_MODE},
      {"appearanceSettingsTabsVerticalTabPosition",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_VERTICAL_TAB_POSITION},
      {"appearanceSettingsTabsVerticalTabExpandedStatePerWindow",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_VERTICAL_TAB_EXPANDED_STATE_PER_WINDOW},
      {"appearanceSettingsTabsVerticalTabShowScrollbar",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_VERTICAL_TAB_SHOW_SCROLLBAR},
      {"appearanceSettingsTabsVerticalTabOnRight",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_VERTICAL_TAB_ON_RIGHT},
      {"appearanceSettingsTabsVerticalTabOnLeft",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_VERTICAL_TAB_ON_LEFT},
      {"appearanceSettingsTabHoverModeCard",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_HOVER_MODE_CARD},
      {"appearanceSettingsTabHoverModeCardWithPreview",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_HOVER_MODE_CARD_WITH_PREVIEW},
      {"appearanceSettingsTabHoverModeTooltip",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_TAB_HOVER_MODE_TOOLTIP},
      {"appearanceSettingsSharedPinnedTab",
       IDS_SETTINGS_APPEARANCE_SETTINGS_QORAI_SHARED_PINNED_TAB},
      {"sideBar", IDS_SETTINGS_APPEARNCE_SETTINGS_SIDEBAR_PART_TITLE},
      {"appearanceSettingsShowOptionTitle",
       IDS_SETTINGS_SIDEBAR_SHOW_OPTION_TITLE},
      {"appearanceSettingsShowSidebarButton",
       IDS_SETTINGS_APPEARANCE_SETTINGS_SHOW_SIDEBAR_BUTTON},
      {"appearanceSettingsShowOptionAlways", IDS_SIDEBAR_SHOW_OPTION_ALWAYS},
      {"appearanceSettingsShowOptionMouseOver",
       IDS_SIDEBAR_SHOW_OPTION_MOUSEOVER},
      {"appearanceSettingsShowOptionNever", IDS_SIDEBAR_SHOW_OPTION_NEVER},
      {"appearanceSettingsSidebarEnabledDesc",
       IDS_SETTINGS_APPEARANCE_SETTINGS_SIDEBAR_ENABLED_DESC},
      {"appearanceSettingsSidebarDisabledDesc",
       IDS_SETTINGS_APPEARANCE_SETTINGS_SIDEBAR_DISABLED_DESC},
      {"contentSettingsContentSection",
       IDS_SETTINGS_APPEARANCE_SETTINGS_CONTENT_SECTION},
#endif  // defined(TOOLKIT_VIEWS)
#if BUILDFLAG(ENABLE_QORAI_VPN)
      {"showQoraiVPNButton", IDS_SETTINGS_SHOW_VPN_BUTTON},
      {"showQoraiVPNButtonSubLabel", IDS_SETTINGS_SHOW_VPN_BUTTON_SUB_LABEL},
      {"vpnPageTitle", IDS_SETTINGS_VPN_PAGE_TITLE},
      {"useWireguardLabel", IDS_SETTINGS_VPN_PAGE_USE_WIREGUARD_TITLE},
      {"sublabelVpnConnected", IDS_SETTINGS_VPN_PAGE_SUBLABEL_VPN_CONNECTED},
#endif
#if BUILDFLAG(IS_MAC)
      {"showToolbarInFullScreen", IDS_SHOW_TOOLBAR_IN_FULL_SCREEN},
#endif
  // Search settings
#if BUILDFLAG(ENABLE_EXTENSIONS)
      {"qoraiWebDiscoveryLabel", IDS_SETTINGS_WEB_DISCOVERY_LABEL},
      {"qoraiWebDiscoverySubLabel", IDS_SETTINGS_WEB_DISCOVERY_SUBLABEL},
#endif
      {"autofillInPrivateSettingLabel",
       IDS_SETTINGS_QORAI_AUTOFILL_PRIVATE_WINDOWS_LABEL},
      {"autofillInPrivateSettingDesc",
       IDS_SETTINGS_QORAI_AUTOFILL_PRIVATE_WINDOWS_DESC},
      {"mruCyclingSettingLabel", IDS_SETTINGS_QORAI_MRU_CYCLING_LABEL},
      {"speedreaderSettingLabel", IDS_SETTINGS_SPEEDREADER_SETTING_LABEL},
      {"speedreaderFeatureLabel", IDS_SETTINGS_SPEEDREADER_FEATURE_LABEL},
      {"speedreaderFeatureSubLabel",
       IDS_SETTINGS_SPEEDREADER_FEATURE_SUB_LABEL},
      {"speedreaderEnabledForAllReadableSitesLabel",
       IDS_SETTINGS_SPEEDREADER_ALLOWED_FOR_ALL_READABLE_SITES_LABEL},
      {"speedreaderEnabledForAllReadableSitesSubLabel",
       IDS_SETTINGS_SPEEDREADER_ALLOWED_FOR_ALL_READABLE_SITES_SUB_LABEL},
      {"deAmpSettingLabel", IDS_SETTINGS_DE_AMP_LABEL},
      {"deAmpSettingSubLabel", IDS_SETTINGS_DE_AMP_SUB_LABEL},
      {"debounceSettingLabel", IDS_SETTINGS_DEBOUNCE_LABEL},
      {"debounceSettingSubLabel", IDS_SETTINGS_DEBOUNCE_SUB_LABEL},
      {"qoraiShieldsTitle", IDS_SETTINGS_QORAI_SHIELDS_TITLE},
      {"qoraiShieldsDefaultsSectionTitle",
       IDS_SETTINGS_QORAI_SHIELDS_DEFAULTS_TITLE},
      {"qoraiShieldsDefaultsSectionDescription1",
       IDS_SETTINGS_QORAI_SHIELDS_DEFAULTS_DESCRIPTION_1},
      {"qoraiShieldsDefaultsSectionDescription2",
       IDS_SETTINGS_QORAI_SHIELDS_DEFAULTS_DESCRIPTION_2},
      {"adBlockOnlyModeAlertDesc", IDS_SETTINGS_AD_BLOCK_ONLY_MODE_ALERT_DESC},
      {"adBlockOnlyModeAlertTitle",
       IDS_SETTINGS_AD_BLOCK_ONLY_MODE_ALERT_TITLE},
      {"adBlockOnlyMode", IDS_SETTINGS_AD_BLOCK_ONLY_MODE},
      {"adBlockOnlyModeLabel", IDS_SETTINGS_AD_BLOCK_ONLY_MODE_LABEL},
      {"adBlockOnlyModeDesc", IDS_SETTINGS_AD_BLOCK_ONLY_MODE_DESC},
      {"adBlockOnlyModeAlertTurnOffButton",
       IDS_SETTINGS_AD_BLOCK_ONLY_MODE_ALERT_TURN_OFF_BUTTON},
      {"socialBlocking", IDS_SETTINGS_SOCIAL_BLOCKING_DEFAULTS_TITLE},
      {"defaultView", IDS_SETTINGS_QORAI_SHIELDS_DEFAULTS_DEFAULT_VIEW_LABEL},
      {"simpleView", IDS_SETTINGS_QORAI_SHIELDS_DEFAULTS_SIMPLE_VIEW_LABEL},
      {"advancedView", IDS_SETTINGS_QORAI_SHIELDS_DEFAULTS_ADVANCED_VIEW_LABEL},
      {"adControlLabel", IDS_SETTINGS_QORAI_SHIELDS_AD_CONTROL_LABEL},
      {"cookieControlLabel", IDS_SETTINGS_QORAI_SHIELDS_COOKIE_CONTROL_LABEL},
      {"fingerprintingControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_FINGERPRINTING_CONTROL_LABEL},
      {"httpsUpgradeControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_HTTPS_UPGRADE_CONTROL_LABEL},
      {"reduceLanguageControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_REDUCE_LANGUAGE_CONTROL_LABEL},
      {"reduceLanguageDesc",
       IDS_SETTINGS_QORAI_SHIELDS_REDUCE_LANGUAGE_SUBITEM},
      {"noScriptControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_NO_SCRIPT_CONTROL_LABEL},
      {"showStatsBlockedBadgeLabel",
       IDS_SETTINGS_QORAI_SHIELDS_SHOW_STATS_BLOCKED_BADGE_LABEL},
      {"googleLoginControlLabel", IDS_GOOGLE_SIGN_IN_PERMISSION_FRAGMENT},
      {"fbEmbedControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_FACEBOOK_EMBEDDED_POSTS_LABEL},
      {"twitterEmbedControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_TWITTER_EMBEDDED_TWEETS_LABEL},
      {"linkedInEmbedControlLabel",
       IDS_SETTINGS_QORAI_SHIELDS_LINKEDIN_EMBEDDED_POSTS_LABEL},
      {"searchSuggestLabel",
       IDS_SETTINGS_QORAI_SEARCH_ENGINES_SEARCH_SUGGEST_LABEL},
      {"searchSuggestDesc",
       IDS_SETTINGS_QORAI_SEARCH_ENGINES_SEARCH_SUGGEST_DESC},
      {"otherSearchEnginesControlLabel",
       IDS_SETTINGS_QORAI_OTHER_SEARCH_ENGINES_LABEL},
      {"otherSearchEnginesControlDesc",
       IDS_SETTINGS_QORAI_OTHER_SEARCH_ENGINES_DESC},
      {"normalSearchEnginesSiteSearchEngineHeading",
       IDS_SETTINGS_NORMAL_PROFILE_SEARCH_ENGINE_HEADING},
      {"privateSearchEnginesSiteSearchEngineHeading",
       IDS_SETTINGS_PRIVATE_PROFILE_SEARCH_ENGINE_HEADING},
      {"privateSearchEngineSearchExplanation",
       IDS_SETTINGS_PRIVATE_PROFILE_SEARCH_EXPLANATION},
      {"privateSearchEngineTitle",
       IDS_SETTINGS_PRIVATE_PROFILE_SEARCH_ENGINE_TITLE},
      {"privateSearchEnginesConfirmationToastLabel",
       IDS_SETTINGS_PRIVATE_PROFILE_SEARCH_ENGINE_CHOICE_SETTINGS_CONFIRMATION_TOAST_LABEL},
      {"searchEngineListQoraiSearchDescription",
       IDS_SETTINGS_SEARCH_ENGINE_LIST_QORAI_SEARCH_DESCRIPTION},
      {"searchEngineListQoraiSearchRecommended",
       IDS_SETTINGS_SEARCH_ENGINE_LIST_QORAI_SEARCH_RECOMMENDED},
      {"blockAdsTrackersAggressive",
       IDS_SETTINGS_BLOCK_ADS_TRACKERS_AGGRESSIVE},
      {"blockAdsTrackersStandard", IDS_SETTINGS_BLOCK_ADS_TRACKERS_STANDARD},
      {"allowAdsTrackers", IDS_SETTINGS_ALLOW_ADS_TRACKERS},
      {"block3rdPartyCookies", IDS_SETTINGS_BLOCK_3RD_PARTY_COOKIES},
      {"allowAllCookies", IDS_SETTINGS_ALLOW_ALL_COOKIES},
      {"blockAllCookies", IDS_SETTINGS_BLOCK_ALL_COOKIES},
      {"forgetFirstPartyStorageLabel",
       IDS_QORAI_SHIELDS_FORGET_FIRST_PARTY_STORAGE_LABEL},
      {"forgetFirstPartyStorageSubLabel",
       IDS_QORAI_SHIELDS_FORGET_FIRST_PARTY_STORAGE_SUBLABEL},
      {"standardFingerprinting", IDS_SETTINGS_STANDARD_FINGERPRINTING},
      {"allowAllFingerprinting", IDS_SETTINGS_ALLOW_ALL_FINGERPRINTING},
      {"strictFingerprinting", IDS_SETTINGS_STRICT_FINGERPRINTING},
      {"standardHttpsUpgrade", IDS_SETTINGS_STANDARD_HTTPS_UPGRADE},
      {"disabledHttpsUpgrade", IDS_SETTINGS_DISABLED_HTTPS_UPGRADE},
      {"strictHttpsUpgrade", IDS_SETTINGS_STRICT_HTTPS_UPGRADE},
      {"webRTCPolicyLabel", IDS_SETTINGS_WEBRTC_POLICY_LABEL},
      {"webRTCPolicySubLabel", IDS_SETTINGS_WEBRTC_POLICY_SUB_LABEL},
      {"webRTCDefault", IDS_SETTINGS_WEBRTC_POLICY_DEFAULT},
      {"pushMessagingLabel", IDS_SETTINGS_PUSH_MESSAGING},
      {"defaultPublicAndPrivateInterfaces",
       IDS_SETTINGS_WEBRTC_POLICY_DEFAULT_PUBLIC_AND_PRIVATE_INTERFACES},
      {"defaultPublicInterfaceOnly",
       IDS_SETTINGS_WEBRTC_POLICY_DEFAULT_PUBLIC_INTERFACE_ONLY},
      {"disableNonProxiedUdp",
       IDS_SETTINGS_WEBRTC_POLICY_DISABLE_NON_PROXIED_UDP},
#if BUILDFLAG(ENABLE_REQUEST_OTR)
      {"requestOTRLabel", IDS_SETTINGS_REQUEST_OTR_LABEL},
      {"requestOTRSubLabel", IDS_SETTINGS_REQUEST_OTR_SUB_LABEL},
      {"requestOTRDefault", IDS_SETTINGS_REQUEST_OTR_DEFAULT},
      {"requestOTRAlways", IDS_SETTINGS_REQUEST_OTR_ALWAYS},
      {"requestOTRNever", IDS_SETTINGS_REQUEST_OTR_NEVER},
#endif
#if BUILDFLAG(IS_WIN)
      {"windowsRecallDisabledLabel",
       IDS_SETTINGS_WINDOWS_RECALL_DISABLED_LABEL},
      {"windowsRecallDisabledSubLabel",
       IDS_SETTINGS_WINDOWS_RECALL_DISABLED_SUBLABEL},
#endif
      {"qoraiSync", IDS_SETTINGS_QORAI_SYNC_TITLE},
      {"qoraiSyncSetupActionLabel", IDS_SETTINGS_QORAI_SYNC_SETUP_ACTION_LABEL},
      {"qoraiSyncSetupTitle", IDS_SETTINGS_QORAI_SYNC_SETUP_TITLE},
      {"qoraiSyncSetupSubtitle", IDS_SETTINGS_QORAI_SYNC_SETUP_SUBTITLE},
      {"qoraiSyncManageActionLabel",
       IDS_SETTINGS_QORAI_SYNC_MANAGE_ACTION_LABEL},
      {"qoraiSyncCouldNotSyncActionLabel",
       IDS_SETTINGS_QORAI_SYNC_COULD_NOT_SYNC_ACTION_LABEL},
      {"qoraiSyncWordCount", IDS_SETTINGS_QORAI_SYNC_WORD_COUNT},
      {"qoraiSyncCopied", IDS_SETTINGS_QORAI_SYNC_COPIED_TEXT},
      {"qoraiSyncQRCodeAlt", IDS_SETTINGS_QORAI_SYNC_QR_IMAGE_ALT},
      {"qoraiSyncQRError", IDS_SETTINGS_QORAI_SYNC_QR_ERROR},
      {"qoraiSyncManagerTitle", IDS_SETTINGS_QORAI_SYNC_MANAGER_TITLE},
      {"qoraiSyncSettingsTitle", IDS_SETTINGS_QORAI_SYNC_SETTINGS_TITLE},
      {"qoraiSyncSettingsSubtitle", IDS_SETTINGS_QORAI_SYNC_SETTINGS_SUBTITLE},
      {"qoraiSyncDeviceListTitle", IDS_SETTINGS_QORAI_SYNC_DEVICE_LIST_TITLE},
      {"qoraiSyncDeviceListSubtitle",
       IDS_SETTINGS_QORAI_SYNC_DEVICE_LIST_SUBTITLE},
      {"qoraiSyncDeviceListNameColumn",
       IDS_SETTINGS_QORAI_SYNC_DEVICE_LIST_NAME_COLUMN},
      {"qoraiSyncDeviceListNameThisDevice",
       IDS_SETTINGS_QORAI_SYNC_DEVICE_LIST_NAME_THIS_DEVICE},
      {"qoraiSyncDeviceListLastActiveColumn",
       IDS_SETTINGS_QORAI_SYNC_DEVICE_LIST_LAST_ACTIVE_COLUMN},
      {"qoraiSyncDeviceListRemoveColumn",
       IDS_SETTINGS_QORAI_SYNC_DEVICE_LIST_REMOVE_COLUMN},
      {"qoraiSyncSetupTitle", IDS_QORAI_SYNC_SETUP_TITLE},
      {"qoraiSyncSetupDesc", IDS_QORAI_SYNC_SETUP_DESCRIPTION},
      {"qoraiSyncStartNewChain", IDS_QORAI_SYNC_START_NEW_CHAIN_BUTTON},
      {"qoraiSyncEnterCode", IDS_QORAI_SYNC_ENTER_CODE_BUTTON},
      {"qoraiSyncChooseDeviceMobileTitle",
       IDS_QORAI_SYNC_CHOOSE_DEVICE_MOBILE_TITLE},
      {"qoraiSyncChooseDeviceComputerTitle",
       IDS_QORAI_SYNC_CHOOSE_DEVICE_COMPUTER_TITLE},
      {"qoraiSyncScanCodeTitle", IDS_QORAI_SYNC_SCAN_CODE_TITLE},
      {"qoraiSyncScanCodeDesc1",
       IDS_QORAI_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_1},
      {"qoraiSyncScanCodeDesc2",
       IDS_QORAI_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_2},
      {"qoraiSyncScanCodeDesc3",
       IDS_QORAI_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_3},
      {"qoraiSyncViewCodeTitle", IDS_QORAI_SYNC_VIEW_CODE_TITLE},
      {"qoraiSyncViewCodeDesc1",
       IDS_QORAI_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_1},
      {"qoraiSyncViewCodeDesc2",
       IDS_QORAI_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_2},
      {"qoraiSyncViewCodeDesc3",
       IDS_QORAI_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_3},
      {"qoraiSyncCodeWarning", IDS_QORAI_SYNC_CODE_WARNING},
      {"qoraiSyncViewCodeQRCodeButton",
       IDS_QORAI_SYNC_VIEW_CODE_QR_CODE_BUTTON},
      {"qoraiSyncEnterCodeTitle", IDS_QORAI_SYNC_ENTER_CODE_TITLE},
      {"qoraiSyncEnterCodeDesc", IDS_QORAI_SYNC_ENTER_CODE_DESCRIPTION},
      {"qoraiSyncViewCodeButton", IDS_QORAI_SYNC_VIEW_CODE_BUTTON},
      {"qoraiSyncAddDevice", IDS_QORAI_SYNC_ADD_DEVICE_BUTTON},
      {"qoraiSyncChooseDeviceTitle", IDS_QORAI_SYNC_CHOOSE_DEVICE_TITLE},
      {"qoraiSyncChooseDeviceDesc", IDS_QORAI_SYNC_CHOOSE_DEVICE_DESCRIPTION},
      {"qoraiSyncInvalidSyncCodeTitle", IDS_QORAI_SYNC_INVALID_SYNC_CODE_TITLE},
      {"qoraiSyncResetButton", IDS_QORAI_SYNC_RESET_BUTTON},
      {"qoraiSyncResetConfirmation", IDS_QORAI_SYNC_RESET_CONFIRMATION},
      {"qoraiSyncDeleteAccountButtonAndDialogTitle",
       IDS_QORAI_DELETE_SYNC_ACCOUNT_BUTTON_AND_DIALOG_TITLE},
      {"qoraiSyncPermanentlyDeleteAccountButton",
       IDS_QORAI_SYNC_PERMANENTLY_DELETE_ACCOUNT_BUTTON},
      {"qoraiSyncDeleteDeviceConfirmation",
       IDS_QORAI_SYNC_DELETE_DEVICE_CONFIRMATION},
      {"qoraiSyncPermanentlyDeleteAccountInProgress",
       IDS_QORAI_SYNC_PERMANENTLY_DELETE_ACCOUNT_IN_PROGRESS},
      {"qoraiSyncDeleteAccountDesc1",
       IDS_QORAI_SYNC_DELETE_ACCOUNT_DESCRIPTION_PARTIAL_1},
      {"qoraiSyncDeleteAccountDesc2",
       IDS_QORAI_SYNC_DELETE_ACCOUNT_DESCRIPTION_PARTIAL_2},
      {"qoraiSyncDeleteAccountDesc3",
       IDS_QORAI_SYNC_DELETE_ACCOUNT_DESCRIPTION_PARTIAL_3},
      {"qoraiSyncFinalSecurityWarning",
       IDS_QORAI_SYNC_FINAL_SECURITY_WARNING_TEXT},
      {"qoraiSyncPassphraseDecryptionErrorUnlockedSsMessage",
       IDS_QORAI_SYNC_PASSPHRASE_DECRYPTION_SS_UNLOCKED_ERROR_MESSAGE},
      {"qoraiSyncLeaveAndRejoinTheChainButton",
       IDS_QORAI_SYNC_LEAVE_AND_REJOIN_THE_CHAIN_BUTTON},
      {"qoraiDataCollection", IDS_QORAI_DATA_COLLECTION_SETTINGS_SECTION},
      {"qoraiWeb3", IDS_QORAI_WEB3_SETTINGS_SECTION},
      {"qoraiWeb3Domains", IDS_QORAI_WEB3_DOMAINS_SETTINGS_SECTION},
      {"qoraiTor", IDS_QORAI_TOR_SETTINGS_SECTION},
      {"qoraiWallet", IDS_QORAI_WALLET_SETTINGS_SECTION},
      {"qoraiWaybackMachineLabel",
       IDS_SETTINGS_SHOW_QORAI_WAYBACK_MACHINE_PROMPT},
      {"qoraiWarnBeforeClosingWindow",
       IDS_SETTINGS_WINDOW_CLOSING_CONFIRM_OPTION_LABEL},
      {"qoraiClosingLastTab", IDS_SETTINGS_CLOSING_LAST_TAB_OPTION_LABEL},
      {"qoraiDisableClickableMuteIndicators",
       IDS_SETTINGS_DISABLE_CLICKABLE_MUTE_INDICATORS},
      {"qoraiShowFullscreenReminder",
       IDS_SETTINGS_SHOW_FULLSCREEN_REMINDER_OPTION_LABEL},

      // Qora Assistant Page
      {"leoAssistant", IDS_SETTINGS_QORA_ASSISTANT},
      {"qoraiQoraAssistantShowIconOnToolbarLabel",
       IDS_SETTINGS_QORA_ASSISTANT_SHOW_ICON_ON_TOOLBAR_LABEL},
      {"qoraiQoraAssistantShowInContextMenuLabel",
       IDS_SETTINGS_QORA_ASSISTANT_SHOW_IN_CONTEXT_MENU_LABEL},
      {"qoraiQoraAssistantShowInContextMenuDesc",
       IDS_SETTINGS_QORA_ASSISTANT_SHOW_IN_CONTEXT_MENU_DESC},
      {"qoraiQoraAssistantTabOrganizationLabel",
       IDS_SETTINGS_QORA_ASSISTANT_TAB_ORGANIZATION_LABEL},
      {"qoraiQoraAssistantHistoryPreferenceLabel",
       IDS_SETTINGS_QORA_ASSISTANT_HISTORY_PREFERENCE_LABEL},
      {"qoraiQoraAssistantHistoryPreferenceConfirm",
       IDS_SETTINGS_QORA_ASSISTANT_HISTORY_PREFERENCE_CONFIRM},
      {"qoraiQoraAssistantResetAndClearDataLabel",
       IDS_SETTINGS_QORA_ASSISTANT_RESET_AND_CLEAR_DATA_LABEL},
      {"qoraiQoraAssistantResetAndClearDataConfirmationText",
       IDS_SETTINGS_QORA_ASSISTANT_RESET_AND_CLEAR_DATA_CONFIRMATION_LABEL},
      {"qoraiQoraAssistantAutocompleteLink",
       IDS_SETTINGS_QORA_ASSISTANT_AUTOCOMPLETE_LINK},
      {"aiChatClearHistoryData", IDS_SETTINGS_AI_CHAT_CLEAR_HISTORY_DATA_LABEL},
      {"aiChatClearHistoryDataSubLabel",
       IDS_SETTINGS_AI_CHAT_CLEAR_HISTORY_DATA_SUBLABEL},
      {"qoraiQoraPremiumLabelNonPremium",
       IDS_CHAT_UI_MODEL_PREMIUM_LABEL_NON_PREMIUM},
      {"qoraiQoraAssistantModelSelectionLabel",
       IDS_SETTINGS_QORA_ASSISTANT_MODEL_SELECTION_LABEL},
      {"qoraiQoraAssistantPersonalizationLabel",
       IDS_SETTINGS_QORA_ASSISTANT_PERSONALIZATION_LABEL},
      {"qoraiQoraAssistantCustomizationLinkLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_LINK_LABEL},
      {"qoraiQoraModelSubtitle-chat-basic", IDS_CHAT_UI_CHAT_BASIC_SUBTITLE},
      {"qoraiQoraModelSubtitle-chat-claude-instant",
       IDS_CHAT_UI_CHAT_CLAUDE_INSTANT_SUBTITLE},
      {"qoraiQoraModelSubtitle-chat-claude-haiku",
       IDS_CHAT_UI_CHAT_CLAUDE_HAIKU_SUBTITLE},
      {"qoraiQoraModelSubtitle-chat-claude-sonnet",
       IDS_CHAT_UI_CHAT_CLAUDE_SONNET_SUBTITLE},
      {"qoraiQoraModelSubtitle-chat-qwen", IDS_CHAT_UI_CHAT_QWEN_SUBTITLE},
      {"qoraiQoraModelSubtitle-chat-gemma", IDS_CHAT_UI_CHAT_GEMMA_SUBTITLE},
      {"qoraiQoraModelSubtitle-chat-deepseek-r1",
       IDS_CHAT_UI_CHAT_DEEPSEEK_R1_SUBTITLE},
      {"qoraiQoraAssistantManageUrlLabel",
       IDS_SETTINGS_QORA_ASSISTANT_MANAGE_URL},
      {"qoraiQoraAssistantByomLabel", IDS_SETTINGS_QORA_ASSISTANT_BYOM_LABEL},
      {"qoraiQoraAssistantDeleteModelConfirmation",
       IDS_SETTINGS_QORA_ASSISTANT_DELETE_MODEL_CONFIRMATION},
      {"qoraiQoraAssistantAddModelLabel",
       IDS_SETTINGS_QORA_ASSISTANT_ADD_MODEL_LABEL},
      {"qoraiQoraAssistantEditModelLabel",
       IDS_SETTINGS_QORA_ASSISTANT_EDIT_MODEL_LABEL},
      {"qoraiQoraAssistantInputModelLabel",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_LABEL},
      {"qoraiQoraAssistantInputModelRequestName",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_REQUEST_NAME},
      {"qoraiQoraAssistantInputModelServerEndpoint",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_SERVER_ENDPOINT},
      {"qoraiQoraAssistantInputModelApiKey",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_API_KEY},
      {"qoraiQoraAssistantInputModelLabelTooltipInfo",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_LABEL_TOOLTIP_INFO},
      {"qoraiQoraAssistantInputModelVisionSupport",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_VISION_SUPPORT},
      {"qoraiQoraAssistantInputModelVisionSupportTooltipInfo",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_VISION_SUPPORT_TOOLTIP_INFO},
      {"qoraiQoraAssistantInputContextSizeLabel",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_CONTEXT_SIZE},
      {"qoraiQoraAssistantInputContextSizeTooltipInfo",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_CONTEXT_SIZE_TOOLTIP_INFO},
      {"qoraiQoraAssistantInputModelRequestNameTooltipInfo",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_REQUEST_NAME_TOOLTIP_INFO},
      {"qoraiQoraAssistantInputModelServerEndpointTooltipInfo",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_SERVER_ENDPOINT_TOOLTIP_INFO},
      {"qoraiQoraAssistantInputModelApiKeyTooltipInfo",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_MODEL_API_KEY_TOOLTIP_INFO},
      {"qoraiQoraAssistantCloseButtonLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CLOSE_BUTTON_LABEL},
      {"qoraiQoraAssistantProxyNote", IDS_SETTINGS_QORA_ASSISTANT_PROXY_NOTE},
      {"qoraiQoraAssistantEndpointError",
       IDS_SETTINGS_QORA_ASSISTANT_ENDPOINT_ERROR},
      {"qoraiQoraAssistantAddNewModelButtonLabel",
       IDS_SETTINGS_QORA_ASSISTANT_ADD_NEW_BUTTON_LABEL},
      {"qoraiQoraAssistantModelListEmptyLabel",
       IDS_SETTINGS_QORA_ASSISTANT_MODEL_LIST_EMPTY_LABEL},
      {"qoraiQoraAssistantYourModelsTitle",
       IDS_SETTINGS_QORA_ASSISTANT_YOUR_MODELS_TITLE},
      {"qoraiQoraAssistantYourModelsDesc1",
       IDS_SETTINGS_QORA_ASSISTANT_YOUR_MODELS_DESC_1},
      {"qoraiQoraAssistantAboutQoraLabel",
       IDS_SETTINGS_QORA_ASSISTANT_ABOUT_QORA_LABEL},
      {"qoraiQoraAssistantAboutQoraDesc1",
       IDS_SETTINGS_QORA_ASSISTANT_ABOUT_QORA_DESC_1},
      {"qoraiQoraModelSectionTitle", IDS_CHAT_UI_MENU_TITLE_MODELS},
      {"qoraiQoraAssistantEndpointInvalidError",
       IDS_SETTINGS_QORA_ASSISTANT_ENDPOINT_INVALID_ERROR},
      {"qoraiQoraAssistantEndpointPotentiallyUnsafeError",
       IDS_SETTINGS_QORA_ASSISTANT_ENDPOINT_POTENTIALLY_UNSAFE_ERROR},
      {"qoraiQoraAssistantEndpointValidAsPrivateIp_Title",
       IDS_SETTINGS_QORA_ASSISTANT_PRIVATE_IP_NOT_ALLOWED_TITLE},
      {"qoraiQoraAssistantEndpointValidAsPrivateIp_Body",
       IDS_SETTINGS_QORA_ASSISTANT_PRIVATE_IP_NOT_ALLOWED_BODY},
      {"qoraiQoraAssistantEndpointValidAsPrivateIp_Instructions",
       IDS_SETTINGS_QORA_ASSISTANT_PRIVATE_IP_NOT_ALLOWED_INSTRUCTIONS},
      {"qoraiQoraAssistantAddModelButtonLabel",
       IDS_SETTINGS_QORA_ASSISTANT_ADD_MODEL_BUTTON_LABEL},
      {"qoraiQoraAssistantSaveModelButtonLabel",
       IDS_SETTINGS_QORA_ASSISTANT_SAVE_MODEL_BUTTON_LABEL},
      {"qoraiQoraAssistantModelSystemPromptTitle",
       IDS_SETTINGS_QORA_ASSISTANT_MODEL_SYSTEM_PROMPT_TITLE},
      {"qoraiQoraAssistantModelSystemPromptDesc",
       IDS_SETTINGS_QORA_ASSISTANT_MODEL_SYSTEM_PROMPT_DESC},
      {"qoraiQoraAssistantTokensCount", IDS_SETTINGS_QORA_ASSISTANT_TOKENS_COUNT},

      // Qora Customization
      {"qoraiQoraAssistantCustomizationTitle",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_TITLE},
      {"qoraiQoraAssistantCustomizationPageTitle",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_PAGE_TITLE},
      {"qoraiQoraAssistantCustomizationEnabledLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_ENABLED_LABEL},
      {"qoraiQoraAssistantUserMemoryEnabledLabel",
       IDS_SETTINGS_QORA_ASSISTANT_USER_MEMORY_ENABLED_LABEL},
      {"qoraiQoraAssistantCustomizationNameLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_NAME_LABEL},
      {"qoraiQoraAssistantCustomizationNamePlaceholder",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_NAME_PLACEHOLDER},
      {"qoraiQoraAssistantCustomizationJobLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_JOB_LABEL},
      {"qoraiQoraAssistantCustomizationJobPlaceholder",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_JOB_PLACEHOLDER},
      {"qoraiQoraAssistantCustomizationToneLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_TONE_LABEL},
      {"qoraiQoraAssistantCustomizationTonePlaceholder",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_TONE_PLACEHOLDER},
      {"qoraiQoraAssistantCustomizationOtherLabel",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_OTHER_LABEL},
      {"qoraiQoraAssistantCustomizationOtherPlaceholder",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_OTHER_PLACEHOLDER},
      {"qoraiQoraAssistantCustomizationSaveButton",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_SAVE_BUTTON},
      {"qoraiQoraAssistantCustomizationChangesSaved",
       IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_CHANGES_SAVED},
      {"qoraiQoraAssistantInputLengthError",
       IDS_SETTINGS_QORA_ASSISTANT_INPUT_LENGTH_ERROR},

      // Qora Assistant Memory Section
      {"qoraiQoraAssistantYourMemoriesTitle",
       IDS_SETTINGS_QORA_ASSISTANT_YOUR_MEMORIES_TITLE},
      {"qoraiQoraAssistantYourMemoriesDesc",
       IDS_SETTINGS_QORA_ASSISTANT_YOUR_MEMORIES_DESC},
      {"qoraiQoraAssistantMemoryListEmptyTitle",
       IDS_SETTINGS_QORA_ASSISTANT_MEMORY_LIST_EMPTY_TITLE},
      {"qoraiQoraAssistantMemoryListEmptyDescription",
       IDS_SETTINGS_QORA_ASSISTANT_MEMORY_LIST_EMPTY_DESCRIPTION},
      {"qoraiQoraAssistantAddNewMemoryButtonLabel",
       IDS_SETTINGS_QORA_ASSISTANT_ADD_NEW_MEMORY_BUTTON_LABEL},
      {"qoraiQoraAssistantEditMemoryDialogTitle",
       IDS_SETTINGS_QORA_ASSISTANT_EDIT_MEMORY_DIALOG_TITLE},
      {"qoraiQoraAssistantCreateMemoryDialogTitle",
       IDS_SETTINGS_QORA_ASSISTANT_CREATE_MEMORY_DIALOG_TITLE},
      {"qoraiQoraAssistantMemoryInputPlaceholder",
       IDS_SETTINGS_QORA_ASSISTANT_MEMORY_INPUT_PLACEHOLDER},
      {"qoraiQoraAssistantDeleteMemoryConfirmation",
       IDS_SETTINGS_QORA_ASSISTANT_DELETE_MEMORY_CONFIRMATION},
      {"qoraiQoraAssistantDeleteMemoryConfirmationTitle",
       IDS_SETTINGS_QORA_ASSISTANT_DELETE_MEMORY_CONFIRMATION_TITLE},
      {"qoraiQoraAssistantDeleteAllMemoriesConfirmation",
       IDS_SETTINGS_QORA_ASSISTANT_DELETE_ALL_MEMORIES_CONFIRMATION},
      {"qoraiQoraAssistantDeleteAllMemoriesConfirmationTitle",
       IDS_SETTINGS_QORA_ASSISTANT_DELETE_ALL_MEMORIES_CONFIRMATION_TITLE},
      {"qoraiQoraAssistantNoSearchResultsFound",
       IDS_SETTINGS_QORA_ASSISTANT_NO_SEARCH_RESULTS_FOUND},
      {"qoraiQoraAssistantClearSearch", IDS_SETTINGS_QORA_ASSISTANT_CLEAR_SEARCH},
      {"qoraiQoraAssistantSearchMemoriesPlaceholder",
       IDS_SETTINGS_QORA_ASSISTANT_SEARCH_MEMORIES_PLACEHOLDER},

      // Survey Panelist Page
      {"surveyPanelist", IDS_SETTINGS_SURVEY_PANELIST},
      {"qoraiSurveyPanelistLabel", IDS_SETTINGS_SURVEY_PANELIST_LABEL},
      {"qoraiSurveyPanelistDesc", IDS_SETTINGS_SURVEY_PANELIST_DESC},

      // New Tab Page
      {"qoraiNewTab", IDS_SETTINGS_NEW_TAB},
      {"qoraiNewTabQoraiRewards", IDS_SETTINGS_NEW_TAB_QORAI_REWARDS},
      {"qoraiNewTabNewTabPageShows", IDS_SETTINGS_NEW_TAB_NEW_TAB_PAGE_SHOWS},
      {"qoraiNewTabNewTabCustomizeWidgets",
       IDS_SETTINGS_NEW_TAB_NEW_TAB_CUSTOMIZE_WIDGETS},
  // Pin shortcut page
#if BUILDFLAG(ENABLE_PIN_SHORTCUT)
      {"canPinShortcut", IDS_SETTINGS_CAN_PIN_SHORTCUT},
      {"pinShortcut", IDS_SETTINGS_PIN_SHORTCUT},
#if BUILDFLAG(IS_WIN)
      {"pinShortcutSublabel", IDS_SETTINGS_PIN_SHORTCUT_SUBLABEL},
#endif
      {"shortcutPinned", IDS_SETTINGS_SHORTCUT_PINNED},
#endif
      // Rewards page
      {"qoraiRewards", IDS_SETTINGS_QORAI_REWARDS_TITLE},
      {"qoraiRewardsDisabledLabel", IDS_SETTINGS_QORAI_REWARDS_DISABLED_LABEL},
      {"qoraiRewardsDisabledSubLabel",
       IDS_SETTINGS_QORAI_REWARDS_DISABLED_SUB_LABEL},
      {"qoraiRewardsPageLabel", IDS_SETTINGS_QORAI_REWARDS_PAGE_LABEL},
      {"qoraiRewardsShowQoraiRewardsButtonLabel",
       IDS_SETTINGS_QORAI_REWARDS_SHOW_QORAI_REWARDS_BUTTON_LABEL},

      // Delete browsing data settings
      {"clearQoraiAdsData", IDS_SETTINGS_CLEAR_QORAI_ADS_DATA},
      {"resetRewardsData", IDS_SETTINGS_RESET_REWARDS_DATA},

      // Misc (TODO: Organize this)
      {"showSearchTabsBtn", IDS_SETTINGS_TABS_SEARCH_SHOW},
      {"onExitPageTitle", IDS_SETTINGS_QORAI_ON_EXIT},
      {"qoraiDefaultExtensions", IDS_SETTINGS_QORAI_DEFAULT_EXTENSIONS_TITLE},
      {"defaultEthereumWalletDesc", IDS_SETTINGS_DEFAULT_ETHEREUM_WALLET_DESC},
      {"defaultSolanaWalletDesc", IDS_SETTINGS_DEFAULT_SOLANA_WALLET_DESC},
      {"defaultCardanoWalletDesc", IDS_SETTINGS_DEFAULT_CARDANO_WALLET_DESC},
      {"defaultBaseCurrencyDesc", IDS_SETTINGS_DEFAULT_BASE_CURRENCY_DESC},
      {"defaultBaseCryptocurrencyDesc",
       IDS_SETTINGS_DEFAULT_BASE_CRYPTOCURRENCY_DESC},
      {"showQoraiwalletIconOnToolbar",
       IDS_SETTINGS_SHOW_QORAI_WALLET_ICON_ON_TOOLBAR},
      {"enableNftDiscoveryLabel", IDS_SETTINGS_ENABLE_NFT_DISCOVERY_LABEL},
      {"enableNftDiscoveryDesc", IDS_SETTINGS_ENABLE_NFT_DISCOVERY_DESC},
      {"enablePrivateWindowsLabel",
       IDS_SETTINGS_ENABLE_QORAI_WALLET_IN_PRIVATE_WINDOWS_LABEL},
      {"enablePrivateWindowsDesc",
       IDS_SETTINGS_ENABLE_QORAI_WALLET_IN_PRIVATE_WINDOWS_DESC},
      {"showQoraiwalletTestNetworks",
       IDS_SETTINGS_SHOW_QORAI_WALLET_TEST_NETWORKS},
      {"autoLockMinutes", IDS_SETTINGS_AUTO_LOCK_MINUTES},
      {"autoLockMinutesDesc", IDS_SETTINGS_AUTO_LOCK_MINUTES_DESC},
      {"googleLoginForExtensionsDesc",
       IDS_SETTINGS_GOOGLE_LOGIN_FOR_EXTENSIONS},
      {"mediaRouterEnabledDesc", IDS_SETTINGS_MEDIA_ROUTER_ENABLED_DESC},
      {"resolveUnstoppableDomainsDesc",
       IDS_SETTINGS_RESOLVE_UNSTOPPABLE_DOMAINS_DESC},
      {"resolveENSDesc", IDS_SETTINGS_RESOLVE_ENS_DESC},
      {"ensOffchainLookupTitle", IDS_SETTINGS_ENABLE_ENS_OFFCHAIN_LOOKUP_TITLE},
      {"resolveSnsDesc", IDS_SETTINGS_RESOLVE_SNS_DESC},
      {"torEnabledLabel", IDS_SETTINGS_ENABLE_TOR_TITLE},
      {"torEnabledDesc", IDS_SETTINGS_ENABLE_TOR_DESC},
      {"torConnectionSettingsTitle",
       IDS_SETTINGS_TOR_CONNECTION_SETTINGS_TITLE},
      {"torConnectionSettingsDesc", IDS_SETTINGS_TOR_CONNECTION_SETTINGS_DESC},
      {"torSnowflakeExtensionLabel",
       IDS_SETTINGS_TOR_SNOWFLAKE_EXTENSION_TITLE},
      {"torSnowflakeExtensionDesc", IDS_SETTINGS_TOR_SNOWFLAKE_EXTENSION_DESC},
      {"torSnowflakeInstallFailed", IDS_SETTINGS_TOR_SNOWFLAKE_INSTALL_FAILED},
      {"torUseBridgesTitle", IDS_SETTINGS_TOR_USE_BRIDGES_TITLE},
      {"torUseBridgesDesc", IDS_SETTINGS_TOR_USE_BRIDGES_DESC},
      {"torSelectBuiltInRadio", IDS_SETTINGS_TOR_SELECT_BUILT_IN_RADIO},
      {"torRequestBridgesRadio", IDS_SETTINGS_TOR_REQUEST_BRIDGES_RADIO},
      {"torRequestNewBridgeButton", IDS_SETTINGS_TOR_REQUEST_NEW_BRIDGE_BUTTON},
      {"torProvideBridgesRadio", IDS_SETTINGS_TOR_PROVIDE_BRIDGES_RADIO},
      {"torEnterBridgeInfoLabel", IDS_SETTINGS_TOR_ENTER_BRIDGE_INFO_LABEL},
      {"torApplyChangesButton", IDS_SETTINGS_TOR_APPLY_CHANGES_BUTTON},
      {"torRequestedBridgesPlaceholder",
       IDS_SETTINGS_TOR_REQUESTED_BRIDGES_PLACEHOLDER},
      {"torProvidedBridgesPlaceholder",
       IDS_SETTINGS_TOR_PROVIDED_BRIDGES_PLACEHOLDER},
      {"torRequestBridgeDialogTitle",
       IDS_SETTINGS_TOR_REQUEST_BRIDGE_DIALOG_TITLE},
      {"torRequestBridgeDialogWaiting",
       IDS_SETTINGS_TOR_REQUEST_BRIDGE_DIALOG_WAITING},
      {"torRequestBridgeDialogSolve",
       IDS_SETTINGS_TOR_REQUEST_BRIDGE_DIALOG_SOLVE},
      {"torRequestBridgeDialogError",
       IDS_SETTINGS_TOR_REQUEST_BRIDGE_DIALOG_ERROR},
      {"torSubmitDialogButton", IDS_SETTINGS_TOR_SUBMIT_DIALOG_BUTTON},
      {"torCancelDialogButton", IDS_SETTINGS_TOR_CANCEL_DIALOG_BUTTON},
      {"onionOnlyInTorWindowsLabel",
       IDS_SETTINGS_ONION_ONLY_IN_TOR_WINDOWS_TITLE},
      {"onionOnlyInTorWindowsDesc",
       IDS_SETTINGS_ONION_ONLY_IN_TOR_WINDOWS_DESC},
      {"widevineEnabledDesc", IDS_SETTINGS_ENABLE_WIDEVINE_DESC},
      {"restartNotice", IDS_SETTINGS_RESTART_NOTICE},
      {"relaunchButtonLabel", IDS_SETTINGS_RELAUNCH_BUTTON_LABEL},
      {"manageExtensionsV2Label", IDS_SETTINGS_MANAGE_EXTENSIONS_V2_LABEL},
      {"manageExtensionsV2SubLabel",
       IDS_SETTINGS_MANAGE_EXTENSIONS_V2_SUBLABEL},
      {"extensionsV2ToastConfirmButtonLabel",
       IDS_SETTINGS_MANAGE_EXTENSIONS_V2_TOAST_CONFIRM},
      {"extensionsV2RemoveButtonLabel",
       IDS_SETTINGS_MANAGE_EXTENSIONS_V2_REMOVE_BUTTON},
      {"manageExtensionsLabel", IDS_SETTINGS_MANAGE_EXTENSIONS_LABEL},
      {"keyboardShortcuts", IDS_EXTENSIONS_SIDEBAR_KEYBOARD_SHORTCUTS},
      {"getMoreExtensionsLabel", IDS_QORAI_SETTINGS_GET_MORE_EXTENSIONS_LABEL},
      {"getMoreExtensionsSubLabel",
       IDS_QORAI_SETTINGS_GET_MORE_EXTENSIONS_SUBLABEL},
      {"statsUsagePingEnabledTitle", IDS_QORAI_STATS_USAGE_PING_SETTING},
      {"statsUsagePingEnabledDesc", IDS_QORAI_STATS_USAGE_PING_SETTING_SUBITEM},
      {"p3aEnableTitle", IDS_QORAI_P3A_ENABLE_SETTING},
      {"p3aEnabledDesc", IDS_QORAI_P3A_ENABLE_SETTING_SUBITEM},
      {"siteSettings", IDS_SETTINGS_SITE_AND_SHIELDS_SETTINGS},
      {"showFullUrls", IDS_SETTINGS_ALWAYS_SHOW_FULL_URLS},
      {"resetZCashSyncStateInfo",
       IDS_SETTINGS_WALLET_RESET_ZCASH_SYNC_STATE_INFO},
      {"resetZCashSyncStateDesc",
       IDS_SETTINGS_WALLET_RESET_ZCASH_SYNC_STATE_DESC},
      {"resetZCashSyncStateConfirmation",
       IDS_SETTINGS_WALLET_RESET_ZCASH_SYNC_STATE_CONFIRMATION},
      {"resetZCashSyncStateConfirmed",
       IDS_SETTINGS_WALLET_RESET_ZCASH_SYNC_STATE_CONFIRMED},
      {"resetWallet", IDS_SETTINGS_WALLET_RESET},
      {"resetTransactionInfo", IDS_SETTINGS_WALLET_RESET_TRANSACTION_INFO},
      {"resetTransactionInfoDesc",
       IDS_SETTINGS_WALLET_RESET_TRANSACTION_INFO_DESC},
      {"walletResetConfirmation", IDS_SETTINGS_WALLET_RESET_CONFIRMATION},
      {"walletResetTransactionInfoConfirmation",
       IDS_SETTINGS_WALLET_RESET_TRANSACTION_INFO_CONFIRMATION},
      {"walletResetConfirmed", IDS_SETTINGS_WALLET_RESET_CONFIRMED},
      {"walletResetTransactionInfoConfirmed",
       IDS_SETTINGS_WALLET_RESET_TRANSACTION_INFO_CONFIRMED},
      {"walletNetworksLinkTitle", IDS_SETTINGS_WALLET_NETWORKS_ITEM},
      {"walletAddNetworkDialogTitle", IDS_SETTINGS_WALLET_ADD_NETWORK_TITLE},
      {"walletAddNetworkInvalidURLInput",
       IDS_SETTINGS_WALLET_ADD_NETWORK_INVALID_ADDRESS_ERROR},
      {"walletNetworkAdd", IDS_SETTINGS_WALLET_ADD_NETWORK},
      {"walletEthNetworksListTitle",
       IDS_SETTINGS_WALLET_ETH_NETWORK_LIST_TITLE},
      {"walletFilNetworksListTitle",
       IDS_SETTINGS_WALLET_FIL_NETWORK_LIST_TITLE},
      {"walletSolNetworksListTitle",
       IDS_SETTINGS_WALLET_SOL_NETWORK_LIST_TITLE},
      {"walletBtcNetworksListTitle",
       IDS_SETTINGS_WALLET_BTC_NETWORK_LIST_TITLE},
      {"walletZecNetworksListTitle",
       IDS_SETTINGS_WALLET_ZEC_NETWORK_LIST_TITLE},
      {"walletCardanoNetworksListTitle",
       IDS_SETTINGS_WALLET_CARDANO_NETWORK_LIST_TITLE},
      {"walletPolkadotNetworksListTitle",
       IDS_SETTINGS_WALLET_POLKADOT_NETWORK_LIST_TITLE},
      {"walletNetworksItemDesc", IDS_SETTINGS_WALLET_NETWORKS_ITEM_DESC},
      {"walletNetworksError", IDS_SETTINGS_WALLET_NETWORKS_ERROR},
      {"walletDeleteNetworkConfirmation",
       IDS_SETTINGS_WALLET_DELETE_NETWORK_CONFIRMATION},
      {"walletDefaultNetworkIsAlwaysVisible",
       IDS_SETTINGS_WALLET_DEFAULT_NETWORK_IS_ALWAYS_VISIBLE},
      {"walletShowHideNetwork", IDS_SETTINGS_WALLET_SHOW_HIDE_NETWORK},
      {"walletResetNetworkConfirmation",
       IDS_SETTINGS_WALLET_RESET_NETWORK_CONFIRMATION},
      {"walletAddNetworkDialogChainIdTitle",
       IDS_SETTINGS_WALLET_NETWORKS_CHAIN_ID_TITLE},
      {"walletAddNetworkDialogChainIdPlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_CHAIN_ID_PLACEHOLDER},
      {"walletAddNetworkDialogSearchForNetworkLabel",
       IDS_SETTINGS_WALLET_NETWORKS_SEARCH_FOR_NETWORK_LABEL},
      {"walletAddNetworkDialogSearchForNetworkPlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_SEARCH_FOR_NETWORK_PLACEHOLDER},
      {"walletAddNetworkDialogChainNameTitle",
       IDS_SETTINGS_WALLET_NETWORKS_CHAIN_NAME_TITLE},
      {"walletAddNetworkDialogChainNamePlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_CHAIN_NAME_PLACEHOLDER},
      {"walletAddNetworkDialogCurrencyNameTitle",
       IDS_SETTINGS_WALLET_NETWORKS_CURRENCY_NAME_TITLE},
      {"walletAddNetworkDialogCurrencyNamePlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_CURRENCY_NAME_PLACEHOLDER},
      {"walletAddNetworkDialogCurrencySymbolTitle",
       IDS_SETTINGS_WALLET_NETWORKS_CURRENCY_SYMBOL_TITLE},
      {"walletAddNetworkDialogCurrencySymbolPlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_CURRENCY_SYMBOL_PLACEHOLDER},
      {"walletAddNetworkDialogCurrencyDecimalsTitle",
       IDS_SETTINGS_WALLET_NETWORKS_CURRENCY_DECIMALS_TITLE},
      {"walletAddNetworkDialogCurrencyDecimalsPlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_CURRENCY_DECIMALS_PLACEHOLDER},
      {"walletAddNetworkDialogRpcTitle",
       IDS_SETTINGS_WALLET_NETWORKS_RPC_TITLE},
      {"walletAddNetworkDialogUrlPlaceholder",
       IDS_SETTINGS_WALLET_NETWORKS_URL_PLACEHOLDER},
      {"walletAddNetworkDialogIconsTitle",
       IDS_SETTINGS_WALLET_NETWORKS_ICONS_TITLE},
      {"walletAddNetworkDialogBlocksTitle",
       IDS_SETTINGS_WALLET_NETWORKS_BLOCKS_TITLE},
      {"walletAddNetworkMandarotyFieldError",
       IDS_SETTINGS_WALLET_NETWORKS_MANDATORY_ERROR},
      {"walletAddNetworkInvalidChainId",
       IDS_SETTINGS_WALLET_NETWORKS_CHAID_ID_ERROR},
      {"walletAddNetworkDialogFillNativeCurrencyInfo",
       IDS_SETTINGS_WALLET_NETWORKS_NATIVE_CURRENCY_ERROR},
      {"walletAddNetworkDialogReplaceNetwork",
       IDS_SETTINGS_WALLET_NETWORKS_REPLACE},
      {"walletNetworkEdit", IDS_QORAI_WALLET_NETWORK_EDIT},
      {"walletNetworkRemove", IDS_QORAI_WALLET_NETWORK_REMOVE},
      {"walletNetworkReset", IDS_QORAI_WALLET_NETWORK_RESET},
      {"walletNetworkSetAsDefault", IDS_QORAI_WALLET_NETWORK_SET_AS_DEFAULT},
      {"adblockContentFilteringLabel",
       IDS_QORAI_ADBLOCK_CONTENT_FILTERING_LABEL},
      {"adblockAddCustomFiltersListsLabel",
       IDS_QORAI_ADBLOCK_ADD_CUSTOM_FILTERS_LISTS_LABEL},
      {"adblockContentFilterLabelDesc",
       IDS_QORAI_ADBLOCK_CONTENT_FILTER_LABEL_DESCRIPTION},
      {"adblockAddCustomFiltersListsDesc",
       IDS_QORAI_ADBLOCK_ADD_CUSTOM_FILTERS_LISTS_DESC},
      {"adblockAddCustomFiltersListsNote",
       IDS_QORAI_ADBLOCK_ADD_CUSTOM_FILTERS_LISTS_NOTE},
      {"adblockCustomFiltersLabel", IDS_QORAI_ADBLOCK_CUSTOM_FILTERS_LABEL},
      {"adblockCustomFiltersDesc", IDS_QORAI_ADBLOCK_CUSTOM_FILTERS_DESC},
      {"adblockAddListsButtonLabel", IDS_QORAI_ADBLOCK_ADD_LISTS_BUTTON_LABEL},
      {"adblockShowFullListsButtonLabel",
       IDS_QORAI_ADBLOCK_SHOW_FULL_LISTS_BUTTON_LABEL},
      {"adblockUpdateListsButtonLabel",
       IDS_QORAI_ADBLOCK_UPDATE_LISTS_BUTTON_LABEL},
      {"adblockUpdateListsRetryButtonLabel",
       IDS_QORAI_ADBLOCK_UPDATE_LISTS_RETRY_BUTTON_LABEL},
      {"adblockUpdateListsUpdatedButtonLabel",
       IDS_QORAI_ADBLOCK_UPDATE_LISTS_UPDATED_BUTTON_LABEL},
      {"adblockUpdateListsUpdatingButtonLabel",
       IDS_QORAI_ADBLOCK_UPDATE_LISTS_UPDATING_BUTTON_LABEL},
      {"adblockFilterListsInputURLPlaceholder",
       IDS_QORAI_ADBLOCK_CUSTOM_FILTER_LISTS_INPUT_PLACEHOLDER},
      {"adblockContentFiltersLabel", IDS_QORAI_ADBLOCK_CONTENT_FILTERS},
      {"adblockFilterListsInputPlaceHolder",
       IDS_QORAI_ADBLOCK_FILTER_LISTS_INPUT_PLACEHOLDER},
      {"adblockFilterListsTableTitleHeader",
       IDS_QORAI_ADBLOCK_FILTER_LISTS_TABLE_TITLE_HEADER},
      {"adblockFilterListsTableUpdatedHeader",
       IDS_QORAI_ADBLOCK_FILTER_LISTS_TABLE_UPDATED_HEADER},
      {"adblockUpdateNowButtonLabel",
       IDS_QORAI_ADBLOCK_UPDATE_NOW_BUTTON_LABEL},
      {"adblockViewSourceButtonLabel",
       IDS_QORAI_ADBLOCK_VIEW_SOURCE_BUTTON_LABEL},
      {"adblockUnsubscribeButtonLabel",
       IDS_QORAI_ADBLOCK_UNSUBSCRIBE_BUTTON_LABEL},
      {"adblockSaveChangesButtonLabel", IDS_QORAI_ADBLOCK_SAVE_BUTTON_LABEL},
      {"adblockTrackingFiltersLabel", IDS_QORAI_ADBLOCK_TRACKING_FILTERS_LABEL},
      {"adblockTrackingFiltersDesc", IDS_QORAI_ADBLOCK_TRACKING_FILTERS_DESC},
      {"adblockSubscribeUrlDownloadFailed",
       IDS_QORAI_ADBLOCK_SUBSCRIBE_URL_DOWNLOAD_FAILED},
      {"adblockSubscribeUrlUpdateFailed",
       IDS_QORAI_ADBLOCK_SUBSCRIBE_URL_UPDATE_FAILED},
      {"adblockCustomListsLabel", IDS_QORAI_ADBLOCK_CUSTOM_LISTS_LABEL},
      {"adblockDeveloperModeLabel", IDS_QORAI_ADBLOCK_DEVELOPER_MODE_LABEL},
      {"adblockDeveloperModeDesc", IDS_QORAI_ADBLOCK_DEVELOPER_MODE_DESC},
      {"adblockCustomSciptletsListLabel",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLETS_LIST_LABEL},
      {"adblockAddCustomScriptletButton",
       IDS_QORAI_ADBLOCK_ADD_CUSTOM_SCRIPTLET_BUTTON},
      {"adblockAddCustomScriptletDialogTitle",
       IDS_QORAI_ADBLOCK_ADD_CUSTOM_SCRIPTLET_DIALOG_TITLE},
      {"adblockEditCustomScriptletDialogTitle",
       IDS_QORAI_ADBLOCK_EDIT_CUSTOM_SCRIPTLET_DIALOG_TITLE},
      {"adblockCustomSciptletDialogNameLabel",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_DIALOG_NAME_LABEL},
      {"adblockCustomScriptletDialogContentLabel",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_DIALOG_CONTENT_LABEL},
      {"adblockCustomScriptletDialogCancelButton",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_DIALOG_CANCEL_BUTTON},
      {"adblockCustomScriptletDialogSaveButton",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_DIALOG_SAVE_BUTTON},
      {"adblockCustomScriptletDeleteConfirmation",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_DELETE_CONFIRMATION},
      {"adblockCustomScriptletAlreadyExistsError",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_ALREADY_EXISTS_ERROR},
      {"adblockCustomScriptletInvalidNameError",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_INVALID_NAME_ERROR},
      {"adblockCustomScriptletNotFoundError",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_NOT_FOUND_ERROR},
      {"adblockCustomScriptletWarning",
       IDS_QORAI_ADBLOCK_CUSTOM_SCRIPTLET_WARNING},

      {"qoraiShortcutsPage", IDS_SETTINGS_QORAI_SHORTCUTS_TITLE},
      {"settingsSelectValueYes", IDS_SETTINGS_SELECT_VALUE_YES},
      {"settingsSelectValueNo", IDS_SETTINGS_SELECT_VALUE_NO},
      {"settingsSelectValueAsk", IDS_SETTINGS_SELECT_VALUE_ASK},
      {"qoraiShieldsSaveContactInfo",
       IDS_QORAI_SHIELDS_SAVE_CONTACT_INFO_LABEL},
      {"qoraiShieldsSaveContactInfoSublabel",
       IDS_QORAI_SHIELDS_SAVE_CONTACT_INFO_LABEL_SUBLABEL},
      {"cookieControlledByShieldsHeader",
       IDS_SETTINGS_COOKIE_CONTROLLED_BY_SHIELDS_HEADER_TEXT},
      {"cookieControlledByShieldsTooltip",
       IDS_SETTINGS_COOKIE_CONTROLLED_BY_SHIELDS_TOOLTIP_TEXT},
      {"cookieControlledByGoogleSigninTooltip",
       IDS_SETTINGS_COOKIE_CONTROLLED_BY_GOOGLE_SIGN_IN_TOOLTIP_TEXT},
  };

  html_source->AddLocalizedStrings(localized_strings);
  html_source->AddString("qoraiShieldsExampleTemplate", "example.com");
  html_source->AddString("webRTCLearnMoreURL", kWebRTCLearnMoreURL);
  html_source->AddString("googleLoginLearnMoreURL", kGoogleLoginLearnMoreURL);
  html_source->AddString("deAmpLearnMoreURL", kDeAmpLearnMoreUrl);
  html_source->AddString("debounceLearnMoreURL", kDebounceLearnMoreUrl);
  html_source->AddString("enableNftDiscoveryLearnMoreURL",
                         kEnableNftDiscoveryLearnMoreUrl);
  html_source->AddString(
      "qoraiQoraAssistantModelSystemPromptPlaceholder",
      base::ReplaceStringPlaceholders(
          l10n_util::GetStringUTF8(
              IDS_AI_CHAT_DEFAULT_CUSTOM_MODEL_SYSTEM_PROMPT),
          {"%datetime%"}, nullptr));
  auto confirmation_phrase =
      l10n_util::GetStringUTF16(IDS_SETTINGS_WALLET_RESET_CONFIRMATION_PHRASE);
  html_source->AddString("walletResetConfirmationPhrase", confirmation_phrase);
  auto confirmation_text = l10n_util::GetStringFUTF16(
      IDS_SETTINGS_WALLET_RESET_CONFIRMATION, confirmation_phrase);
  html_source->AddString("walletResetConfirmation", confirmation_text);
  auto reset_tx_confirmation_text = l10n_util::GetStringFUTF16(
      IDS_SETTINGS_WALLET_RESET_TRANSACTION_INFO_CONFIRMATION,
      confirmation_phrase);
  html_source->AddString("walletResetTransactionInfoConfirmation",
                         reset_tx_confirmation_text);
  html_source->AddString(
      "resetZCashSyncStateConfirmation",
      l10n_util::GetStringFUTF16(
          IDS_SETTINGS_WALLET_RESET_ZCASH_SYNC_STATE_CONFIRMATION,
          confirmation_phrase));
  html_source->AddString(
      "qoraiQoraAssistantInputDefaultContextSize",
      base::NumberToString16(ai_chat::kDefaultCustomModelContextSize));

  html_source->AddString("qoraiQoraAssistantTabOrganizationDesc",
                         l10n_util::GetStringFUTF16(
                             IDS_SETTINGS_QORA_ASSISTANT_TAB_ORGANIZATION_DESC,
                             kTabOrganizationLearnMoreURL));

  html_source->AddString("qoraiQoraAssistantTabOrganizationLearnMoreURL",
                         kTabOrganizationLearnMoreURL);

#if BUILDFLAG(ENABLE_EXTENSIONS)
  html_source->AddString("webDiscoveryLearnMoreURL", kWebDiscoveryLearnMoreUrl);
#endif
  html_source->AddString("speedreaderLearnMoreURL", kSpeedreaderLearnMoreUrl);
  html_source->AddString(
      "getMoreExtensionsUrl",
      base::ASCIIToUTF16(
          google_util::AppendGoogleLocaleParam(
              GURL(extension_urls::GetWebstoreExtensionsCategoryURL()),
              g_browser_process->GetApplicationLocale())
              .spec()));
  html_source->AddString("autoLockMinutesValue",
                         base::NumberToString(profile->GetPrefs()->GetInteger(
                             kQoraiWalletAutoLockMinutes)));

  html_source->AddString(
      "transactionSimulationDesc",
      l10n_util::GetStringFUTF16(IDS_QORAI_WALLET_TRANSACTION_SIMULATIONS_DESC,
                                 kTransactionSimulationLearnMoreURL));

  html_source->AddString("resolveUnstoppableDomainsSubDesc",
                         l10n_util::GetStringFUTF16(
                             IDS_SETTINGS_RESOLVE_UNSTOPPABLE_DOMAINS_SUB_DESC,
                             kUnstoppableDomainsLearnMoreURL));

#if BUILDFLAG(ENABLE_CONTAINERS)
  html_source->AddLocalizedStrings(webui::kContainersStrings);
  html_source->AddString("containersLearnMoreURL", kContainersLearnMoreURL);
#endif  // BUILDFLAG(ENABLE_CONTAINERS)
  html_source->AddString(
      "ensOffchainLookupDesc",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_ENABLE_ENS_OFFCHAIN_LOOKUP_DESC,
                                 kEnsOffchainLookupLearnMoreURL));

  html_source->AddString(
      "blockAllCookiesDeprecatedLabel",
      l10n_util::GetStringFUTF16(
          IDS_SETTINGS_QORAI_SHIELDS_COOKIE_CONTROL_BLOCK_ALL_DEPRECATED_LABEL,
          kBlockAllCookiesLearnMoreUrl));

  html_source->AddString(
      "adBlockOnlyModeDesc",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_AD_BLOCK_ONLY_MODE_DESC,
                                 kAdBlockOnlyModeLearnMoreURL));

  html_source->AddString(
      "qoraiQoraAssistantYourModelsDesc2",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_QORA_ASSISTANT_YOUR_MODELS_DESC_2,
                                 kQoraCustomModelsLearnMoreURL));

  html_source->AddString(
      "qoraiQoraAssistantAboutQoraDesc2",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_QORA_ASSISTANT_ABOUT_QORA_DESC_2,
                                 kQoraPrivacyPolicyURL));

  html_source->AddString(
      "qoraiQoraAssistantCustomizationDescription",
      l10n_util::GetStringFUTF16(
          IDS_SETTINGS_QORA_ASSISTANT_CUSTOMIZATION_DESCRIPTION,
          kQoraMemoryLearnMoreURL));

  html_source->AddString(
      "qoraiQoraAssistantYourMemoriesDesc",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_QORA_ASSISTANT_YOUR_MEMORIES_DESC,
                                 kQoraMemoryLearnMoreURL));

  html_source->AddString("qoraiSurveyPanelistLearnMoreURL",
                         kSurveyPanelistLearnMoreURL);

  html_source->AddString(
      "qoraiSurveyPanelistDesc",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_SURVEY_PANELIST_DESC,
                                 kSurveyPanelistLearnMoreURL));
  html_source->AddString(
      "extensionsV2Warn",
      l10n_util::GetStringFUTF16(IDS_SETTINGS_MANAGE_EXTENSIONS_V2_WARN,
                                 kExtensionsV2LearnMoreURL));

  // Disabled due to crash with tab group dragging.
  // TODO(https://github.com/qorai/qorai-browser/issues/49752): Re-enable.
  html_source->AddBoolean("showSplitViewDragAndDropSetting", false);
}  // NOLINT(readability/fn_size)

void QoraiAddResources(content::WebUIDataSource* html_source,
                       Profile* profile) {
  QoraiSettingsUI::AddResources(html_source, profile);
}

void QoraiAddAboutStrings(content::WebUIDataSource* html_source,
                          Profile* profile) {
  std::u16string license = l10n_util::GetStringFUTF16(
      IDS_QORAI_VERSION_UI_LICENSE, kQoraiLicenseUrl,
      chrome::kChromeUICreditsURL16, kQoraiBuildInstructionsUrl,
      kQoraiReleaseTagPrefix +
          base::UTF8ToUTF16(
              version_info::GetQoraiVersionWithoutChromiumMajorVersion()));
  html_source->AddString("aboutProductLicense", license);
}

void QoraiAddSyncStrings(content::WebUIDataSource* html_source) {
  std::u16string passphraseDecryptionErrorMessage = l10n_util::GetStringFUTF16(
      IDS_QORAI_SYNC_PASSPHRASE_DECRYPTION_ERROR_MESSAGE, kQoraiSyncGuideUrl);
  html_source->AddString("qoraiSyncPassphraseDecryptionErrorMessage",
                         passphraseDecryptionErrorMessage);
}

void QoraiAddEmailAliasesStrings(content::WebUIDataSource* html_source) {
  if (!base::FeatureList::IsEnabled(email_aliases::features::kEmailAliases)) {
    return;
  }
  html_source->AddLocalizedStrings(webui::kEmailAliasesStrings);
}

void QoraiAddQoraiAccountStrings(content::WebUIDataSource* html_source) {
  if (!qorai_account::features::IsQoraiAccountEnabled()) {
    return;
  }

  webui::LocalizedString localized_strings[] = {
      {"qoraiAccountRowTitle", IDS_SETTINGS_QORAI_ACCOUNT_ROW_TITLE},
      {"qoraiAccountRowDescription",
       IDS_SETTINGS_QORAI_ACCOUNT_ROW_DESCRIPTION},
      {"qoraiAccountGetStartedButtonLabel",
       IDS_SETTINGS_QORAI_ACCOUNT_GET_STARTED_BUTTON_LABEL},
      {"qoraiAccountManageAccountButtonLabel",
       IDS_SETTINGS_QORAI_ACCOUNT_MANAGE_ACCOUNT_BUTTON_LABEL},
  };

  html_source->AddLocalizedStrings(localized_strings);
}

}  // namespace

void QoraiAddLocalizedStrings(content::WebUIDataSource* html_source,
                              Profile* profile) {
  QoraiAddCommonStrings(html_source, profile);
  QoraiAddResources(html_source, profile);
  QoraiAddAboutStrings(html_source, profile);
  QoraiPrivacyHandler::AddLoadTimeData(html_source, profile);
  QoraiAddSyncStrings(html_source);
  QoraiAddEmailAliasesStrings(html_source);
  QoraiAddQoraiAccountStrings(html_source);

  // Load time data for qorai://settings/extensions
  html_source->AddBoolean(
      "signInAllowedOnNextStartupInitialValue",
      profile->GetPrefs()->GetBoolean(prefs::kSigninAllowedOnNextStartup));

  html_source->AddBoolean("isMediaRouterEnabled",
                          media_router::MediaRouterEnabled(profile));

  html_source->AddBoolean(
      "isHttpsByDefaultEnabled",
      base::FeatureList::IsEnabled(net::features::kQoraiHttpsByDefault));

  html_source->AddBoolean(
      "showStrictFingerprintingMode",
      base::FeatureList::IsEnabled(
          qorai_shields::features::kQoraiShowStrictFingerprintingMode));

  html_source->AddBoolean(
      "qoraiTalkDisabledByPolicy",
      profile->GetPrefs()->GetBoolean(kQoraiTalkDisabledByPolicy));

#if BUILDFLAG(ENABLE_TOR)
  html_source->AddBoolean("qoraiTorDisabledByPolicy",
                          TorProfileServiceFactory::IsTorDisabled(profile) &&
                              TorProfileServiceFactory::IsTorManaged(profile));
#endif

  if (base::FeatureList::IsEnabled(
          net::features::kQoraiFirstPartyEphemeralStorage)) {
    const webui::LocalizedString kSessionOnlyToEphemeralStrings[] = {
        {"cookiePageSessionOnlyExceptions",
         IDS_SETTINGS_COOKIES_USE_EPHEMERAL_STORAGE_EXCEPTIONS},
        {"siteSettingsSessionOnly",
         IDS_SETTINGS_SITE_SETTINGS_USE_EPHEMERAL_STORAGE},
        {"siteSettingsActionSessionOnly",
         IDS_SETTINGS_SITE_SETTINGS_USE_EPHEMERAL_STORAGE},
    };
    html_source->AddLocalizedStrings(kSessionOnlyToEphemeralStrings);
  }

  if (base::FeatureList::IsEnabled(commands::features::kQoraiCommands)) {
    html_source->AddLocalizedStrings(webui::kShortcutsStrings);
  }

  html_source->AddBoolean(
      "cosmeticFilteringCustomScriptletsEnabled",
      base::FeatureList::IsEnabled(
          qorai_shields::features::kCosmeticFilteringCustomScriptlets));

  html_source->AddBoolean(
      "isAdBlockOnlyModeSupportedAndFeatureEnabled",
      base::FeatureList::IsEnabled(qorai_shields::features::kAdblockOnlyMode) &&
          qorai_shields::IsAdblockOnlyModeSupportedForLocale(
              g_browser_process->GetApplicationLocale()));

  // Always disable upstream's side panel align option.
  // We add our customized option at preferred position.
  html_source->AddBoolean("showSidePanelOptions", false);

  // We're reinstating these cookie-related settings that were deleted upstream
  html_source->AddString(
      "cacheStorageLastModified",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_LAST_MODIFIED_LABEL));
  html_source->AddString("cacheStorageOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString(
      "cacheStorageSize",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_SIZE_ON_DISK_LABEL));
  html_source->AddString(
      "cookieAccessibleToScript",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_COOKIE_ACCESSIBLE_TO_SCRIPT_LABEL));
  html_source->AddString(
      "cookieCacheStorage",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_CACHE_STORAGE));
  html_source->AddString(
      "cookieContent",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_CONTENT_LABEL));
  html_source->AddString(
      "cookieCreated",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_CREATED_LABEL));
  html_source->AddString(
      "cookieDatabaseStorage",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_DATABASE_STORAGE));
  html_source->AddString(
      "cookieDomain",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_DOMAIN_LABEL));
  html_source->AddString(
      "cookieExpires",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_EXPIRES_LABEL));
  html_source->AddString(
      "cookieFileSystem",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_FILE_SYSTEM));
  html_source->AddString("cookieFlashLso", l10n_util::GetStringUTF16(
                                               IDS_SETTINGS_COOKIES_FLASH_LSO));
  html_source->AddString(
      "cookieLocalStorage",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_LOCAL_STORAGE));
  html_source->AddString(
      "cookieName",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_NAME_LABEL));
  html_source->AddString(
      "cookiePath",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_PATH_LABEL));
  html_source->AddString(
      "cookieSendFor",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_COOKIE_SENDFOR_LABEL));
  html_source->AddString(
      "cookieServiceWorker",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_SERVICE_WORKER));
  html_source->AddString(
      "cookieSharedWorker",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_SHARED_WORKER));
  html_source->AddString(
      "cookieQuotaStorage",
      l10n_util::GetStringUTF16(IDS_SETTINGS_COOKIES_QUOTA_STORAGE));
  html_source->AddString("databaseOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString("fileSystemOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString(
      "fileSystemPersistentUsage",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_FILE_SYSTEM_PERSISTENT_USAGE_LABEL));
  html_source->AddString(
      "fileSystemTemporaryUsage",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_FILE_SYSTEM_TEMPORARY_USAGE_LABEL));
  html_source->AddString(
      "indexedDbSize",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_SIZE_ON_DISK_LABEL));
  html_source->AddString(
      "indexedDbLastModified",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_LAST_MODIFIED_LABEL));
  html_source->AddString("indexedDbOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString(
      "localStorageLastModified",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_LAST_MODIFIED_LABEL));
  html_source->AddString("localStorageOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString(
      "localStorageSize",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_SIZE_ON_DISK_LABEL));
  html_source->AddString("quotaOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString(
      "quotaSize", l10n_util::GetStringUTF16(
                       IDS_SETTINGS_COOKIES_LOCAL_STORAGE_SIZE_ON_DISK_LABEL));
  html_source->AddString("serviceWorkerOrigin",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_COOKIES_LOCAL_STORAGE_ORIGIN_LABEL));
  html_source->AddString(
      "serviceWorkerSize",
      l10n_util::GetStringUTF16(
          IDS_SETTINGS_COOKIES_LOCAL_STORAGE_SIZE_ON_DISK_LABEL));
  html_source->AddLocalizedStrings(webui::kQoraiSettingsStrings);

  // We add strings regardless of the FeatureFlag state to prevent crash

  // At this moment, the feature name is DNT.
  html_source->AddString("playlist", "Playlist");

  html_source->AddString(
      "qoraiPlaylistEnablePlaylistLabel",
      l10n_util::GetStringUTF16(IDS_SETTINGS_PLAYLIST_ENABLE_PLAYLIST_LABEL));
  html_source->AddString(
      "qoraiPlaylistCacheByDefaultLabel",
      l10n_util::GetStringUTF16(IDS_SETTINGS_PLAYLIST_CACHE_BY_DEFAULT_LABEL));
  html_source->AddString("qoraiPlaylistCacheByDefaultSubLabel",
                         l10n_util::GetStringUTF16(
                             IDS_SETTINGS_PLAYLIST_CACHE_BY_DEFAULT_SUB_LABEL));
}

}  // namespace settings
