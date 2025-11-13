/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_RENDERER_QORAI_WALLET_QORAI_WALLET_RENDER_FRAME_OBSERVER_H_
#define QORAI_RENDERER_QORAI_WALLET_QORAI_WALLET_RENDER_FRAME_OBSERVER_H_

#include <optional>

#include "qorai/common/qorai_renderer_configuration.mojom.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/renderer/js_cardano_provider.h"
#include "qorai/components/qorai_wallet/renderer/js_ethereum_provider.h"
#include "qorai/components/qorai_wallet/renderer/js_solana_provider.h"
#include "qorai/renderer/qorai_wallet/qorai_wallet_render_frame_observer_p3a_util.h"
#include "content/public/renderer/render_frame.h"
#include "content/public/renderer/render_frame_observer.h"
#include "third_party/blink/public/web/web_navigation_type.h"
#include "url/gurl.h"
#include "v8/include/v8.h"

namespace qorai_wallet {

class QoraiWalletRenderFrameObserver : public content::RenderFrameObserver {
 public:
  using GetDynamicParamsCallback =
      base::RepeatingCallback<const qorai::mojom::DynamicParams&()>;

  explicit QoraiWalletRenderFrameObserver(
      content::RenderFrame* render_frame,
      GetDynamicParamsCallback get_dynamic_params_callback);
  ~QoraiWalletRenderFrameObserver() override;

  // RenderFrameObserver implementation.
  void DidStartNavigation(
      const GURL& url,
      std::optional<blink::WebNavigationType> navigation_type) override;
  void DidClearWindowObject() override;

  void DidFinishLoad() override;

 private:
  // RenderFrameObserver implementation.
  void OnDestruct() override;

  bool IsPageValid();
  bool CanCreateProvider();

  GURL url_;
  GetDynamicParamsCallback get_dynamic_params_callback_;

  QoraiWalletRenderFrameObserverP3AUtil p3a_util_;
};

}  // namespace qorai_wallet

#endif  // QORAI_RENDERER_QORAI_WALLET_QORAI_WALLET_RENDER_FRAME_OBSERVER_H_
