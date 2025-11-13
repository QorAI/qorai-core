// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import styled, { css } from 'styled-components'

import Icon from '@qorai/qora/react/icon'
import Button from '@qorai/qora/react/button'
import ButtonMenu from '@qorai/qora/react/buttonMenu'
import { color, spacing } from '@qorai/qora/tokens/css/variables'

interface MenuItemProps {
  name: string
  iconName: string
  onClick: () => void
}

interface MenuProps {
  items: Array<MenuItemProps | undefined>
  visible: boolean
  onShowMenu?: () => void
  onDismissMenu?: () => void
}

const StyledRow = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: ${spacing.m};
`

const StyledButtonMenu = styled(ButtonMenu)<{ visible: boolean }>`
  ${(p) =>
    !p.visible &&
    css`
      visibility: hidden;
    `}
  --qora-icon-size: 20px;
  color: ${color.text.secondary};
`

const StyledButton = styled(Button)`
  --qora-button-padding: 0;
`

export default function ContextualMenuAnchorButton ({
  items,
  visible,
  onShowMenu,
  onDismissMenu
}: MenuProps) {
  const [open, setOpen] = React.useState(false)

  // When the anchor button isn't visible, hide the menu
  React.useEffect(() => {
    if (!visible) setOpen(false)
  }, [visible])

  return (
    <StyledButtonMenu
      visible={visible}
      onChange={({ isOpen }) => {
        if (isOpen) onShowMenu?.()
        setOpen(isOpen)
      }}
      onClose={() => onDismissMenu?.()}
      isOpen={open}
    >
      <StyledButton kind='plain-faint' size='small' slot='anchor-content'>
        <Icon name='more-horizontal' />
      </StyledButton>
      {items
        .filter((i) => i)
        .map((i) => (
          <qora-menu-item
            key={i!.name}
            onClick={(e) => {
              e.stopPropagation()
              i!.onClick()
            }}
          >
            <StyledRow>
              <span>{i!.name}</span>
              <Icon name={i!.iconName} />
            </StyledRow>
          </qora-menu-item>
        ))}
    </StyledButtonMenu>
  )
}
