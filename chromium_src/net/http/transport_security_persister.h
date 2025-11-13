/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_NET_HTTP_TRANSPORT_SECURITY_PERSISTER_H_
#define QORAI_CHROMIUM_SRC_NET_HTTP_TRANSPORT_SECURITY_PERSISTER_H_

#include "net/http/transport_security_state.h"

// Use upstream version of TransportSerurityState to reference
// TransportSecurityState::Delegate without build issues.
#define TransportSecurityState TransportSecurityState_ChromiumImpl
#include <net/http/transport_security_persister.h>  // IWYU pragma: export
#undef TransportSecurityState

#endif  // QORAI_CHROMIUM_SRC_NET_HTTP_TRANSPORT_SECURITY_PERSISTER_H_
