/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_wallet/nft/nft_ui.h"

#include <string>

#include "qorai/browser/ui/webui/untrusted_sanitized_image_source.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/nft_display/resources/grit/nft_display_generated_map.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/grit/browser_resources.h"
#include "chrome/grit/generated_resources.h"
#include "components/grit/qorai_components_resources.h"
#include "content/public/browser/url_data_source.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/webui/resources/grit/webui_resources.h"
#include "ui/webui/webui_util.h"

namespace nft {

UntrustedNftUI::UntrustedNftUI(content::WebUI* web_ui)
    : ui::UntrustedWebUIController(web_ui) {
  auto* untrusted_source = content::WebUIDataSource::CreateAndAdd(
      web_ui->GetWebContents()->GetBrowserContext(), kUntrustedNftURL);

  for (const auto& str : qorai_wallet::kLocalizedStrings) {
    std::u16string l10n_str = l10n_util::GetStringUTF16(str.id);
    untrusted_source->AddString(str.name, l10n_str);
  }

  untrusted_source->SetDefaultResource(IDR_QORAI_WALLET_NFT_DISPLAY_HTML);
  untrusted_source->AddResourcePaths(kNftDisplayGenerated);
  untrusted_source->AddFrameAncestor(GURL(kQoraiUIWalletPageURL));
  untrusted_source->AddFrameAncestor(GURL(kQoraiUIWalletPanelURL));
  webui::SetupWebUIDataSource(untrusted_source, kNftDisplayGenerated,
                              IDR_QORAI_WALLET_NFT_DISPLAY_HTML);
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

  Profile* profile = Profile::FromWebUI(web_ui);
  content::URLDataSource::Add(
      profile, std::make_unique<UntrustedSanitizedImageSource>(profile));
}

UntrustedNftUI::~UntrustedNftUI() = default;

std::unique_ptr<content::WebUIController>
UntrustedNftUIConfig::CreateWebUIController(content::WebUI* web_ui,
                                            const GURL& url) {
  return std::make_unique<UntrustedNftUI>(web_ui);
}

UntrustedNftUIConfig::UntrustedNftUIConfig()
    : WebUIConfig(content::kChromeUIUntrustedScheme, kUntrustedNftHost) {}

}  // namespace nft
