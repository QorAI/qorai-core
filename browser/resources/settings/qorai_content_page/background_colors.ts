// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { hexColorToSkColor } from '//resources/js/color_utils.js'
import { SkColor } from '//resources/mojo/skia/public/mojom/skcolor.mojom-webui.js'

const allProperties = getComputedStyle(document.documentElement)

function getSkColorFromQoraVariable(variableName: string): SkColor {
  // Convert the variable name to lower case to match the hexColorToSkColor
  // requirement.
  return hexColorToSkColor(
    allProperties.getPropertyValue(variableName).trim().toLowerCase(),
  )
}

export default [
  getSkColorFromQoraVariable('--qora-color-red-40'),
  getSkColorFromQoraVariable('--qora-color-orange-40'),
  getSkColorFromQoraVariable('--qora-color-yellow-40'),
  getSkColorFromQoraVariable('--qora-color-green-40'),
  getSkColorFromQoraVariable('--qora-color-teal-40'),
  getSkColorFromQoraVariable('--qora-color-blue-40'),
  getSkColorFromQoraVariable('--qora-color-purple-40'),
  getSkColorFromQoraVariable('--qora-color-pink-40'),
]
