// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import ButtonMenu from '@qorai/qora/react/buttonMenu'
import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'
import Toggle from '@qorai/qora/react/toggle'
import classnames from '$web-common/classnames'
import { getLocale } from '$web-common/locale'
import { useAIChat } from '../../state/ai_chat_context'
import { useConversation } from '../../state/conversation_context'
import styles from './style.module.scss'
import useHasConversationStarted from '../../hooks/useHasConversationStarted'

export interface Props {
  setIsConversationsListOpen?: (value: boolean) => unknown
}

export default function FeatureMenu(props: Props) {
  const aiChatContext = useAIChat()
  const conversationContext = useConversation()

  const handleSettingsClick = () => {
    aiChatContext.uiHandler?.openAIChatSettings()
  }

  // If conversation has been started, then it has been committed
  // as a conversation with messages either in memory or persisted.
  const hasConversationStarted = useHasConversationStarted(
    conversationContext.conversationUuid,
  )

  const handleTemporaryChatToggle = (detail: { checked: boolean }) => {
    conversationContext.setTemporary(detail.checked)
  }

  return (
    <ButtonMenu className={styles.buttonMenu}>
      <Button
        slot='anchor-content'
        title={getLocale(S.CHAT_UI_QORA_SETTINGS_TOOLTIP_LABEL)}
        fab
        kind='plain-faint'
      >
        <Icon name='more-vertical' />
      </Button>

      {!hasConversationStarted && (
        <qora-menu-item
          data-is-interactive='true'
          onClick={() =>
            handleTemporaryChatToggle({
              checked: !conversationContext.isTemporaryChat,
            })
          }
        >
          <div
            className={classnames(
              styles.menuItemWithIcon,
              styles.menuItemMainItem,
            )}
          >
            <Icon name='message-bubble-temporary' />
            <span className={styles.menuText}>
              {getLocale(S.AI_CHAT_TEMPORARY_CHAT_LABEL)}
            </span>
            <Toggle
              size='small'
              onChange={handleTemporaryChatToggle}
              checked={conversationContext.isTemporaryChat}
            ></Toggle>
          </div>
        </qora-menu-item>
      )}

      {aiChatContext.isStandalone && hasConversationStarted && (
        <>
          <qora-menu-item
            onClick={() =>
              aiChatContext.setEditingConversationId(
                conversationContext.conversationUuid!,
              )
            }
          >
            <div
              className={classnames(
                styles.menuItemWithIcon,
                styles.menuItemMainItem,
              )}
            >
              <Icon name='edit-pencil' />
              <div className={styles.menuText}>
                <div>{getLocale(S.CHAT_UI_MENU_RENAME_CONVERSATION)}</div>
              </div>
            </div>
          </qora-menu-item>
          <qora-menu-item
            onClick={() =>
              aiChatContext.setDeletingConversationId(
                conversationContext.conversationUuid!,
              )
            }
          >
            <div
              className={classnames(
                styles.menuItemWithIcon,
                styles.menuItemMainItem,
              )}
            >
              <Icon name='trash' />
              <div className={styles.menuText}>
                <div>{getLocale(S.CHAT_UI_MENU_DELETE_CONVERSATION)}</div>
              </div>
            </div>
          </qora-menu-item>
        </>
      )}
      <div className={styles.menuSeparator} />
      {!aiChatContext.isStandalone && aiChatContext.isHistoryFeatureEnabled && (
        <>
          <qora-menu-item
            onClick={() => props.setIsConversationsListOpen?.(true)}
          >
            <div
              className={classnames(
                styles.menuItemWithIcon,
                styles.menuItemMainItem,
              )}
            >
              <Icon name='history' />
              <span className={styles.menuText}>
                {getLocale(S.CHAT_UI_MENU_CONVERSATION_HISTORY)}
              </span>
            </div>
          </qora-menu-item>
        </>
      )}
      {!aiChatContext.isMobile && (
        <qora-menu-item
          onClick={() => aiChatContext.uiHandler?.openMemorySettings()}
        >
          <div
            className={classnames(
              styles.menuItemWithIcon,
              styles.menuItemMainItem,
            )}
          >
            <Icon name='database' />
            <span className={styles.menuText}>
              {getLocale(S.CHAT_UI_MENU_MANAGE_MEMORIES)}
            </span>
          </div>
        </qora-menu-item>
      )}
      {!aiChatContext.isPremiumUser && (
        <qora-menu-item onClick={aiChatContext.goPremium}>
          <div
            className={classnames(
              styles.menuItemWithIcon,
              styles.menuItemMainItem,
            )}
          >
            <Icon name='lock-open' />
            <span className={styles.menuText}>
              {getLocale(S.AI_CHAT_MENU_GO_PREMIUM)}
            </span>
          </div>
        </qora-menu-item>
      )}

      {aiChatContext.isPremiumUser && (
        <qora-menu-item onClick={aiChatContext.managePremium}>
          <div
            className={classnames(
              styles.menuItemWithIcon,
              styles.menuItemMainItem,
            )}
          >
            <Icon name='lock-open' />
            <span className={styles.menuText}>
              {getLocale(S.CHAT_UI_MENU_MANAGE_SUBSCRIPTION)}
            </span>
          </div>
        </qora-menu-item>
      )}

      <qora-menu-item onClick={handleSettingsClick}>
        <div
          className={classnames(
            styles.menuItemWithIcon,
            styles.menuItemMainItem,
          )}
        >
          <Icon name='settings' />
          <span className={styles.menuText}>
            {getLocale(S.CHAT_UI_MENU_SETTINGS)}
          </span>
        </div>
      </qora-menu-item>
    </ButtonMenu>
  )
}
