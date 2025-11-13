/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_PLATFORM_BINDINGS_IDL_MEMBER_INSTALLER_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_PLATFORM_BINDINGS_IDL_MEMBER_INSTALLER_H_

struct QoraiNavigatorAttributeInstallerTrait;

#define QORAI_IDL_MEMBER_INSTALLER_H_                                 \
  template <typename T>                                               \
  static void QoraiInstallAttributes(                                 \
      v8::Isolate* isolate, const DOMWrapperWorld& world,             \
      v8::Local<v8::Template> instance_template,                      \
      v8::Local<v8::Template> prototype_template,                     \
      v8::Local<v8::Template> interface_template,                     \
      v8::Local<v8::Signature> signature, const char* interface_name, \
      base::span<const AttributeConfig> configs);                     \
  template <typename T>                                               \
  static void QoraiInstallAttributes(                                 \
      v8::Isolate* isolate, const DOMWrapperWorld& world,             \
      v8::Local<v8::Object> instance_object,                          \
      v8::Local<v8::Object> prototype_object,                         \
      v8::Local<v8::Object> interface_object,                         \
      v8::Local<v8::Signature> signature, const char* interface_name, \
      base::span<const AttributeConfig> configs);

#include <third_party/blink/renderer/platform/bindings/idl_member_installer.h>  // IWYU pragma: export
#undef QORAI_IDL_MEMBER_INSTALLER_H_

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_PLATFORM_BINDINGS_IDL_MEMBER_INSTALLER_H_
