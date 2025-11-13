/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_QORAI_SPEECH_TO_TEXT_NETWORK_DELEGATE_HELPER_H_
#define QORAI_BROWSER_NET_QORAI_SPEECH_TO_TEXT_NETWORK_DELEGATE_HELPER_H_

namespace network {
struct ResourceRequest;
}

namespace stt {

void OnBeforeURLRequest_SpoofSpeechToText(network::ResourceRequest* request);

}

#endif  // QORAI_BROWSER_NET_QORAI_SPEECH_TO_TEXT_NETWORK_DELEGATE_HELPER_H_
