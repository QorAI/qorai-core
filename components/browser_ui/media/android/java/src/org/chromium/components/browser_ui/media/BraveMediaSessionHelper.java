/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.browser_ui.media;

import android.graphics.Bitmap;

import androidx.annotation.Nullable;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.chromium.content.browser.MediaSessionImpl;
import org.chromium.content_public.browser.MediaSession;
import org.chromium.content_public.browser.MediaSessionObserver;
import org.chromium.content_public.browser.WebContents;
import org.chromium.services.media_session.MediaImage;
import org.chromium.services.media_session.MediaMetadata;
import org.chromium.services.media_session.MediaPosition;
import org.chromium.url.GURL;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class QoraiMediaSessionHelper implements MediaImageCallback {
    private static final List<String> sQoraiTalkHosts =
            Arrays.asList("talk.qorai.com", "talk.qoraisoftware.com", "talk.qorai.software");

    public static boolean isQoraiTalk(WebContents webContents) {
        if (webContents == null) {
            return false;
        }
        GURL pageUrl = webContents.getLastCommittedUrl();
        if (pageUrl.isValid()
                && pageUrl.getScheme().equals(UrlConstants.HTTPS_SCHEME)
                && sQoraiTalkHosts.contains(pageUrl.getHost())) {
            return true;
        }

        return false;
    }

    private boolean isQoraiTalk() {
        WebContents webContents =
                (WebContents)
                        QoraiReflectionUtil.getField(
                                MediaSessionHelper.class, "mWebContents", this);

        return isQoraiTalk(webContents);
    }

    @Override
    public void onImageDownloaded(Bitmap image) {}

    public void showNotification() {
        MediaNotificationInfo.Builder notificationInfoBuilder =
                (MediaNotificationInfo.Builder)
                        QoraiReflectionUtil.getField(
                                MediaSessionHelper.class, "mNotificationInfoBuilder", this);
        if (notificationInfoBuilder != null && isQoraiTalk()) {
            notificationInfoBuilder.setActions(0);
            HashSet<Integer> actionSet = new HashSet<Integer>();
            actionSet.add(0);
            notificationInfoBuilder.setMediaSessionActions(actionSet);
            Set<Integer> mediaSessionActions =
                    (Set<Integer>)
                            QoraiReflectionUtil.getField(
                                    MediaSessionHelper.class, "mMediaSessionActions", this);
            if (mediaSessionActions != null) {
                mediaSessionActions = actionSet;
            }
        }
        QoraiReflectionUtil.invokeMethod(MediaSessionHelper.class, this, "showNotification");
    }

    protected MediaSessionObserver createMediaSessionObserver(MediaSession mediaSession) {
        MediaSessionObserver mediaSessionObserver =
                (MediaSessionObserver)
                        QoraiReflectionUtil.invokeMethod(
                                MediaSessionHelper.class,
                                this,
                                "createMediaSessionObserver",
                                MediaSession.class,
                                mediaSession);
        assert mediaSessionObserver != null;

        if (!isQoraiTalk()) {
            return mediaSessionObserver;
        }
        ((MediaSessionImpl) mediaSession).removeObserver(mediaSessionObserver);
        return new MediaSessionObserver(mediaSession) {
            @Override
            public void mediaSessionDestroyed() {
                mediaSessionObserver.mediaSessionDestroyed();
            }

            @Override
            public void mediaSessionStateChanged(boolean isControllable, boolean isPaused) {
                isControllable = true;
                isPaused = false;
                mediaSessionObserver.mediaSessionStateChanged(isControllable, isPaused);
            }

            @Override
            public void mediaSessionMetadataChanged(MediaMetadata metadata) {
                mediaSessionObserver.mediaSessionMetadataChanged(metadata);
            }

            @Override
            public void mediaSessionActionsChanged(Set<Integer> actions) {
                mediaSessionObserver.mediaSessionActionsChanged(actions);
            }

            @Override
            public void mediaSessionArtworkChanged(List<MediaImage> images) {
                mediaSessionObserver.mediaSessionArtworkChanged(images);
            }

            @Override
            public void mediaSessionPositionChanged(@Nullable MediaPosition position) {
                mediaSessionObserver.mediaSessionPositionChanged(position);
            }
        };
    }
}
