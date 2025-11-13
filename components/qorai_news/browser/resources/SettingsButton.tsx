// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Button from "@qorai/qora/react/button";
import { radius, spacing } from "@qorai/qora/tokens/css/variables";
import styled from "styled-components";


const SettingsButton = styled(Button)`
  --qora-button-color: var(--bn-glass-50);
  --qora-button-radius: ${radius.s};
  --qora-button-padding: ${spacing.s};

  flex: 0;
`

SettingsButton.defaultProps = {
  fab: true,
  kind: 'outline'
}

export default SettingsButton
