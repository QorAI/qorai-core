// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Button from '@qorai/qora/react/button'

// utils
import { getLocale } from '../../../../../common/locale'

// styles
import { ContinueButton } from '../../onboarding/onboarding.style'
import { SkipDialog, WarningText } from './explain-recovery-phrase.style'

interface SkipWarningDialogProps {
  isOpen: boolean
  onBack: () => void
  onSkip: () => void
}

export const SkipWarningDialog = ({
  isOpen,
  onBack,
  onSkip,
}: SkipWarningDialogProps) => {
  return (
    <SkipDialog
      isOpen={isOpen}
      onClose={onBack}
    >
      <WarningText>{getLocale('qoraiWalletSkipBackupWarning')}</WarningText>
      <div slot='actions'>
        <Button
          kind='plain-faint'
          onClick={onBack}
        >
          {getLocale('qoraiWalletGoBack')}
        </Button>
        <ContinueButton onClick={onSkip}>
          {getLocale('qoraiWalletSkipBackup')}
        </ContinueButton>
      </div>
    </SkipDialog>
  )
}
