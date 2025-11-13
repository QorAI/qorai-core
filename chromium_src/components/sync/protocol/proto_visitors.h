/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_PROTOCOL_PROTO_VISITORS_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_PROTOCOL_PROTO_VISITORS_H_

#define QORAI_VISIT_DEVICE_INFO_SPECIFICS_QORAI_FIELDS \
VISIT(qorai_fields);

#define QORAI_VISIT_PROTO_FIELDS_QORAI_SPECIFIC_FIELD                  \
VISIT_PROTO_FIELDS(const sync_pb::QoraiSpecificFields& proto) {        \
  VISIT(is_self_delete_supported);                                     \
}

#include <components/sync/protocol/proto_visitors.h>  // IWYU pragma: export
#undef QORAI_VISIT_PROTO_FIELDS_QORAI_SPECIFIC_FIELD
#undef QORAI_VISIT_DEVICE_INFO_SPECIFICS_QORAI_FIELDS

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_PROTOCOL_PROTO_VISITORS_H_
