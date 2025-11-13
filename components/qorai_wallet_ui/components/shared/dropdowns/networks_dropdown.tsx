// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import Icon from '@qorai/qora/react/icon'

// Types
import { QoraiWallet } from '../../../constants/types'

// Utils
import {
  reduceNetworkDisplayName, //
} from '../../../utils/network-utils'
import { getNetworkId } from '../../../common/slices/entities/network.entity'

// Options
import {
  AllNetworksOption, //
  AllNetworksOptionNetworkId,
} from '../../../options/network-filter-options'

// Components
import {
  CreateNetworkIcon, //
} from '../create-network-icon'

// Styled Components
import { DropdownFilter, DropdownOption } from './shared_dropdown.styles'
import { Row } from '../style'

interface Props {
  networks: QoraiWallet.NetworkInfo[]
  selectedNetwork?: QoraiWallet.NetworkInfo
  showAllNetworksOption?: boolean
  onSelectNetwork: (network: QoraiWallet.NetworkInfo) => void
  checkIsNetworkOptionDisabled?: (network: QoraiWallet.NetworkInfo) => boolean
  placeholder?: string
  label?: React.ReactNode
}

export const NetworksDropdown = (props: Props) => {
  const {
    networks,
    selectedNetwork,
    showAllNetworksOption,
    onSelectNetwork,
    checkIsNetworkOptionDisabled,
    placeholder,
    label,
  } = props

  // computed
  const selectedNetworkId = selectedNetwork
    ? getNetworkId(selectedNetwork)
    : undefined

  // render
  return (
    <DropdownFilter
      placeholder={placeholder}
      onChange={(e) => {
        const network = networks.find((n) => getNetworkId(n) === e.value)
        onSelectNetwork(network || AllNetworksOption)
      }}
      value={selectedNetworkId}
    >
      {label && <div slot='label'>{label}</div>}
      <Row
        slot='value'
        justifyContent='flex-start'
      >
        {selectedNetworkId !== AllNetworksOptionNetworkId && (
          <CreateNetworkIcon
            network={selectedNetwork}
            marginRight={8}
            size='medium'
          />
        )}
        {selectedNetworkId === AllNetworksOptionNetworkId
          ? AllNetworksOption?.chainName
          : selectedNetwork
            ? reduceNetworkDisplayName(selectedNetwork.chainName)
            : (placeholder ?? '')}
      </Row>
      {showAllNetworksOption && (
        <qora-option value={AllNetworksOptionNetworkId}>
          <DropdownOption justifyContent='space-between'>
            <Row width='unset'>{AllNetworksOption.chainName}</Row>
            {selectedNetworkId === AllNetworksOptionNetworkId && (
              <Icon name='check-normal' />
            )}
          </DropdownOption>
        </qora-option>
      )}
      {networks.map((network) => {
        const networkId = getNetworkId(network)
        return (
          <qora-option
            value={networkId}
            key={networkId}
          >
            <DropdownOption
              justifyContent='space-between'
              isDisabled={
                checkIsNetworkOptionDisabled
                  ? checkIsNetworkOptionDisabled(network)
                  : false
              }
            >
              <Row width='unset'>
                {networkId !== AllNetworksOptionNetworkId && (
                  <CreateNetworkIcon
                    network={network}
                    marginRight={8}
                    size='medium'
                  />
                )}
                {network.chainName}
              </Row>
              {selectedNetworkId === networkId && <Icon name='check-normal' />}
            </DropdownOption>
          </qora-option>
        )
      })}
    </DropdownFilter>
  )
}
