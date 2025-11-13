/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

use adblock::resources::{InMemoryResourceStorage, ResourceImpl, ResourceStorageBackend};
use std::sync::Arc;

#[derive(Clone)]
pub struct QoraiCoreResourceStorage {
    pub shared_storage: Arc<InMemoryResourceStorage>,
}

impl ResourceStorageBackend for QoraiCoreResourceStorage {
    fn get_resource(&self, resource_ident: &str) -> Option<ResourceImpl> {
        self.shared_storage.get_resource(resource_ident)
    }
}
