# Copyright (c) 2023 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import json
import os
import shlex
import shutil

import qorai_chromium_utils
import override_utils

VERBOSE = False  # Set to True to print verbose messages.


# Loads the qora overrides from qora_overrides.json.
def LoadQoraOverrides():
    qora_overrides_config_path = qorai_chromium_utils.wspath(
        '//qorai/components/vector_icons/qora_overrides.json')
    qora_override_format = '//qorai/node_modules/@qorai/qora/icons-skia/{}.icon'

    with open(qora_overrides_config_path, 'r') as f:
        qora_overrides_config = json.load(f)

    qora_overrides = {}
    for icon, qora_override in qora_overrides_config.items():
        if not icon.startswith("//"):
            raise ValueError(f'Invalid icon path: {icon}, must start with //')
        qora_override = qorai_chromium_utils.wspath(
            qora_override_format.format(qora_override))
        if not os.path.exists(qora_override):
            raise FileNotFoundError(f'Qora override not found: {qora_override}')
        qora_overrides[icon] = os.path.relpath(qora_override)

    return qora_overrides


# Rewrites the file list with overridden icons.
def RewriteFileListWithOverrides(file_list):
    with open(file_list, "r") as f:
        file_list_contents = f.read()
    icon_list = shlex.split(file_list_contents)

    qora_overrides = LoadQoraOverrides()

    rewritten_icon_list = []
    for icon_path in icon_list:
        icon_ws_path = qorai_chromium_utils.to_wspath(icon_path)
        chromium_src_override = qorai_chromium_utils.get_chromium_src_override(
            icon_path)

        # Qora override may have a different name than the original icon.
        # Copy the override to gen/qorai/vector_icons_overrides with the
        # original name.
        qora_override = qora_overrides.get(icon_ws_path)
        if qora_override:
            if os.path.exists(chromium_src_override):
                raise RuntimeError(
                    f'Qora override and chromium_src override both exist for '
                    f'{icon_path}')

            gen_file = f'gen/qorai/vector_icons_overrides/{icon_ws_path[2:]}'
            os.makedirs(os.path.dirname(gen_file), exist_ok=True)
            shutil.copyfile(qora_override, gen_file)
            rewritten_icon_list.append(gen_file)
            if VERBOSE:
                print(
                    f'Using qora override: {qora_override} copied to {gen_file}')
            continue

        # If the icon is not in qora overrides, check if it's in chromium_src
        # overrides.
        if os.path.exists(chromium_src_override):
            chromium_src_override = os.path.relpath(chromium_src_override)
            rewritten_icon_list.append(chromium_src_override)
            if VERBOSE:
                print(f'Using chromium_src override: {chromium_src_override}')
            continue

        # Otherwise use the original icon.
        rewritten_icon_list.append(icon_path)

    # Write the rewritten file list to the original file list.
    with open(file_list, "w") as f:
        f.write(shlex.join(rewritten_icon_list))


@override_utils.override_function(globals())
def AggregateVectorIcons(orig_func, working_directory, file_list, output_cc,
                         output_h, output_test_h):
    RewriteFileListWithOverrides(file_list)
    return orig_func(working_directory, file_list, output_cc, output_h,
                     output_test_h)
