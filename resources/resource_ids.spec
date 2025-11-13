# Since recent changes upstream, Chromium is now using IDs up to ~59570 (see end
# of //out/<BUILD_TYPE>/gen/tools/gritsettings/default_resource_ids). We
# previously added our strings after all of the upstream strings, but we are now
# too close to the maximum id (65536) to continue doing that. Instead, we now
# overlap with a section of upstream strings related to ChromeOS/Ash which are
# unused by us. This range currently runs from [31600-40000), so it should
# provide a decent amount of room for future growth.
{
  "SRCDIR": "../..",
  "qorai/common/extensions/api/qorai_api_resources.grd": {
    "includes": [31600],
  },
  "qorai/components/resources/qorai_components_resources.grd": {
    "includes": [31620],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_adblock/qorai_adblock.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31640],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_new_tab/qorai_new_tab.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [31660],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_welcome/qorai_welcome.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [31680],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/browser/resources/settings/qorai_settings_resources.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [31700],
  },
  "qorai/app/qorai_generated_resources.grd": {
    "includes": [31720],
    "messages": [31740],
  },
  "qorai/app/theme/qorai_theme_resources.grd": {
    "structures": [31760],
  },
  "qorai/app/theme/qorai_unscaled_resources.grd": {
    "includes": [31780],
  },
  "qorai/components/qorai_rewards/resources/qorai_rewards_static_resources.grd": {
    "includes": [31800],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-rewards_internals/rewards_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31820],
  },
  "qorai/components/resources/qorai_components_strings.grd": {
    "messages": [31840],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_page/qorai_wallet_page.grd": {
    "META": {"sizes": {"includes": [200]}},
    "includes": [31860],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_panel/qorai_wallet_panel.grd": {
    "META": {"sizes": {"includes": [200]}},
    "includes": [31880],
  },
  "qorai/components/qorai_extension/extension/resources.grd": {
    "includes": [31900],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_extension/qorai_extension.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31920],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-webcompat_reporter/webcompat_reporter.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31940],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-cosmetic_filters/cosmetic_filters.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31960],
  },
  "qorai/components/tor/resources/tor_static_resources.grd": {
    "includes": [31980],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-tor_internals/tor_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32000],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_script/qorai_wallet_script.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32020],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_vpn_panel/qorai_vpn_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32040],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_shields_panel/qorai_shields_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32060],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-trezor_bridge/trezor_bridge.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32080],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-market_display/market_display.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [32100],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_private_new_tab/qorai_private_new_tab.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32120],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-playlist/playlist.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32140],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-ledger_bridge/ledger_bridge.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32160],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-nft_display/nft_display.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32180],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_speedreader_toolbar/qorai_speedreader_toolbar.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32200],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_adblock_internals/qorai_adblock_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32220],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_swap_page/qorai_wallet_swap_page.grd": {
    "META": {"sizes": {"includes": [100]}},
    "includes": [32240],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_send_page/qorai_wallet_send_page.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [32260],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_deposit_page/qorai_wallet_deposit_page.grd": {
    "META": {"sizes": {"includes": [100]}},
    "includes": [32280],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_wallet_fund_wallet_page/qorai_wallet_fund_wallet_page.grd": {
    "META": {"sizes": {"includes": [80]}},
    "includes": [32300],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-tip_panel/tip_panel.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [32320]
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-ai_chat_ui/ai_chat_ui.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32340],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-skus_internals/skus_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32360],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_news_internals/qorai_news_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32380],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-line_chart_display/line_chart_display.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32400]
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-ai_rewriter_ui/ai_rewriter_ui.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32420],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-rewards_page/rewards_page.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [32440],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-creator_detection/creator_detection.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32460],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-ads_internals/ads_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32480],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-custom_site_distiller_scripts/custom_site_distiller_scripts.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [32500],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/browser/resources/qorai_education/resources.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32520],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-new_tab_takeover/new_tab_takeover.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32540],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-qorai_new_tab_page_refresh/qorai_new_tab_page_refresh.grd": {
    "META": {"sizes": {"includes": [30]}},
    "includes": [32560],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-email_aliases/email_aliases.grd": {
    "META": {"sizes": {"includes": [40]}},
    "includes": [32580],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/components/qorai_account/resources/resources.grd": {
    "META": {"sizes": {"includes": [35]}},
    "includes": [32600],
  },
  "qorai/ios/web/test/test_resources.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32620],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/browser/resources/ai_chat_agent_new_tab_page/ai_chat_agent_new_tab_page_static_resources.grd": {
    "META": {"sizes": {"includes": [1]}},
    "includes": [32630],
  },
  "<(SHARED_INTERMEDIATE_DIR)/qorai/web-ui-ai_chat_agent_new_tab_page/ai_chat_agent_new_tab_page.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [32631],
  },
  # WARNING: The upstream ChromeOS/Ash strings currently run through 40000. We
  # must be careful not to exceed that maximum when adding new strings here.
  # Check out/<BUILD_TYPE>/gen/qorai/resources/qorai_resource_ids for how much
  # the ids got expanded after the build.
}
