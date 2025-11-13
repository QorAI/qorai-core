/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CRYPTO_SIGNATURE_VERIFIER_H_
#define QORAI_CHROMIUM_SRC_CRYPTO_SIGNATURE_VERIFIER_H_

#define ECDSA_SHA256 ECDSA_SHA256, ECDSA_SHA384

#include <crypto/signature_verifier.h>  // IWYU pragma: export

#undef ECDSA_SHA256

#endif  // QORAI_CHROMIUM_SRC_CRYPTO_SIGNATURE_VERIFIER_H_
