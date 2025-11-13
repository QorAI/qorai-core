// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/ui/webui/qorai_wallet/nft_ui.h"

#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/nft_display/resources/grit/nft_display_generated_map.h"
#include "qorai/ios/browser/ui/webui/untrusted_sanitized_image_source.h"
#include "qorai/ios/web/webui/qorai_web_ui_ios_data_source.h"
#include "qorai/ios/web/webui/qorai_webui_utils.h"
#include "components/grit/qorai_components_resources.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/web_state.h"
#include "ios/web/public/webui/url_data_source_ios.h"
#include "ios/web/public/webui/web_ui_ios.h"
#include "ios/web/public/webui/web_ui_ios_data_source.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/webui/web_ui_util.h"
#include "ui/webui/resources/grit/webui_resources.h"

namespace nft {

UntrustedNftUI::UntrustedNftUI(web::WebUIIOS* web_ui, const GURL& url)
    : web::WebUIIOSController(web_ui, url.host()) {
  QoraiWebUIIOSDataSource* untrusted_source =
      qorai::CreateAndAddWebUIDataSource(web_ui, url.host(),
                                         kNftDisplayGenerated,
                                         IDR_QORAI_WALLET_NFT_DISPLAY_HTML);

  untrusted_source->AddLocalizedStrings(qorai_wallet::kLocalizedStrings);

  untrusted_source->AddFrameAncestor(GURL(kQoraiUIWalletPageURL));

  untrusted_source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ScriptSrc,
      std::string("script-src 'self' chrome-untrusted://resources;"));
  untrusted_source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::StyleSrc,
      std::string("style-src 'self' 'unsafe-inline';"));
  untrusted_source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::FontSrc,
      std::string("font-src 'self' data:;"));
  untrusted_source->AddResourcePath("load_time_data_deprecated.js",
                                    IDR_WEBUI_JS_LOAD_TIME_DATA_DEPRECATED_JS);
  untrusted_source->UseStringsJs();
  untrusted_source->AddString("qoraiWalletNftBridgeUrl", kUntrustedNftURL);
  untrusted_source->AddString("qoraiWalletTrezorBridgeUrl",
                              kUntrustedTrezorURL);
  untrusted_source->AddString("qoraiWalletLedgerBridgeUrl",
                              kUntrustedLedgerURL);
  untrusted_source->AddString("qoraiWalletMarketUiBridgeUrl",
                              kUntrustedMarketURL);
  untrusted_source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ImgSrc,
      std::string("img-src 'self' chrome-untrusted://resources "
                  "chrome-untrusted://image;"));

  auto* profile = ProfileIOS::FromWebUIIOS(web_ui);
  web::URLDataSourceIOS::Add(profile,
                             new UntrustedSanitizedImageSource(profile));
}

UntrustedNftUI::~UntrustedNftUI() = default;

}  // namespace nft
