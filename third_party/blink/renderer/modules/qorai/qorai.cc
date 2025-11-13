/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/third_party/blink/renderer/modules/qorai/qorai.h"

#include "third_party/blink/renderer/bindings/core/v8/script_promise.h"
#include "third_party/blink/renderer/bindings/core/v8/script_promise_resolver.h"

namespace blink {

const char Qorai::kSupplementName[] = "Qorai";

Qorai::Qorai(NavigatorBase& navigator) : Supplement<NavigatorBase>(navigator) {}

Qorai* Qorai::qorai(NavigatorBase& navigator) {
  auto* supplement = Supplement<NavigatorBase>::From<Qorai>(navigator);
  if (!supplement) {
    supplement = MakeGarbageCollected<Qorai>(navigator);
    Supplement<NavigatorBase>::ProvideTo(navigator, supplement);
  }
  return supplement;
}

ScriptPromise<IDLBoolean> Qorai::isQorai(ScriptState* script_state) {
  auto* resolver =
      MakeGarbageCollected<ScriptPromiseResolver<IDLBoolean>>(script_state);
  ScriptPromise<IDLBoolean> promise = resolver->Promise();
  resolver->Resolve(true);
  return promise;
}

void Qorai::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  Supplement<NavigatorBase>::Trace(visitor);
}

}  // namespace blink
