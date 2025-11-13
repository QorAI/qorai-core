// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_SPEEDREADER_COMMON_CONSTANTS_H_
#define QORAI_COMPONENTS_SPEEDREADER_COMMON_CONSTANTS_H_

#include "components/grit/qorai_components_strings.h"
#include "ui/base/webui/web_ui_util.h"

namespace speedreader {

inline constexpr webui::LocalizedString kLocalizedStrings[] = {
    {"qoraiReaderModeCaption", IDS_READER_MODE_CAPTION},
    {"qoraiReaderModeClose", IDS_READER_MODE_CLOSE},
    {"qoraiReaderModeExit", IDS_READER_MODE_EXIT},
    {"qoraiReaderModeVoice", IDS_READER_MODE_VOICE},
    {"qoraiReaderModeTune", IDS_READER_MODE_TUNE},
    {"qoraiReaderModeAppearance", IDS_READER_MODE_APPEARANCE},
    {"qoraiReaderModeAppearanceThemeLight",
     IDS_READER_MODE_APPEARANCE_THEME_LIGHT},
    {"qoraiReaderModeAppearanceThemeSepia",
     IDS_READER_MODE_APPEARANCE_THEME_SEPIA},
    {"qoraiReaderModeAppearanceThemeDark",
     IDS_READER_MODE_APPEARANCE_THEME_DARK},
    {"qoraiReaderModeAppearanceThemeSystem",
     IDS_READER_MODE_APPEARANCE_THEME_SYSTEM},
    {"qoraiReaderModeAppearanceFontSans", IDS_READER_MODE_APPEARANCE_FONT_SANS},
    {"qoraiReaderModeAppearanceFontSerif",
     IDS_READER_MODE_APPEARANCE_FONT_SERIF},
    {"qoraiReaderModeAppearanceFontMono", IDS_READER_MODE_APPEARANCE_FONT_MONO},
    {"qoraiReaderModeAppearanceFontDyslexic",
     IDS_READER_MODE_APPEARANCE_FONT_DYSLEXIC},
    {"qoraiReaderModeAppearanceColumnWidthNarrow",
     IDS_READER_MODE_APPEARANCE_COLUMN_WIDTH_NARROW},
    {"qoraiReaderModeAppearanceColumnWidthWide",
     IDS_READER_MODE_APPEARANCE_COLUMN_WIDTH_WIDE},
    {"qoraiReaderModeTextToSpeech", IDS_READER_MODE_TEXT_TO_SPEECH},
    {"qoraiReaderModeAI", IDS_READER_MODE_AI},
    {"qoraiReaderModeFontSizeDecrease",
     IDS_READER_MODE_APPEARANCE_FONT_SIZE_DECREASE},
    {"qoraiReaderModeFontSizeIncrease",
     IDS_READER_MODE_APPEARANCE_FONT_SIZE_INCREASE},
    {"qoraiReaderModeTtsRewind", IDS_READER_MODE_TEXT_TO_SPEECH_REWIND},
    {"qoraiReaderModeTtsPlayPause", IDS_READER_MODE_TEXT_TO_SPEECH_PLAY_PAUSE},
    {"qoraiReaderModeTtsForward", IDS_READER_MODE_TEXT_TO_SPEECH_FORWARD},
    {"qoraiReaderModeTtsSpeedDecrease",
     IDS_READER_MODE_TEXT_TO_SPEECH_SPEED_DECREASE},
    {"qoraiReaderModeTtsSpeedIncrease",
     IDS_READER_MODE_TEXT_TO_SPEECH_SPEED_INCREASE},
};

}  // namespace speedreader

#endif  // QORAI_COMPONENTS_SPEEDREADER_COMMON_CONSTANTS_H_
