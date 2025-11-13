/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import * as mixins from '../../lib/css_mixins'

export const root = styled.div`
  position: absolute;
  top: calc(100% + 2px);
  left: 1px;
  overflow: hidden;
  z-index: 1;
  width: 329px;
  box-shadow: 0px 0px 16px rgba(99, 105, 110, 0.28);
  border: solid 1px rgba(0, 0, 0, .15);
  border-radius: 8px;
`

export const content = styled.div`
  background: var(--qorai-palette-white);
  color: var(--qorai-palette-neutral900);
  padding: 14px 21px 16px;

  .qorai-theme-dark & {
    background: var(--qorai-palette-grey800);
    color: var(--qorai-palette-grey000);
  }
`

export const header = styled.div`
  border-bottom: solid 1px var(--qorai-palette-neutral200);
  padding-bottom: 7px;
  display: flex;
  align-items: center;

  .qorai-theme-dark & {
    border-color: var(--qorai-palette-grey700);
  }
`

export const providerIcon = styled.div`
  .icon {
    height: 24px;
    width: auto;
    vertical-align: middle;
    margin-right: 8px;
    margin-bottom: 2px;
  }
`

export const username = styled.div`
  flex: 1 1 auto;
  font-weight: 600;
  font-size: 14px;
  line-height: 20px;

  .qorai-theme-dark & {
    color: var(--qorai-palette-white);
  }
`

export const status = styled.div`
  font-size: 14px;
  line-height: 20px;

  &.connected {
    color: var(--qorai-palette-teal600);
  }

  .icon {
    height: 16px;
    width: auto;
    vertical-align: middle;
    margin-right: 6px;
    margin-bottom: 2px;
  }
`

export const links = styled.div`
  margin: 11px 4px 0;
`

export const link = styled.div`
  button {
    ${mixins.buttonReset}
    font-size: 12px;
    line-height: 24px;
    color: var(--qorai-color-brandQor);
    cursor: pointer;
    display: inline-flex;
    align-items: center;
    gap: 3px;

    &:hover {
      text-decoration: underline;
    }

    .qorai-theme-dark & {
      color: var(--qorai-palette-blurple300);
    }

    --qora-icon-size: 16px;

    qora-icon {
      margin-bottom: 1px;
    }
  }
`

export const linkMarker = styled.div`
  border-radius: 50%;
  display: inline-block;
  height: 5px;
  width: 5px;
  background-color: var(--qorai-palette-grey500);
  margin-bottom: 2px;
  margin-right: 8px;

  .qorai-theme-dark & {
    background-color: var(--qorai-palette-grey600);
  }
`

export const backdrop = styled.div`
  position: fixed;
  top: 0;
  left: 0;
  bottom: 0;
  right: 0;
  z-index: -1;
`
