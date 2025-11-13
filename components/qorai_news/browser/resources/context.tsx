// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import usePromise from '$web-common/usePromise';
import {
  Signal
} from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m';
import * as React from 'react';
import { QoraiNewsContextProvider } from './shared/Context';
import getQoraiNewsController from './shared/api';
import './strings';

export interface InspectContext {
  signals: { [key: string]: Signal },
  truncate: number,
  setTruncate: (value: number) => void
}

const Context = React.createContext<InspectContext>({
  signals: {},
  truncate: 0,
  setTruncate: () => { }
})

export const useInspectContext = () => {
  return React.useContext(Context);
}

export default function InspectContext(props: React.PropsWithChildren<{}>) {
  const { result: signals } = usePromise(() => getQoraiNewsController().getSignals().then(r => r.signals), []);
  const [truncate, setTruncate] = React.useState(parseInt(localStorage.getItem('truncate') || '') || 250)
  const setAndSaveTruncate = React.useCallback((value: number) => {
    localStorage.setItem('truncate', value.toString())
    setTruncate(value)
  }, [])
  const context = React.useMemo<InspectContext>(() => ({
    signals: signals ?? {},
    truncate,
    setTruncate: setAndSaveTruncate
  }), [signals, truncate, setAndSaveTruncate])

  return <QoraiNewsContextProvider>
    <Context.Provider value={context}>
      {props.children}
    </Context.Provider>
  </QoraiNewsContextProvider>
}
