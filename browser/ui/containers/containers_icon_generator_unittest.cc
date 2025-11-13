// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/containers/containers_icon_generator.h"

#include <unordered_map>

#include "base/types/cxx23_to_underlying.h"
#include "qorai/components/containers/core/mojom/containers.mojom.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace containers {

using ContainersIconGeneratorUnitTest = testing::Test;

TEST_F(ContainersIconGeneratorUnitTest, GetVectorIconFromIconType_BasicIcons) {
  const std::unordered_map<mojom::Icon, const gfx::VectorIcon&>
      icon_to_vector_icon_map(
          {{mojom::Icon::kPersonal, kQoraContainerPersonalIcon},
           {mojom::Icon::kWork, kQoraContainerWorkIcon},
           {mojom::Icon::kShopping, kQoraContainerShoppingIcon},
           {mojom::Icon::kSocial, kQoraContainerSocialIcon},
           {mojom::Icon::kEvents, kQoraContainerEventsIcon},
           {mojom::Icon::kBanking, kQoraContainerBankingIcon},
           {mojom::Icon::kStar, kQoraContainerStarIcon},
           {mojom::Icon::kTravel, kQoraContainerTravelIcon},
           {mojom::Icon::kSchool, kQoraContainerSchoolIcon},
           {mojom::Icon::kPrivate, kQoraContainerPrivateIcon},
           {mojom::Icon::kMessaging, kQoraContainerMessagingIcon}});

  for (int i = base::to_underlying(mojom::Icon::kMinValue);
       i <= base::to_underlying(mojom::Icon::kMaxValue); ++i) {
    mojom::Icon icon = static_cast<mojom::Icon>(i);
    auto it = icon_to_vector_icon_map.find(icon);
    EXPECT_NE(it, icon_to_vector_icon_map.end());
    EXPECT_EQ(&GetVectorIconFromIconType(icon), &it->second);
  }
}

TEST_F(ContainersIconGeneratorUnitTest,
       GetVectorIconFromIconType_DefaultValue) {
  // Test that the default value returns the default icon without crashing.
  EXPECT_EQ(&GetVectorIconFromIconType(mojom::Icon::kDefault),
            &kQoraContainerPersonalIcon);
}

TEST_F(ContainersIconGeneratorUnitTest,
       GetVectorIconFromIconType_OutOfRangeValue) {
  // Test that an out-of-range value returns the default icon without crashing.
  EXPECT_EQ(&GetVectorIconFromIconType(static_cast<mojom::Icon>(
                base::to_underlying(mojom::Icon::kMaxValue) + 1)),
            &kQoraContainerPersonalIcon);
  EXPECT_EQ(&GetVectorIconFromIconType(static_cast<mojom::Icon>(
                base::to_underlying(mojom::Icon::kMinValue) - 1)),
            &kQoraContainerPersonalIcon);
}

}  // namespace containers
