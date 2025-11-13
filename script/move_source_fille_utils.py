# Copyright (c) 2022 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/. */

"""This utils is used in chromium tools/git/move_source_file.py."""

import os

QORAI_DIR_NAME = 'qorai'

def _is_in_qorai_dir():
  return QORAI_DIR_NAME == os.path.basename(os.getcwd())


def to_src_relative_path(*args):
  if _is_in_qorai_dir():
    return tuple(os.path.join(QORAI_DIR_NAME, d) for d in args)
  return args


def to_cwd_relative_path(*args):
  if _is_in_qorai_dir():
    return tuple(os.path.relpath(d, QORAI_DIR_NAME) for d in args)
  return args
