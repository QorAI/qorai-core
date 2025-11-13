/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_COMMON_FUNCTIONAL_ONCE_CLOSURE_TASK_QUEUE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_COMMON_FUNCTIONAL_ONCE_CLOSURE_TASK_QUEUE_H_

#include "base/containers/queue.h"
#include "base/functional/callback.h"

namespace qorai_ads {

class OnceClosureTaskQueue final {
 public:
  OnceClosureTaskQueue();

  OnceClosureTaskQueue(const OnceClosureTaskQueue&) = delete;
  OnceClosureTaskQueue& operator=(const OnceClosureTaskQueue&) = delete;

  ~OnceClosureTaskQueue();

  void Add(base::OnceClosure closure);
  void FlushAndStopQueueing();

  bool should_queue() const { return should_queue_; }

  bool empty() const { return queue_.empty(); }

 private:
  bool should_queue_ = true;
  base::queue<base::OnceClosure> queue_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_COMMON_FUNCTIONAL_ONCE_CLOSURE_TASK_QUEUE_H_
