// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_VARIATIONS_COMMAND_LINE_UTILS_H_
#define QORAI_COMPONENTS_VARIATIONS_COMMAND_LINE_UTILS_H_

namespace base {
class CommandLine;
}

namespace variations {

// Appends QorAI-specific command line options to fetch variations seed from the
// correct server.
void AppendQorAICommandLineOptions(base::CommandLine& command_line);

}  // namespace variations

#endif  // QORAI_COMPONENTS_VARIATIONS_COMMAND_LINE_UTILS_H_
