/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import styled, { ThemeContext } from 'styled-components'
import qoraiDefaultTheme from 'qorai-ui/theme/qorai-default'
import qoraiDarkTheme from 'qorai-ui/theme/qorai-dark'

function createThemeRules (theme: any) {
  if (!theme) {
    return ''
  }

  let list = []

  for (const [key, value] of Object.entries(theme.color)) {
    list.push(`--qorai-color-${key}: ${String(value)};`)
  }
  for (const [key, value] of Object.entries(theme.palette)) {
    list.push(`--qorai-palette-${key}: ${String(value)};`)
  }
  for (const [key, value] of Object.entries(theme.fontFamily)) {
    list.push(`--qorai-font-${key}: ${String(value)};`)
  }

  return list.join('\n')
}

const Wrapper = styled.div`
  ${createThemeRules(qoraiDefaultTheme)}

  &.qorai-theme-dark {
    ${createThemeRules(qoraiDarkTheme)}
  }
`

function normalizeThemeName (name: string) {
  if (name.toLowerCase() === 'dark' || name === qoraiDarkTheme.name) {
    return 'dark'
  }
  return 'default'
}

export function WithThemeVariables (props: { children: React.ReactNode }) {
  const styledComponentsTheme = React.useContext(ThemeContext) || {}

  const currentTheme = normalizeThemeName(
    styledComponentsTheme.name || '')

  return (
    <Wrapper className={`qorai-theme-${currentTheme}`}>
      {props.children}
    </Wrapper>
  )
}
