/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_RENDERER_QORAI_WALLET_QORAI_WALLET_RENDER_FRAME_OBSERVER_P3A_UTIL_H_
#define QORAI_RENDERER_QORAI_WALLET_QORAI_WALLET_RENDER_FRAME_OBSERVER_P3A_UTIL_H_

#include "qorai/common/qorai_renderer_configuration.mojom.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "content/public/renderer/render_frame.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace v8 {
class Context;
template <class T>
class Local;
class Isolate;
}  // namespace v8

namespace qorai_wallet {

class QoraiWalletRenderFrameObserverP3AUtil {
 public:
  QoraiWalletRenderFrameObserverP3AUtil();
  ~QoraiWalletRenderFrameObserverP3AUtil();

  void ReportJSProviders(content::RenderFrame* render_frame,
                         const qorai::mojom::DynamicParams& dynamic_params);

 private:
  bool EnsureConnected(content::RenderFrame* render_frame);

  void ReportJSProvider(v8::Isolate* isolate,
                        v8::Local<v8::Context>& context,
                        mojom::CoinType coin_type,
                        const char* provider_object_key,
                        bool allow_provider_overwrite);

  mojo::Remote<qorai_wallet::mojom::QoraiWalletP3A> qorai_wallet_p3a_;
};

}  // namespace qorai_wallet

#endif  // QORAI_RENDERER_QORAI_WALLET_QORAI_WALLET_RENDER_FRAME_OBSERVER_P3A_UTIL_H_
