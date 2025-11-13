# Copyright (c) 2024 The Qorai Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import qorai_chromium_utils
import override_utils

with qorai_chromium_utils.sys_path('//qorai/tools/perf'):
    from components.cloud_storage import CloudFolder, DownloadFileFromCloudStorage


@override_utils.override_function(globals())
def _RunCommand(original_func, args):
    if args[0] == 'cp' and len(args) == 3:
        # Handle `gsutil cp gs://qorai-perf-data/<sha1> target_file`
        # and reroute it to download the file from qorai s3 cloud storage.
        url = args[1]
        local_filepath = args[2]
        assert url.startswith('gs://')
        bucket = url.split('/')[2]
        hash = url.split('/')[3]
        if bucket == PARTNER_BUCKET or bucket == INTERNAL_BUCKET:
            assert hash is not None
            return DownloadFileFromCloudStorage(CloudFolder.CATAPULT_PERF_DATA,
                                                hash, local_filepath)
        else:
            return original_func(args)

    # 1. Qorai perf tests should use PARTNER_BUCKET to load WPR and other data
    #    from s3://qorai-perf-data/
    # 2. Chromium perf tests with PUBLIC_BUCKET should be handled by the
    #    if-statement above and works as-is.
    # 3. Uploading to original chromium/chrome buckets is restricted for
    #    non-googlers. To update WPR files change the bucket to PARTNER_BUCKET.
    # 4. If it makes sense more gutils => aws handlers could be added in
    #    the future.
    raise RuntimeError('gsutil command is not supported: ' + args.join(''))
