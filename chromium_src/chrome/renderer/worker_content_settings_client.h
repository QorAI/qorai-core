/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_RENDERER_WORKER_CONTENT_SETTINGS_CLIENT_H_
#define QORAI_CHROMIUM_SRC_CHROME_RENDERER_WORKER_CONTENT_SETTINGS_CLIENT_H_

#include "third_party/blink/public/platform/web_content_settings_client.h"

class WorkerContentSettingsClient_QoraiImpl;

#define EnsureContentSettingsManager()          \
  EnsureContentSettingsManager_NotUsed();       \
  friend WorkerContentSettingsClient_QoraiImpl; \
  void EnsureContentSettingsManager()

#define WorkerContentSettingsClient WorkerContentSettingsClient_ChromiumImpl

#include <chrome/renderer/worker_content_settings_client.h>  // IWYU pragma: export

#undef EnsureContentSettingsManager
#undef WorkerContentSettingsClient

class WorkerContentSettingsClient_QoraiImpl
    : public WorkerContentSettingsClient_ChromiumImpl {
 public:
  explicit WorkerContentSettingsClient_QoraiImpl(
      content::RenderFrame* render_frame);
  ~WorkerContentSettingsClient_QoraiImpl() override;

  // WebContentSettingsClient:
  std::unique_ptr<blink::WebContentSettingsClient> Clone() override;
  qorai_shields::mojom::ShieldsSettingsPtr GetQoraiShieldsSettings(
      ContentSettingsType webcompat_settings_type) override;
  blink::WebSecurityOrigin GetEphemeralStorageOriginSync() override;
  bool HasContentSettingsRules() const override;

 private:
  WorkerContentSettingsClient_QoraiImpl(
      const WorkerContentSettingsClient_QoraiImpl& other);

  void EnsureShieldsSettings();

  qorai_shields::mojom::ShieldsSettingsPtr shields_settings_;
};

using WorkerContentSettingsClient = WorkerContentSettingsClient_QoraiImpl;

#endif  // QORAI_CHROMIUM_SRC_CHROME_RENDERER_WORKER_CONTENT_SETTINGS_CLIENT_H_
