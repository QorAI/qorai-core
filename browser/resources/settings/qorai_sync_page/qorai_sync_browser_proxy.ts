// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import {SyncStatus} from '/shared/settings/people_page/sync_browser_proxy.js';
import {sendWithPromise} from 'chrome://resources/js/cr.js';

export type QoraiDeviceInfo = {
  name: string
  guid: string
  id: string
  os: string
  type: string
  chromeVersion: string
  lastUpdatedTimestamp: number
  sendTabToSelfReceivingEnabled: boolean
  supportsSelfDelete: boolean
  isCurrentDevice: boolean
  hasSharingInfo: boolean
}

export interface QoraiSyncStatus extends SyncStatus {
  hasSyncWordsDecryptionError: boolean
  isOsEncryptionAvailable: boolean
}

export class QoraiSyncBrowserProxy {
  getSyncCode(): Promise<string> {
    return sendWithPromise('SyncSetupGetSyncCode');
  }

  getPureSyncCode(): Promise<string> {
    return sendWithPromise('SyncSetupGetPureSyncCode');
  }

  getQRCode(syncCode: string): Promise<string> {
    return sendWithPromise('SyncGetQRCode', syncCode);
  }

  copySyncCodeToClipboard(syncCode: string): Promise<boolean> {
    return sendWithPromise('SyncCopySyncCodeToClipboard', syncCode);
  }

  getDeviceList(): Promise<QoraiDeviceInfo[]> {
    return sendWithPromise('SyncGetDeviceList');
  }

  setSyncCode(syncCode: string): Promise<boolean> {
    return sendWithPromise('SyncSetupSetSyncCode', syncCode);
  }

  resetSyncChain(): Promise<boolean> {
    return sendWithPromise('SyncSetupReset');
  }

  deleteDevice(deviceId: string): Promise<boolean> {
    return sendWithPromise('SyncDeleteDevice', deviceId);
  }

  getSyncStatus(): Promise<QoraiSyncStatus> {
    return sendWithPromise('SyncSetupGetSyncStatus');
  }

  permanentlyDeleteSyncAccount(): Promise<boolean> {
    return sendWithPromise('SyncPermanentlyDeleteAccount');
  }

  getWordsCount(syncCode: string): Promise<number> {
    return sendWithPromise('SyncGetWordsCount', syncCode);
  }
  static getInstance() {
    return instance || (instance = new QoraiSyncBrowserProxy())
  }
}

let instance: QoraiSyncBrowserProxy|null = null
