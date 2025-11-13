// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import Flex from '$web-common/Flex';
import { getLocale } from '$web-common/locale';
import Icon from '@qorai/qora/react/icon';
import Input from '@qorai/qora/react/input';
import { color, font, spacing } from '@qorai/qora/tokens/css/variables';
import * as React from 'react';
import styled from 'styled-components';
import EnginePicker from './EnginePicker';
import { useSearchContext } from './SearchContext';
import { qoraiSearchHost, searchBoxRadius } from './config';

const searchBoxClass = 'ntp-search-box'

const SearchInput = styled(Input)`
  --qora-control-focus-effect: none;
  --qora-control-padding: 12px 10px;
  --qora-control-text-color: ${color.text.primary};
  --qora-control-font: ${font.large.regular};

  display: inline-block;
  width: 540px;

  qora-icon {
    --qora-icon-color: ${color.icon.default};
  }
`

const SearchIconContainer = styled.div`
  padding-right: ${spacing.m};
`

const Container = styled.div`
  --qora-control-radius: ${searchBoxRadius};

  display: flex;

  /* If we have search results, don't add a radius to the bottom of the search box */
  &:has(+ .search-results) {
    --qora-control-radius: ${searchBoxRadius} ${searchBoxRadius} 0 0;
  }

  border-radius: var(--qora-control-radius);
`

export default function SearchBox() {
  const { searchEngine, query, setQuery } = useSearchContext()
  const placeholderText = searchEngine?.host === qoraiSearchHost
    ? getLocale('searchQoraiPlaceholder')
    : getLocale('searchNonQoraiPlaceholder')
  const searchInput = React.useRef<HTMLElement>()
  React.useEffect(() => {
    const listener = (e: KeyboardEvent) => {
      if (e.key === 'Tab' && document.activeElement === document.body) {
        e.preventDefault()
        searchInput.current?.focus()
      }
    }
    document.addEventListener('keydown', listener)
    return () => {
      document.removeEventListener('keydown', listener)
    }
  }, [])
  return <Container className={searchBoxClass}>
    <SearchInput tabIndex={1} type="text" ref={searchInput} value={query} onInput={e => setQuery(e.value)} placeholder={placeholderText}>
      <Flex slot="left-icon" align='center'>
        <EnginePicker />
      </Flex>
      <SearchIconContainer slot="right-icon">
        <Icon name="search" />
      </SearchIconContainer>
    </SearchInput>
  </Container>
}
