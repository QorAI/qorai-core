/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_PIPELINE_LINEAR_PIPELINE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_PIPELINE_LINEAR_PIPELINE_UTIL_H_

#include <stddef.h>
#include <stdint.h>

#include <optional>

namespace qorai_ads::ml::pipeline {

struct PipelineInfo;

std::optional<PipelineInfo> LoadLinearPipeline(const uint8_t* data,
                                               size_t length);

}  // namespace qorai_ads::ml::pipeline

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ML_PIPELINE_LINEAR_PIPELINE_UTIL_H_
