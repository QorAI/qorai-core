/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_STORAGE_BROWSER_BLOB_BLOB_URL_STORE_IMPL_H_
#define QORAI_CHROMIUM_SRC_STORAGE_BROWSER_BLOB_BLOB_URL_STORE_IMPL_H_

namespace storage {
class BlobURLStoreImpl;
using BlobURLStoreImpl_QoraiImpl = BlobURLStoreImpl;
}  // namespace storage

#define BlobURLStoreImpl BlobURLStoreImpl_ChromiumImpl
#define BlobUrlIsValid               \
  NotUsed() const;                   \
  friend BlobURLStoreImpl_QoraiImpl; \
  bool BlobUrlIsValid

#include <storage/browser/blob/blob_url_store_impl.h>  // IWYU pragma: export

#include <optional>

#undef BlobUrlIsValid
#undef BlobURLStoreImpl

namespace storage {

class COMPONENT_EXPORT(STORAGE_BROWSER) BlobURLStoreImpl
    : public BlobURLStoreImpl_ChromiumImpl {
 public:
  using BlobURLStoreImpl_ChromiumImpl::BlobURLStoreImpl_ChromiumImpl;

  void ResolveAsURLLoaderFactory(
      const GURL& url,
      mojo::PendingReceiver<network::mojom::URLLoaderFactory> receiver)
      override;
  void ResolveAsBlobURLToken(
      const GURL& url,
      mojo::PendingReceiver<blink::mojom::BlobURLToken> token,
      bool is_top_level_navigation) override;

 private:
  bool IsBlobResolvable(const GURL& url) const;
};

}  // namespace storage

#endif  // QORAI_CHROMIUM_SRC_STORAGE_BROWSER_BLOB_BLOB_URL_STORE_IMPL_H_
