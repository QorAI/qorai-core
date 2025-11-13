/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/sync/qorai_sync_devices_android.h"

#include <string>
#include <utility>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/check.h"
#include "base/check_op.h"
#include "base/json/json_writer.h"
#include "base/logging.h"
#include "qorai/components/qorai_sync/sync_service_impl_helper.h"
#include "qorai/components/sync/service/qorai_sync_service_impl.h"
#include "qorai/components/sync_device_info/qorai_device_info.h"
#include "chrome/android/chrome_jni_headers/QoraiSyncDevices_jni.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/sync/device_info_sync_service_factory.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "components/sync_device_info/device_info_sync_service.h"
#include "components/sync_device_info/device_info_tracker.h"
#include "components/sync_device_info/local_device_info_provider.h"

namespace chrome {
namespace android {

QoraiSyncDevicesAndroid::QoraiSyncDevicesAndroid(
    JNIEnv* env, const base::android::JavaRef<jobject>& obj) :
    weak_java_qorai_sync_worker_(env, obj) {
  Java_QoraiSyncDevices_setNativePtr(env, obj,
    reinterpret_cast<intptr_t>(this));

  profile_ =
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile();
  DCHECK_NE(profile_, nullptr);

  syncer::DeviceInfoTracker* tracker =
    DeviceInfoSyncServiceFactory::GetForProfile(profile_)
       ->GetDeviceInfoTracker();
  DCHECK(tracker);
  if (tracker) {
    device_info_tracker_observer_.Observe(tracker);
  }
}

QoraiSyncDevicesAndroid::~QoraiSyncDevicesAndroid() {
  // Observer will be removed by ScopedObservation
}

void QoraiSyncDevicesAndroid::Destroy(JNIEnv* env) {
  delete this;
}

void QoraiSyncDevicesAndroid::OnDeviceInfoChange() {
  // Notify Java code
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiSyncDevices_deviceInfoChanged(env,
      weak_java_qorai_sync_worker_.get(env));
}

base::Value::List QoraiSyncDevicesAndroid::GetSyncDeviceList() {
  auto* device_info_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  syncer::DeviceInfoTracker* tracker =
      device_info_service->GetDeviceInfoTracker();
  DCHECK(tracker);
  const syncer::DeviceInfo* local_device_info = device_info_service
     ->GetLocalDeviceInfoProvider()->GetLocalDeviceInfo();

  base::Value::List device_list;

  for (const auto& device : tracker->GetAllQoraiDeviceInfo()) {
    auto device_value = device->ToValue();
    bool is_current_device =
        local_device_info && local_device_info->guid() == device->guid();
    device_value.Set("isCurrentDevice", is_current_device);
    // DeviceInfo::ToValue doesn't put guid
    device_value.Set("guid", device->guid());
    device_value.Set("supportsSelfDelete", device->is_self_delete_supported());
    device_list.Append(std::move(device_value));
  }

  return device_list;
}

base::android::ScopedJavaLocalRef<jstring>
QoraiSyncDevicesAndroid::GetSyncDeviceListJson(JNIEnv* env) {
  std::string json_string;
  if (!base::JSONWriter::Write(GetSyncDeviceList(), &json_string)) {
    VLOG(1) << "Writing as JSON failed. Passing empty string to Java code.";
    json_string = std::string();
  }

  return base::android::ConvertUTF8ToJavaString(env, json_string);
}

// TODO(AlexeyBarabash): duplicate with QoraiSyncWorker?
syncer::QoraiSyncServiceImpl* QoraiSyncDevicesAndroid::GetSyncService() const {
  return SyncServiceFactory::IsSyncAllowed(profile_)
             ? static_cast<syncer::QoraiSyncServiceImpl*>(
                   SyncServiceFactory::GetForProfile(profile_))
             : nullptr;
}

void QoraiSyncDevicesAndroid::DeleteDevice(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& device_guid) {
  std::string str_device_guid =
      base::android::ConvertJavaStringToUTF8(device_guid);
  auto* sync_service = GetSyncService();
  DCHECK(sync_service);

  auto* device_info_sync_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  DCHECK(device_info_sync_service);

  qorai_sync::DeleteDevice(sync_service, device_info_sync_service,
                           str_device_guid);
}

static void JNI_QoraiSyncDevices_Init(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  new QoraiSyncDevicesAndroid(env, jcaller);
}

}  // namespace android
}  // namespace chrome
