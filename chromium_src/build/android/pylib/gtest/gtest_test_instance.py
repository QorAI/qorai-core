# Copyright (c) 2025 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.
"""A inline part of gtest_test_instance.py"""

QORAI_BROWSER_TEST_SUITES = [
    'qorai_browser_tests',
]

# Add Qorai items to Chromium BROWSER_TEST_SUITES:
# pylint: disable=used-before-assignment
BROWSER_TEST_SUITES = BROWSER_TEST_SUITES + QORAI_BROWSER_TEST_SUITES
