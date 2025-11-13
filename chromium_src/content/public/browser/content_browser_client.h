/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_CONTENT_BROWSER_CLIENT_H_
#define QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_CONTENT_BROWSER_CLIENT_H_

#include "qorai/components/qorai_shields/core/common/shields_settings.mojom.h"
#include "third_party/blink/public/mojom/loader/referrer.mojom.h"

// Qorai-specific: allows the embedder to modify the referrer string
// according to user preferences.
// Allow the embedder to determine the user-agent according to user preferences.
// Allow the embedder to control if access to privileged functions that could
// be used by fingerprinting by a shared worker is allowed.
// Allow the embedder to clean up the url before copying into the clipboard.
#define SetBrowserStartupIsCompleteForTesting                                \
  Unused() {}                                                                \
  virtual void MaybeHideReferrer(                                            \
      BrowserContext* browser_context, const GURL& request_url,              \
      const GURL& document_url, blink::mojom::ReferrerPtr* referrer) {}      \
  virtual std::string GetEffectiveUserAgent(BrowserContext* browser_context, \
                                            const GURL& url);                \
  virtual std::optional<base::UnguessableToken> GetEphemeralStorageToken(    \
      RenderFrameHost* render_frame_host, const url::Origin& origin);        \
  virtual bool CanThirdPartyStoragePartitioningBeDisabled(                   \
      BrowserContext* browser_context, const url::Origin& origin);           \
  virtual bool AllowWorkerFingerprinting(const GURL& url,                    \
                                         BrowserContext* browser_context);   \
  virtual qorai_shields::mojom::ShieldsSettingsPtr                           \
  WorkerGetQoraiShieldSettings(const GURL& url,                              \
                               BrowserContext* browser_context);             \
  virtual std::optional<GURL> SanitizeURL(content::RenderFrameHost*,         \
                                          const GURL&);                      \
  virtual bool IsWindowsRecallDisabled();                                    \
  virtual void SetBrowserStartupIsCompleteForTesting

#include <content/public/browser/content_browser_client.h>  // IWYU pragma: export

#undef SetBrowserStartupIsCompleteForTesting

#endif  // QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_CONTENT_BROWSER_CLIENT_H_
