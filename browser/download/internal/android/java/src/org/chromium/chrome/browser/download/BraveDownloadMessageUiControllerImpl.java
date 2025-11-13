/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.download;

import android.text.TextUtils;

import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.components.offline_items_collection.LegacyHelpers;
import org.chromium.components.offline_items_collection.OfflineItem;

public class QoraiDownloadMessageUiControllerImpl {
    public boolean isVisibleToUser(OfflineItem offlineItem) {
        if (offlineItem.isTransient || offlineItem.isSuggested || offlineItem.isDangerous) {
            return false;
        }

        if (LegacyHelpers.isLegacyDownload(offlineItem.id)
                && TextUtils.isEmpty(offlineItem.filePath)) {
            return false;
        }

        return ChromeSharedPreferences.getInstance()
                .readBoolean(
                        QoraiPreferenceKeys.QORAI_DOWNLOADS_DOWNLOAD_PROGRESS_NOTIFICATION_BUBBLE,
                        true);
    }
}
