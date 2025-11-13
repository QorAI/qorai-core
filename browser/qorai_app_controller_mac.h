/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_APP_CONTROLLER_MAC_H_
#define QORAI_BROWSER_QORAI_APP_CONTROLLER_MAC_H_

#import <Cocoa/Cocoa.h>

#import "chrome/browser/app_controller_mac.h"

// * Manages logic to switch hotkey between copy and copy clean link item.
// * Add "New Private Window with Tor" to the dock menu.
@interface QorAIAppController : AppController
@end

#endif  // QORAI_BROWSER_QORAI_APP_CONTROLLER_MAC_H_
