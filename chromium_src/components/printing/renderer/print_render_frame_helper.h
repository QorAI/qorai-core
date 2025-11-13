/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_PRINTING_RENDERER_PRINT_RENDER_FRAME_HELPER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_PRINTING_RENDERER_PRINT_RENDER_FRAME_HELPER_H_

#include "components/printing/common/print.mojom.h"

namespace printing {
class PrintRenderFrameHelper;
using PrintRenderFrameHelper_QoraiImpl = PrintRenderFrameHelper;
}  // namespace printing

#define PrintRenderFrameHelper PrintRenderFrameHelper_ChromiumImpl
#define SetupOnStopLoadingTimeout          \
  SetupOnStopLoadingTimeout_Unused();      \
  friend PrintRenderFrameHelper_QoraiImpl; \
  void SetupOnStopLoadingTimeout
#include <components/printing/renderer/print_render_frame_helper.h>  // IWYU pragma: export
#undef SetupOnStopLoadingTimeout
#undef PrintRenderFrameHelper
#undef SetPrintPreviewUI

namespace printing {
class PrintRenderFrameHelper : public PrintRenderFrameHelper_ChromiumImpl {
 public:
  PrintRenderFrameHelper(content::RenderFrame* render_frame,
                         std::unique_ptr<Delegate> delegate);
  PrintRenderFrameHelper(const PrintRenderFrameHelper&) = delete;
  PrintRenderFrameHelper& operator=(const PrintRenderFrameHelper&) = delete;
  ~PrintRenderFrameHelper() override;

 private:
  // printing::mojom::PrintRenderFrame:
#if BUILDFLAG(ENABLE_PRINT_PREVIEW)
  void SetPrintPreviewUI(
      mojo::PendingAssociatedRemote<mojom::PrintPreviewUI> preview) override;
  void InitiatePrintPreview(bool has_selection) override;
  void SetIsPrintPreviewExtraction(bool value) override;

  bool is_print_preview_extraction_ = false;
#endif
};
}  // namespace printing

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_PRINTING_RENDERER_PRINT_RENDER_FRAME_HELPER_H_
