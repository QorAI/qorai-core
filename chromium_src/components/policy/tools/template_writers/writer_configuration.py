# Copyright (c) 2022 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import override_utils

@override_utils.override_function(globals())
def GetConfigurationForBuild(original_function, defines):
    base = original_function(defines)
    merged = _merge_dicts(_QORAI_VALUES, base)

    # Remove Google.Policies namespace. Microsoft.Policies.Windows remains, as it is hardcoded in admx_writer.py.
    merged.pop('admx_using_namespaces', None)

    return merged


_QORAI_VALUES = {
    'build': 'qorai',
    'app_name': 'Qorai',
    'doc_url': 'https://support.qorai.app/hc/en-us/articles/360039248271-Group-Policy',
    'frame_name': 'Qorai Frame',
    'webview_name': 'Qorai WebView',
    'win_config': {
        'win': {
            'reg_mandatory_key_name': 'Software\\Policies\\QoraiSoftware\\Qorai',
            'reg_recommended_key_name': 'Software\\Policies\\QoraiSoftware\\Qorai\\Recommended',
            'mandatory_category_path': ['Cat_Qorai', 'qorai'],
            'recommended_category_path': ['Cat_Qorai', 'qorai_recommended'],
            'category_path_strings': {
                'Cat_Qorai': 'Qorai Software',
                'qorai': 'Qorai',
                'qorai_recommended': 'Qorai - {doc_recommended}'
            },
            'namespace': 'QoraiSoftware.Policies.Qorai',
        },
    },
    'admx_prefix': 'qorai',
    'linux_policy_path': '/etc/qorai/policies/',
    'bundle_id': 'com.qorai.ios.core',
}

def _merge_dicts(src, dst):
    result = dict(dst)
    for k, v in src.items():
        result[k] = _merge_dicts(v, dst.get(k, {})) if isinstance(v,
                                                                  dict) else v
    return result
