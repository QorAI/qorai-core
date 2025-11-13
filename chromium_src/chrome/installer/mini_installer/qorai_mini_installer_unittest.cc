/* Copyright (c) 2018 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/installer/mini_installer/mini_installer.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace mini_installer {

class QoraiMiniInstallerTest: public testing::Test {
 public:
  QoraiMiniInstallerTest() {
  }
  ~QoraiMiniInstallerTest() override {}
};


TEST_F(QoraiMiniInstallerTest, HasNoReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup.exe", &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasStandardReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"QoraiBrowserSetup-FOO123.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(QoraiMiniInstallerTest, HasStandardReferralCodeWithLowercase) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"QoraiBrowserSetup-foo123.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(QoraiMiniInstallerTest, HasStandardReferralCodeWithPath) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/QoraiBrowserSetup-FOO123.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(QoraiMiniInstallerTest,
                HasStandardReferralCodeWithDeduplicatingSuffix) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/QoraiBrowserSetup-FOO123 (1).exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(QoraiMiniInstallerTest,
                HasStandardReferralCodeWithDeduplicatingSuffixNoSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/QoraiBrowserSetup-FOO123(1).exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(QoraiMiniInstallerTest,
                HasStandardReferralCodeWithDeduplicatingSuffixExtraSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(
                          L"c:/foo/bar/QoraiBrowserSetup-FOO123   (1).exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeReversed) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-123FOO.exe",
                          &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeNoDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-FOO.exe", &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeNoLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-123.exe", &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeTooManyDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-FOO1234.exe",
                          &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeTooFewDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-FOO12.exe",
                          &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeTooManyLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-FOOO123.exe",
                          &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidStandardReferralCodeTooFewLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-FO123.exe",
                          &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasExtendedReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"QoraiBrowserSetup-extended-code.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"extended-code");
}

TEST_F(QoraiMiniInstallerTest,
                HasInvalidExtendedReferralCodeNonAlphabeticCharacters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(
                          L"QoraiBrowserSetup-invalid-extended-c0de.exe",
                          &referral_code));
}

TEST_F(QoraiMiniInstallerTest, HasInvalidExtendedReferralCodeTooFewWords) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"QoraiBrowserSetup-invalidextendedcode.exe",
                          &referral_code));
}

}  // namespace mini_installer
