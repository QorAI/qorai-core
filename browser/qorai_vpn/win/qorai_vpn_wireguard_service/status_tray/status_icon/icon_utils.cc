/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/status_tray/status_icon/icon_utils.h"

#include <memory>

#include "base/check.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_wireguard_service/status_tray/status_icon/constants.h"
#include "ui/gfx/icon_util.h"
#include "ui/gfx/image/image_family.h"
#include "ui/gfx/image/image_skia.h"

namespace qorai_vpn {

namespace {

std::unique_ptr<gfx::ImageFamily> GetAppIconImageFamily(int icon_id) {
  // Get the icon from the current module.
  HMODULE module = GetModuleHandle(nullptr);
  DCHECK(module);
  return IconUtil::CreateImageFamilyFromIconResource(module, icon_id);
}
}  // namespace

gfx::ImageSkia GetIconFromResources(int icon_id, const gfx::Size& size) {
  std::unique_ptr<gfx::ImageFamily> family = GetAppIconImageFamily(icon_id);
  DCHECK(family);
  if (!family) {
    return gfx::ImageSkia();
  }

  return family->CreateExact(size).AsImageSkia();
}

HWND GetQorAIVpnStatusTrayIconHWND() {
  return FindWindowEx(nullptr, nullptr, kStatusTrayWindowClass,
                      kStatusTrayWindowName);
}

bool IsQorAIVpnTrayIconRunning() {
  return GetQorAIVpnStatusTrayIconHWND() != NULL;
}

}  // namespace qorai_vpn
