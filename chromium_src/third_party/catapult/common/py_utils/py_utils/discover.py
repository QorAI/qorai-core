# Copyright (c) 2023 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# you can obtain one at http://mozilla.org/MPL/2.0/.

# A override file to add qorai perf directories to src/tools/perf/

import os

import override_utils


def _GetSrcDir():
    return os.path.abspath(
        os.path.join(os.path.dirname(__file__), os.pardir, os.pardir, os.pardir,
                     os.pardir, os.pardir))


def _GetQoraiPerfDir(*dirs):
    return os.path.join('qorai', 'tools', 'perf', *dirs)


def _GetDiscoverClassesExtras(rel_start_dir, rel_top_level):
    if rel_top_level == os.path.join('tools', 'perf', 'page_sets'):
        if rel_start_dir == 'system_health':
            return 'qorai_system_health', _GetQoraiPerfDir('qorai_page_sets')
    if rel_top_level == os.path.join('tools', 'perf'):
        if rel_start_dir == 'benchmarks':
            return 'qorai_benchmarks', _GetQoraiPerfDir()
        if rel_start_dir == 'page_sets':
            return 'qorai_page_sets', _GetQoraiPerfDir()

    return None


@override_utils.override_function(globals())
def DiscoverClasses(original_function, start_dir, top_level_dir, *args,
                    **kwargs):
    original = original_function(start_dir, top_level_dir, *args, **kwargs)
    rel_top_level_dir = os.path.relpath(top_level_dir, _GetSrcDir())
    rel_start_dir = os.path.relpath(start_dir, top_level_dir)

    qorai_extras = _GetDiscoverClassesExtras(rel_start_dir, rel_top_level_dir)
    if qorai_extras is None:
        return original
    qorai_rel_start, qorai_rel_top_level = qorai_extras

    top_level_dir = os.path.join(_GetSrcDir(), qorai_rel_top_level)
    rel_start_dir = os.path.join(top_level_dir, qorai_rel_start)
    qorai_classes = original_function(rel_start_dir, top_level_dir, *args,
                                      **kwargs)

    qorai_classes.update(original)
    return qorai_classes
