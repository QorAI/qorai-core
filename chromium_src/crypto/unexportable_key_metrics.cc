/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#define QORAI_ALL_ALGORITHMS \
  SignatureVerifier::SignatureAlgorithm::ECDSA_SHA256,
#define QORAI_MEASURE_VIRTUAL_TMP_OPERATIONS \
  case SignatureVerifier::SignatureAlgorithm::ECDSA_SHA384:
#define QORAI_MEASURE_TMP_OPERATIONS_INTERNAL \
  case SignatureVerifier::SignatureAlgorithm::ECDSA_SHA384:
#define QORAI_UNEXPORTED_KEY_METRICS_ALGORITHM_TO_STRING \
  case SignatureVerifier::SignatureAlgorithm::ECDSA_SHA384:

#include <crypto/unexportable_key_metrics.cc>

#undef QORAI_ALL_ALGORITHMS
#undef QORAI_MEASURE_VIRTUAL_TMP_OPERATIONS
#undef QORAI_MEASURE_TMP_OPERATIONS_INTERNAL
#undef QORAI_UNEXPORTED_KEY_METRICS_ALGORITHM_TO_STRING
