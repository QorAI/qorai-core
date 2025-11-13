// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_MODULES_QORAI_QORAI_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_MODULES_QORAI_QORAI_H_

#include "third_party/blink/renderer/bindings/core/v8/script_promise.h"
#include "third_party/blink/renderer/core/execution_context/navigator_base.h"
#include "third_party/blink/renderer/modules/modules_export.h"
#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"

namespace blink {

class ScriptState;

class MODULES_EXPORT Qorai final : public ScriptWrappable,
                                   public Supplement<NavigatorBase> {
  DEFINE_WRAPPERTYPEINFO();

 public:
  static const char kSupplementName[];

  static Qorai* qorai(NavigatorBase& navigator);

  explicit Qorai(NavigatorBase& navigator);
  ~Qorai() override = default;

  void Trace(Visitor*) const override;

  ScriptPromise<IDLBoolean> isQorai(ScriptState*);
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_MODULES_QORAI_QORAI_H_
