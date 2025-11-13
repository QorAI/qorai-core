/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_SERVER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_SERVER_UTIL_H_

#include <string>

#include "base/no_destructor.h"

namespace qorai_adaptive_captcha {

class ServerUtil {
 public:
  ServerUtil(const ServerUtil&) = delete;
  ServerUtil& operator=(const ServerUtil&) = delete;
  ~ServerUtil();

  static ServerUtil* GetInstance();

  std::string GetServerUrl(const std::string& path);
  void SetServerHostForTesting(const std::string& host);

 private:
  friend class base::NoDestructor<ServerUtil>;
  ServerUtil();

  std::string GetHost();

  std::string server_host_;
};

}  // namespace qorai_adaptive_captcha

#endif  // QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_SERVER_UTIL_H_
