// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react';
import styled from 'styled-components';
import Flex from '$web-common/Flex';
import { getLocale } from '../../../../common/locale';
import Icon from '@qorai/qora/react/icon';
import { spacing } from '@qorai/qora/tokens/css/variables';

const Container = styled(Flex)`
  color: var(--bn-glass-50);
  gap: ${spacing.xl};

  & > hr {
    flex: 1;
    border-color: var(--bn-glass-10);
  }
`

export default function CaughtUp() {
  return <Container align='center' justify='stretch'>
    <hr />
    <Flex align='center' gap={6}>
      <Icon name='check-circle-outline' /> <span>{getLocale(S.QORAI_NEWS_CAUGHT_UP)}</span>
    </Flex>
    <hr />
  </Container>
}
