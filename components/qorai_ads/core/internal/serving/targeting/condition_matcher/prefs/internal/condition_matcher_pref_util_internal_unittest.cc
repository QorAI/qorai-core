/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_pref_util_internal.h"

#include <string>

#include "base/containers/span.h"
#include "qorai/components/qorai_ads/core/internal/ads_client/ads_client_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/local_state_pref_registry_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_registry_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsConditionMatcherPrefUtilTest : public test::TestBase {};

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotConvertNoneValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(ToString(base::Value()));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, BooleanValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("0", ToString(base::Value(false)));
  EXPECT_EQ("1", ToString(base::Value(true)));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, IntegerValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("123", ToString(base::Value(123)));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, DoubleValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("1.23", ToString(base::Value(1.23)));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, StringValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("123", ToString(base::Value("123")));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotConvertDictValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(ToString(base::Value(base::Value::Dict().Set("foo", "bar"))));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotConvertListValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(ToString(base::Value(base::Value::List().Append("foo"))));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotConvertBinaryValueTypeToString) {
  // Arrange
  // Act & Assert
  EXPECT_FALSE(ToString(base::Value(
      base::span<const uint8_t>({0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57,
                                 0x6F, 0x72, 0x6C, 0x64, 0x21}))));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetVirtualPrefValue) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::Value::Dict().Set("[virtual]:matrix", /*room*/ 303);
  });

  // Act & Assert
  EXPECT_EQ(
      base::Value(/*room*/ 303),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "[virtual]:matrix"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, DoNotGetUnknownVirtualPrefValue) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::Value::Dict().Set("[virtual]:inverse.matrices", /*room*/ 101);
  });

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "[virtual]:matrix"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetBooleanProfilePrefValue) {
  // Arrange
  test::RegisterProfileBooleanPref("boolean", true);

  // Act & Assert
  EXPECT_EQ(base::Value(true),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "boolean"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetIntegerProfilePrefValue) {
  // Arrange
  test::RegisterProfileIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ(base::Value(123),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "integer"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetDoubleProfilePrefValue) {
  // Arrange
  test::RegisterProfileDoublePref("double", 1.23);

  // Act & Assert
  EXPECT_EQ(base::Value(1.23),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "double"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetStringProfilePrefValue) {
  // Arrange
  test::RegisterProfileStringPref("string", "foo");

  // Act & Assert
  EXPECT_EQ(base::Value("foo"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "string"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref("dict", base::Value::Dict().Set("foo", "bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetNestedDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref(
      "dict",
      base::Value::Dict().Set("foo", base::Value::Dict().Set("bar", "qux")));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|bar"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetDeeplyNestedDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref(
      "dict", base::Value::Dict().Set(
                  "foo", base::Value::List().Append("bar").Append(
                             base::Value::Dict().Set("baz", "qux"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|1|baz"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetNestedDictProfilePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterProfileDictPref(
      "dict", base::Value::Dict().Set(
                  "foo.bar", base::Value::Dict().Set("baz.qux", "quux")));

  // Act & Assert
  EXPECT_EQ(base::Value("quux"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "dict|foo.bar|baz.qux"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotGetMalformedDictProfilePrefValue) {
  test::RegisterProfileDictPref("dict",
                                base::Value::Dict().Set("foo.bar", "baz"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo.bar|baz"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::Value::List().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetNestedListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::Value::List().Append(
                  base::Value::List().Append("foo").Append("bar")));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetDeeplyNestedListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::Value::List().Append(base::Value::Dict().Set(
                  "foo", base::Value::List().Append("bar").Append("baz"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("baz"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetNestedListProfilePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::Value::List().Append(base::Value::Dict().Set(
                  "foo.bar",
                  base::Value::List().Append("baz.qux").Append("quux.corge"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("quux.corge"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo.bar|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotGetListProfilePrefValueWithOutOfBoundsListIndicies) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::Value::List().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|-1"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|2"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotGetMalformedListProfilePrefValue) {
  test::RegisterProfileListPref("list", base::Value::List().Append("foo"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|bar"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetBooleanLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateBooleanPref("boolean", true);

  // Act & Assert
  EXPECT_EQ(base::Value(true),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "boolean"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetIntegerLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ(base::Value(123),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "integer"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetDoubleLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDoublePref("double", 1.23);

  // Act & Assert
  EXPECT_EQ(base::Value(1.23),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "double"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetStringLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateStringPref("string", "foo");

  // Act & Assert
  EXPECT_EQ(base::Value("foo"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "string"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref("dict",
                                   base::Value::Dict().Set("foo.bar", "baz"));

  // Act & Assert
  EXPECT_EQ(
      base::Value("baz"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo.bar"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetNestedDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref(
      "dict",
      base::Value::Dict().Set("foo", base::Value::Dict().Set("bar", "qux")));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|bar"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetDeeplyNestedDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref(
      "dict", base::Value::Dict().Set(
                  "foo", base::Value::List().Append("bar").Append(
                             base::Value::Dict().Set("baz", "qux"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|1|baz"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetNestedDictLocalStatePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterLocalStateDictPref(
      "dict", base::Value::Dict().Set(
                  "foo.bar", base::Value::Dict().Set("baz.qux", "quux")));

  // Act & Assert
  EXPECT_EQ(base::Value("quux"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "dict|foo.bar|baz.qux"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotGetMalformedDictLocalStatePrefValue) {
  test::RegisterLocalStateDictPref("dict",
                                   base::Value::Dict().Set("foo.bar", "baz"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo.bar|baz"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::Value::List().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, GetNestedListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::Value::List().Append(
                  base::Value::List().Append("foo").Append("bar")));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetDeeplyNestedListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::Value::List().Append(base::Value::Dict().Set(
                  "foo", base::Value::List().Append("bar").Append("baz"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("baz"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       GetNestedListLocalStatePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::Value::List().Append(base::Value::Dict().Set(
                  "foo.bar",
                  base::Value::List().Append("baz.qux").Append("quux.corge"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("quux.corge"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo.bar|1"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotGetMalformedListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref("list", base::Value::List().Append("foo"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|bar"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest,
       DoNotGetListLocalStatePrefValueWithOutOfBoundsListIndicies) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::Value::List().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|-1"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|2"));
}

TEST_F(QoraiAdsConditionMatcherPrefUtilTest, DoNotGetUnknownPrefValue) {
  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "foo.bar"));
}

}  // namespace qorai_ads
