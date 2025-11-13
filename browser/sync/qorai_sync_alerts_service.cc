/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/sync/qorai_sync_alerts_service.h"

#include "base/check.h"
#include "qorai/browser/infobars/qorai_sync_account_deleted_infobar_delegate.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/infobars/content/content_infobar_manager.h"

#if BUILDFLAG(IS_ANDROID)
#include "base/android/jni_android.h"
#include "qorai/build/android/jni_headers/QoraiSyncAccountDeletedInformer_jni.h"
#else
#include "chrome/browser/ui/browser.h"
#endif

QoraiSyncAlertsService::QoraiSyncAlertsService(Profile* profile)
    : profile_(profile) {
  if (SyncServiceFactory::IsSyncAllowed(profile)) {
    syncer::SyncService* service = SyncServiceFactory::GetForProfile(profile_);

    if (service) {
      DCHECK(!sync_service_observer_.IsObservingSource(service));
      sync_service_observer_.AddObservation(service);
    }
  }
}

QoraiSyncAlertsService::~QoraiSyncAlertsService() {}

void QoraiSyncAlertsService::OnStateChanged(syncer::SyncService* service) {
  qorai_sync::Prefs qorai_sync_prefs(profile_->GetPrefs());
  if (!qorai_sync_prefs.IsSyncAccountDeletedNoticePending()) {
    return;
  }

  ShowInfobar();
}

void QoraiSyncAlertsService::OnSyncShutdown(syncer::SyncService* sync_service) {
  if (sync_service_observer_.IsObservingSource(sync_service)) {
    sync_service_observer_.RemoveObservation(sync_service);
  }
}

void QoraiSyncAlertsService::ShowInfobar() {
#if BUILDFLAG(IS_ANDROID)
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiSyncAccountDeletedInformer_show(env);
#else
  Browser* browser = chrome::FindLastActive();
  if (browser) {
    content::WebContents* active_web_contents =
        browser->tab_strip_model()->GetActiveWebContents();
    if (active_web_contents) {
      QoraiSyncAccountDeletedInfoBarDelegate::Create(active_web_contents,
                                                     profile_, browser);
    }
  }
#endif
}
