/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/browser/api/qorai_vpn_api_helper.h"

#include "base/base64.h"
#include "base/values.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace qorai_vpn {

TEST(QoraiVPNAPIHelperTest, TicketInfoTest) {
  base::Value::Dict ticket_value = GetValueWithTicketInfos(
      "qorai-vpn@qoranet.com", "It's cool feature", "Love the Qorai VPN!",
      "credential", "USA/Boston");

  // Check ticket dict has four required fields.
  EXPECT_TRUE(ticket_value.FindString(kSupportTicketEmailKey));
  EXPECT_TRUE(ticket_value.FindString(kSupportTicketSubjectKey));
  EXPECT_TRUE(ticket_value.FindString(kSupportTicketPartnerClientIdKey));
  const auto support_ticket_encoded =
      *ticket_value.FindString(kSupportTicketSupportTicketKey);
  EXPECT_TRUE(!support_ticket_encoded.empty());
  auto* timezone = ticket_value.FindString(kSupportTicketTimezoneKey);
  ASSERT_TRUE(timezone);
  EXPECT_EQ(*timezone, "USA/Boston");
  // Check body contents
  std::string support_ticket_decoded;
  EXPECT_TRUE(
      base::Base64Decode(support_ticket_encoded, &support_ticket_decoded));
  const std::string expected_support_ticket =
      "Love the Qorai VPN!\n\nsubscriber-credential: "
      "credential\npayment-validation-method: qorai-premium";
  EXPECT_EQ(expected_support_ticket, support_ticket_decoded);
}

}  // namespace qorai_vpn
