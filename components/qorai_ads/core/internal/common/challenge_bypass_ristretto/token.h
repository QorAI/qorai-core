/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TOKEN_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TOKEN_H_

#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "base/check.h"
#include "qorai/components/challenge_bypass_ristretto/token.h"

namespace qorai_ads::cbr {

class BlindedToken;

// A `Token` consists of a randomly chosen preimage and blinding factor. Since a
// `Token` includes the blinding factor it should be treated as a client secret
// and NEVER revealed to the server.

class Token {
 public:
  Token();
  explicit Token(const std::string& token_base64);

  Token(const Token&);
  Token& operator=(const Token&);

  Token(Token&&) noexcept;
  Token& operator=(Token&&) noexcept;

  ~Token();

  bool operator==(const Token&) const;

  bool has_value() const { return token_.has_value(); }

  challenge_bypass_ristretto::Token& get() {
    CHECK(token_);
    return *token_;
  }

  const challenge_bypass_ristretto::Token& get() const {
    CHECK(token_);
    return *token_;
  }

  static Token DecodeBase64(const std::string& token_base64);
  std::optional<std::string> EncodeBase64() const;

  std::optional<BlindedToken> Blind();

 private:
  std::optional<challenge_bypass_ristretto::Token> token_;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

using TokenList = std::vector<Token>;

}  // namespace qorai_ads::cbr

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TOKEN_H_
