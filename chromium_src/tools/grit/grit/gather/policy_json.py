# Copyright (c) 2022 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import override_utils


@override_utils.override_method(PolicyJson)
def SetDefines(self, _orig_method, _defines):
    self._config = {
        'build': 'qorai',
        'app_name': 'Qorai',
        'frame_name': 'Qorai Frame',
        'os_name': 'Google Chrome OS'
    }
