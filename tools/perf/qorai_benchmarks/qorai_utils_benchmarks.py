# Copyright (c) 2023 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

# A special utility benchmark that doesn't measure anything.
#
# Used as part of chromium src/tools/perf/benchmarks/
# Uses the the same code conventions (including pylint).
# pylint: disable=import-error, no-self-use
# pylint: disable=no-name-in-module, too-few-public-methods
# pytype: disable=import-error

import os

from core import perf_benchmark

from core.path_util import SysPath, GetChromiumSrcDir

with SysPath(os.path.join(GetChromiumSrcDir(), 'qorai', 'tools', 'perf')):
  from qorai_page_sets.qorai_perf_utils_pages import QoraiPerfUtilsStorySet


class QoraiUtilsBenchmark(perf_benchmark.PerfBenchmark):
  """A special benchmark for utility purposes.

    Doesn't measure anything.
  """

  def CreateStorySet(self, options):
    return QoraiPerfUtilsStorySet(30, options)

  @classmethod
  def Name(cls):
    return 'qorai_utils.offline'


class QoraiUtilsOnlineBenchmark(QoraiUtilsBenchmark):
  """A version of QoraiUtilsBenchmark with an internet connection."""
  options = {
      'use_live_sites': True,
  }
  # A default delay.
  # SB database update is started <=5 minutes after browser start
  # (kV4TimerStartIntervalSecMax = 300). Add extra 3 minutes to ensure
  # the database is updated. Default delay is 8 minutes.
  _delay = 8 * 60

  @classmethod
  def AddBenchmarkCommandLineArgs(cls, parser):
    parser.add_argument('--delay', type=int, help='Override the default delay')

  @classmethod
  def ProcessCommandLineArgs(cls, _parser, args):
    if args.delay:
      cls._delay = args.delay

  def CreateStorySet(self, options):
    return QoraiPerfUtilsStorySet(self._delay, options)

  def SetExtraBrowserOptions(self, options):
    # To enable Safe Browsing updates:
    options.disable_background_networking = False

  @classmethod
  def Name(cls):
    return 'qorai_utils.online'
