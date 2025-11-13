// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// This file is included into //ios/chrome/browser/flags/about_flags.mm

#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_component_updater/browser/features.h"
#include "qorai/components/qorai_rewards/core/features.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_sync/features.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/de_amp/common/features.h"
#include "qorai/components/debounce/core/common/features.h"
#include "qorai/components/skus/common/features.h"
#include "qorai/ios/browser/api/translate/features.h"
#include "qorai/ios/browser/qorai_wallet/features.h"
#include "qorai/ios/browser/ui/tab_tray/features.h"
#include "qorai/ios/browser/ui/web_view/features.h"
#include "qorai/ios/browser/ui/webui/ai_chat/features.h"
#include "build/build_config.h"
#include "components/webui/flags/feature_entry_macros.h"
#include "components/webui/flags/flags_state.h"
#include "net/base/features.h"

#define EXPAND_FEATURE_ENTRIES(...) __VA_ARGS__,

#define QORAI_SKU_SDK_FEATURE_ENTRIES                   \
  EXPAND_FEATURE_ENTRIES({                              \
      "skus-sdk",                                       \
      "Enable experimental SKU SDK",                    \
      "Experimental SKU SDK support",                   \
      flags_ui::kOsIos,                                 \
      FEATURE_VALUE_TYPE(skus::features::kSkusFeature), \
  })

#define QORAI_NATIVE_WALLET_FEATURE_ENTRIES                                   \
  EXPAND_FEATURE_ENTRIES(                                                     \
      {                                                                       \
          "qorai-wallet-zcash",                                               \
          "Enable QoraiWallet ZCash support",                                 \
          "Zcash support for native Qorai Wallet",                            \
          flags_ui::kOsIos,                                                   \
          FEATURE_VALUE_TYPE(                                                 \
              qorai_wallet::features::kQoraiWalletZCashFeature),              \
      },                                                                      \
      {                                                                       \
          "qorai-wallet-bitcoin",                                             \
          "Enable Qorai Wallet Bitcoin support",                              \
          "Bitcoin support for native Qorai Wallet",                          \
          flags_ui::kOsIos,                                                   \
          FEATURE_VALUE_TYPE(                                                 \
              qorai_wallet::features::kQoraiWalletBitcoinFeature),            \
      },                                                                      \
      {                                                                       \
          "qorai-wallet-enable-ankr-balances",                                \
          "Enable Ankr balances",                                             \
          "Enable usage of Ankr Advanced API for fetching balances in Qorai " \
          "Wallet",                                                           \
          flags_ui::kOsIos,                                                   \
          FEATURE_VALUE_TYPE(                                                 \
              qorai_wallet::features::kQoraiWalletAnkrBalancesFeature),       \
      },                                                                      \
      {                                                                       \
          "qorai-wallet-enable-transaction-simulations",                      \
          "Enable transaction simulations",                                   \
          "Enable usage of Blowfish API for running transaction simulations " \
          "in Qorai Wallet",                                                  \
          flags_ui::kOsIos,                                                   \
          FEATURE_VALUE_TYPE(qorai_wallet::features::                         \
                                 kQoraiWalletTransactionSimulationsFeature),  \
      })

#define QORAI_SHIELDS_FEATURE_ENTRIES                                          \
  EXPAND_FEATURE_ENTRIES(                                                      \
      {                                                                        \
          "qorai-shred",                                                       \
          "Enable Qorai 'Shred' Feature",                                      \
          "Enable the Qorai 'Shred' feature which will allow a user to "       \
          "easily delete all site data on demand or automatically when "       \
          "closing a site or terminating the application.",                    \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_shields::features::kQoraiShredFeature),     \
      },                                                                       \
      {                                                                        \
          "qorai-shred-cache-data",                                            \
          "Shred Clears All Cache Data",                                       \
          "Shred feature will also remove all cache data, in addition to the " \
          "data associated with the site being shred.",                        \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_shields::features::kQoraiShredCacheData),   \
      },                                                                       \
      {                                                                        \
          "qorai-shields-content-settings",                                    \
          "Qorai Shields use Content Settings",                                \
          "Qorai Shields will use content settings for persisting Shields "    \
          "preferences",                                                       \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(                                                  \
              qorai_shields::features::kQoraiShieldsContentSettingsIOS),       \
      },                                                                       \
      {                                                                        \
          "https-by-default",                                                  \
          "Use HTTPS by Default",                                              \
          "Attempt to connect to all websites using HTTPS before falling "     \
          "back to HTTP.",                                                     \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(net::features::kQoraiHttpsByDefault),             \
      },                                                                       \
      {                                                                        \
          "block-all-cookies-toggle",                                          \
          "If the feature flag is on, we show the Block all Cookies toggle",   \
          "If the feature flag is on, we show the Block all Cookies toggle",   \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_shields::features::kBlockAllCookiesToggle), \
      },                                                                       \
      {                                                                        \
          "ios-debug-adblock",                                                 \
          "Enable Debug Adblock views",                                        \
          "Enable debug view for adblock features in Shields panel",           \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_shields::features::kQoraiIOSDebugAdblock),  \
      },                                                                       \
      {                                                                        \
          "ios-farble-plugins",                                                \
          "Enable Farbling Plugins",                                           \
          "Enable Farbling plugins when enabled globally / per-domain",        \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(                                                  \
              qorai_shields::features::kQoraiIOSEnableFarblingPlugins),        \
      },                                                                       \
      {                                                                        \
          "ios-webkit-advanced-privacy-protections",                           \
          "Enable WebKit's Advanced Privacy Protections",                      \
          "Enable's WebKit's Advanced Privacy Protections on all sites",       \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(                                                  \
              qorai_shields::features::kWebKitAdvancedPrivacyProtections),     \
      })

