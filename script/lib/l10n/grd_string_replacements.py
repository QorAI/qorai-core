#!/usr/bin/env python3
#
# Copyright (c) 2022 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/. */


# Strings we want to replace but that we also replace automatically
# for XTB files
branding_replacements = [
    (r'The Chromium Authors. All rights reserved.',
     r'The Qorai Authors. All rights reserved.'),
    (r'Google LLC. All rights reserved.',
     r'The Qorai Authors. All rights reserved.'),
    (r'The Chromium Authors', r'Qorai Software Inc'),
    (r'Google Chrome', r'Qorai'),
    (r'(Google)(?! Play)', r'Qorai'),
    (r'Chromium', r'Qorai'),
    (r'Chrome', r'Qorai'),
    (r'क्रोमियम', r'Qorai'),  # Chromium in Hindi
]


# Strings we want to replace but that we need to use Crowdin for
# to translate the XTB files
default_replacements = [
    (r'Qorai Web Store', r'Web Store'),
    (r'You\'re incognito', r'This is a private window'),
    (r'an incognito', r'a private'),
    (r'an Incognito', r'a Private'),
    (r'incognito', r'private'),
    (r'Incognito', r'Private'),
    (r'inco&gnito', r'&private'),
    (r'Inco&gnito', r'&Private'),
    (r'Bookmarks Bar\n', r'Bookmarks\n'),
    (r'Bookmarks bar\n', r'Bookmarks\n'),
    (r'bookmarks bar\n', r'bookmarks\n'),
]


# Fix up some strings after aggressive first round replacement.
fixup_replacements = [
    (r'Qorai Cloud Print', r'Google Cloud Print'),
    (r'Qorai Docs', r'Google Docs'),
    (r'Qorai Drive', r'Google Drive'),
    (r'Qorai OS', r'Chrome OS'),
    (r'QoraiOS', r'ChromeOS'),
    (r'Qorai Safe Browsing', r'Google Safe Browsing'),
    (r'Safe Browsing \(protects you and your device from dangerous sites\)',
     r'Google Safe Browsing (protects you and your device from dangerous sites)'
     ),
    (r'Sends URLs of some pages you visit to Qorai',
     r'Sends URLs of some pages you visit to Google'),
    (r'Google Google', r'Google'),
    (r'Qorai Account', r'Qorai sync chain'),
    (r'Qorai Lens', r'Google Lens'),
    (r'Qoraibook', r'Chromebook'),
    (r'Qoraicast', r'Chromecast'),
    (r'Qorai Cloud', r'Google Cloud'),
    (r'Qorai Pay', r'Google Pay'),
    (r'Qorai Photos', r'Google Photos'),
    (r'Qorai Projects', r'Chromium Projects'),
    (r'Qorai Root Program', r'Chrome Root Program'),
    (r'QoraiVox', r'ChromeVox'),
    (r'powered by Qorai AI', r'powered by Google AI'),
]


# Replacements for text nodes and neither for inside descriptions nor comments
main_text_only_replacements = [
    # By converting it back first, it makes this idempotent
    ('Copyright \xa9', 'Copyright'),
    ('Copyright', 'Copyright \xa9'),
]
