/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_CRX_FILE_CRX_CREATOR_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_CRX_FILE_CRX_CREATOR_H_

#include <components/crx_file/crx_creator.h>  // IWYU pragma: export

#include "base/containers/span.h"

namespace crx_file {

CreatorResult CreateWithMultipleKeys(
    const base::FilePath& output_path,
    const base::FilePath& zip_path,
    base::span<const crypto::keypair::PrivateKey> keys);
}  // namespace crx_file

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_CRX_FILE_CRX_CREATOR_H_