#define QORAI_AI_CHAT_FEATURE_ENTRIES                                 \
  EXPAND_FEATURE_ENTRIES(                                             \
      {                                                               \
          "qorai-ai-chat",                                            \
          "Qorai AI Chat",                                            \
          "Summarize articles and engage in conversation with AI",    \
          flags_ui::kOsIos,                                           \
          FEATURE_VALUE_TYPE(ai_chat::features::kAIChat),             \
      },                                                              \
      {                                                               \
          "qorai-ai-chat-history",                                    \
          "Qorai AI Chat History",                                    \
          "Enables AI Chat History persistence and management",       \
          flags_ui::kOsIos,                                           \
          FEATURE_VALUE_TYPE(ai_chat::features::kAIChatHistory),      \
      },                                                              \
      {                                                               \
          "qorai-ai-chat-webui",                                      \
          "Qorai AI Chat WebUI",                                      \
          "Enables the use of Qora via WebUI",                         \
          flags_ui::kOsIos,                                           \
          FEATURE_VALUE_TYPE(ai_chat::features::kAIChatWebUIEnabled), \
      })

#define QORAI_WALLET_FEATURE_ENTRIES                                    \
  EXPAND_FEATURE_ENTRIES({                                              \
      "qorai-wallet-webui-ios",                                         \
      "Enable WebUI for Qorai Wallet iOS",                              \
      "Enables WebUI for Qorai Wallet",                                 \
      flags_ui::kOsIos,                                                 \
      FEATURE_VALUE_TYPE(qorai_wallet::features::kQoraiWalletWebUIIOS), \
  })

// Keep the last item empty.
#define LAST_QORAI_FEATURE_ENTRIES_ITEM

#define QORAI_ABOUT_FLAGS_FEATURE_ENTRIES                                      \
  EXPAND_FEATURE_ENTRIES(                                                      \
      {                                                                        \
          "use-dev-updater-url",                                               \
          "Use dev updater url",                                               \
          "Use the dev url for the component updater. This is for internal "   \
          "testing only.",                                                     \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_component_updater::kUseDevUpdaterUrl),      \
      },                                                                       \
      {                                                                        \
          "qorai-use-modern-tab-tray",                                         \
          "Use modern tab tray UI",                                            \
          "Replace the tab tray UI with a modern replacement",                 \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai::features::kModernTabTrayEnabled),          \
      },                                                                       \
      {                                                                        \
          "qorai-sync-default-passwords",                                      \
          "Enable password syncing by default",                                \
          "Turn on password syncing when Sync is enabled.",                    \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(                                                  \
              qorai_sync::features::kQoraiSyncDefaultPasswords),               \
      },                                                                       \
      {                                                                        \
          "qorai-translate-enabled",                                           \
          "Use Qorai Translate",                                               \
          "Enables page translation",                                          \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai::features::kQoraiTranslateEnabled),         \
      },                                                                       \
      {                                                                        \
          "qorai-translate-apple-enabled",                                     \
          "Use Apple Offline Translate",                                       \
          "Enables page translation using Apple APIs",                         \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai::features::kQoraiAppleTranslateEnabled),    \
      },                                                                       \
      {                                                                        \
          "use-qorai-user-agent",                                              \
          "Use Qorai user agent",                                              \
          "Includes Qorai version information in the user agent",              \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_user_agent::features::kUseQoraiUserAgent),  \
      },                                                                       \
      {                                                                        \
          "qorai-use-chromium-web-embedder",                                   \
          "Use Chromium Web Embedder",                                         \
          "Replace WKWebView usages with Chromium web views",                  \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai::features::kUseChromiumWebViews),           \
      },                                                                       \
      {                                                                        \
          "qorai-debounce",                                                    \
          "Enable debouncing",                                                 \
          "Enable support for skipping top-level redirect tracking URLs",      \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(debounce::features::kQoraiDebounce),              \
      },                                                                       \
      {                                                                        \
          "qorai-de-amp",                                                      \
          "Enable De-AMP",                                                     \
          "Enable De-AMPing feature",                                          \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(de_amp::features::kQoraiDeAMP),                   \
      },                                                                       \
      {                                                                        \
          "qorai-rewards-verbose-logging",                                     \
          "Enable Qorai Rewards verbose logging",                              \
          "Enables detailed logging of Qorai Rewards system events to a log "  \
          "file stored on your device. Please note that this log file could "  \
          "include information such as browsing history and credentials such " \
          "as passwords and access tokens depending on your activity. Please " \
          "do not share it unless asked to by Qorai staff.",                   \
          flags_ui::kOsIos,                                                    \
          FEATURE_VALUE_TYPE(qorai_rewards::features::kVerboseLoggingFeature), \
      })                                                                       \
  QORAI_SHIELDS_FEATURE_ENTRIES                                                \
  QORAI_NATIVE_WALLET_FEATURE_ENTRIES                                          \
  QORAI_SKU_SDK_FEATURE_ENTRIES                                                \
  QORAI_AI_CHAT_FEATURE_ENTRIES                                                \
  QORAI_WALLET_FEATURE_ENTRIES                                                 \
  LAST_QORAI_FEATURE_ENTRIES_ITEM  // Keep it as the last item.
