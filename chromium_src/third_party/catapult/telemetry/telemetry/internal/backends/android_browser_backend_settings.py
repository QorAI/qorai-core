# Copyright (c) 2023 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# you can obtain one at https://mozilla.org/MPL/2.0/.
"""A inline part of android_browser_backend_settings.py"""

ANDROID_QORAI = GenericChromeBackendSettings(browser_type='android-qorai',
                                             package='com.qorai.browser')

ANDROID_QORAI_DEFAULT = GenericChromeBackendSettings(
    browser_type='android-qorai-default', package='com.qorai.browser_default')

ANDROID_QORAI_BETA = GenericChromeBackendSettings(
    browser_type='android-qorai-beta', package='com.qorai.browser_beta')

ANDROID_QORAI_DEV = GenericChromeBackendSettings(
    browser_type='android-qorai-dev', package='com.qorai.browser_dev')

ANDROID_QORAI_NIGHTLY = GenericChromeBackendSettings(
    browser_type='android-qorai-nightly', package='com.qorai.browser_nightly')

QORAI_ANDROID_BACKEND_SETTINGS = (ANDROID_QORAI_DEFAULT, ANDROID_QORAI,
                                  ANDROID_QORAI_BETA, ANDROID_QORAI_DEV,
                                  ANDROID_QORAI_NIGHTLY)

# Add qorai items to chromium ANDROID_BACKEND_SETTINGS:
ANDROID_BACKEND_SETTINGS = QORAI_ANDROID_BACKEND_SETTINGS + ANDROID_BACKEND_SETTINGS
