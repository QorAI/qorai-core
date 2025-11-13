/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_H_
#define QORAI_COMPONENTS_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_H_

#include <string>

#include "base/component_export.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_refptr.h"
#include "base/types/expected.h"
#include "qorai/components/challenge_bypass_ristretto/rust/cxx/src/lib.rs.h"

namespace challenge_bypass_ristretto {

class COMPONENT_EXPORT(CHALLENGE_BYPASS_RISTRETTO) SignedToken {
  using CxxSignedTokenBox = rust::Box<cbr_cxx::SignedToken>;
  using CxxSignedTokenRefData = base::RefCountedData<CxxSignedTokenBox>;

 public:
  explicit SignedToken(CxxSignedTokenBox raw);
  SignedToken(const SignedToken&);
  SignedToken& operator=(const SignedToken&);
  SignedToken(SignedToken&&) noexcept;
  SignedToken& operator=(SignedToken&&) noexcept;
  ~SignedToken();

  const cbr_cxx::SignedToken& raw() const { return *raw_->data; }

  static base::expected<SignedToken, std::string> DecodeBase64(
      const std::string& encoded);
  std::string EncodeBase64() const;

  bool operator==(const SignedToken& rhs) const;

 private:
  scoped_refptr<CxxSignedTokenRefData> raw_;
};

}  // namespace challenge_bypass_ristretto

#endif  // QORAI_COMPONENTS_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_H_
