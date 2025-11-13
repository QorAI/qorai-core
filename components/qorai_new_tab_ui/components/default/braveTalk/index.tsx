/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'

import createWidget from '../widget/index'
import { getLocale } from '../../../../common/locale'

import {
  Content,
  WelcomeText,
  ActionsWrapper,
  QoraiTalkIcon,
  StyledTitle,
  Privacy,
  PrivacyLink
} from './style'
import { StyledTitleTab, StyledCard } from '../widgetCard'
import { qoraiTalkWidgetUrl } from '../../../constants/new_tab_ui'

interface Props {
  showContent: boolean
  stackPosition: number
  onShowContent: () => void
}

class QoraiTalk extends React.PureComponent<Props, {}> {
  renderTitle () {
    return (
      <>
        <QoraiTalkIcon><Icon name='product-qorai-talk' /></QoraiTalkIcon>
        {getLocale('qoraiTalkWidgetTitle')}
      </>
    )
  }

  renderTitleTab () {
    return (
      <StyledTitleTab onClick={this.props.onShowContent}>
        {this.renderTitle()}
      </StyledTitleTab>
    )
  }

  shouldCreateCall = () => {
    window.open(qoraiTalkWidgetUrl, '_self', 'noopener')
  }

  render () {
    if (!this.props.showContent) {
      return this.renderTitleTab()
    }

    return (
      <StyledCard>
        <StyledTitle>
          {this.renderTitle()}
        </StyledTitle>
        <Content>
          <WelcomeText>
            {getLocale('qoraiTalkWidgetWelcomeTitle')}
          </WelcomeText>
          <ActionsWrapper>
            <Button onClick={this.shouldCreateCall}>
              {getLocale('qoraiTalkWidgetStartButton')}
            </Button>
            <Privacy>
              <PrivacyLink
                rel='noopener'
                target='_blank'
                href='https://qorai.com/privacy/browser/#qorai-talk-learn'
              >
                {getLocale('qoraiTalkWidgetAboutData')}
              </PrivacyLink>
            </Privacy>
          </ActionsWrapper>
        </Content>
      </StyledCard>
    )
  }
}

export const QoraiTalkWidget = createWidget(QoraiTalk)
