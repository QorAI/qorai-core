/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Reducer
import { stackWidgetReducer, handleWidgetPrefsChange } from '../../../qorai_new_tab_ui/reducers/stack_widget_reducer'

// API
import * as storage from '../../../qorai_new_tab_ui/storage/new_tab_storage'
import { types } from '../../../qorai_new_tab_ui/constants/stack_widget_types'

describe('stackWidgetReducer', () => {
  describe('SET_FOREGROUND_STACK_WIDGET', () => {
    it('adds widget if it is not in the stack and sets it to the foreground', () => {
      const assertion = stackWidgetReducer({
        ...storage.defaultState,
        widgetStackOrder: ['rewards']
      }, {
        type: types.SET_FOREGROUND_STACK_WIDGET,
        payload: {
          widget: 'qoraiTalk'
        }
      })
      const expectedState = {
        ...storage.defaultState,
        widgetStackOrder: ['rewards', 'qoraiTalk']
      }
      expect(assertion).toEqual(expectedState)
    })

    it('sets a widget to the foreground if it is in the stack', () => {
      const assertion = stackWidgetReducer({
        ...storage.defaultState,
        widgetStackOrder: ['qoraiTalk', 'rewards']
      }, {
        type: types.SET_FOREGROUND_STACK_WIDGET,
        payload: {
          widget: 'qoraiTalk'
        }
      })
      const expectedState = {
        ...storage.defaultState,
        widgetStackOrder: ['rewards', 'qoraiTalk']
      }
      expect(assertion).toEqual(expectedState)
    })

    it('does not re-add a widget', () => {
      const assertion = stackWidgetReducer({
        ...storage.defaultState,
        widgetStackOrder: ['qoraiTalk', 'rewards']
      }, {
        type: types.SET_FOREGROUND_STACK_WIDGET,
        payload: {
          widget: 'rewards'
        }
      })
      const expectedState = {
        ...storage.defaultState,
        widgetStackOrder: ['qoraiTalk', 'rewards']
      }
      expect(assertion).toEqual(expectedState)
    })
  })

  describe('addNewStackWidget', () => {
    it('puts new widget at the top at first', () => {
      const state = {
        ...storage.defaultState,
        widgetStackOrder: ['qoraiTalk', 'rewards']
      }

      // Last item in |widgetStackOrder| is top-most card.
      const expectedState = {
        ...storage.defaultState,
        widgetStackOrder: ['qoraiTalk', 'rewards', 'qoraiVPN']
      }

      const assertion = storage.addNewStackWidget(state)
      expect(assertion).toEqual(expectedState)
    })
  })

  describe('handleWidgetPrefsChange', () => {
    it('puts a widget in the forgeround if it is being turned back on', () => {
      const oldState = {
        ...storage.defaultState,
        showQorAITalk: false
      }
      const newState = {
        ...storage.defaultState,
        showQorAITalk: true
      }
      const expectedState = {
        ...storage.defaultState,
        showQorAITalk: true,
        widgetStackOrder: ['rewards', 'qoraiVPN', 'qoraiTalk']
      }
      const assertion = handleWidgetPrefsChange(newState, oldState)
      expect(assertion).toEqual(expectedState)

      // Test again for vpn widget.
      newState.showQorAITalk = false
      expectedState.showQorAITalk = false;
      newState.showQorAIVPN = true
      expectedState.showQorAIVPN = true
      expectedState.widgetStackOrder = ['rewards', 'qoraiVPN']

      const assertionForVPN = handleWidgetPrefsChange(newState, oldState)
      expect(assertionForVPN).toEqual(expectedState)
    })
    it('removes a widget from the stack if its being turned off', () => {
      const oldState = {
        ...storage.defaultState,
        showQorAITalk: true
      }
      const newState = {
        ...storage.defaultState,
        showQorAITalk: false
      }
      const expectedState = {
        ...storage.defaultState,
        showQorAITalk: false,
        removedStackWidgets: ['qoraiTalk']
      }
      const assertion = handleWidgetPrefsChange(newState, oldState)
      expect(assertion).toEqual(expectedState)
    })
  })
})
