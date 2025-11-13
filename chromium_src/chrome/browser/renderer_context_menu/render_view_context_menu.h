/* Copyright (c) 2018 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_H_

#include "qorai/components/ai_chat/core/browser/engine/engine_consumer.h"
#include "qorai/components/containers/buildflags/buildflags.h"
#include "qorai/components/containers/core/mojom/containers.mojom-forward.h"
#include "qorai/components/text_recognition/common/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_CONTAINERS)
#include "qorai/browser/ui/containers/containers_menu_model.h"
#endif  // BUILDFLAG(ENABLE_CONTAINERS)

#define QORAI_RENDER_VIEW_CONTEXT_MENU_H_  \
 private:                                  \
  friend class QoraiRenderViewContextMenu; \
                                           \
 public:
// define QORAI_RENDER_VIEW_CONTEXT_MENU_H_

// Get the Chromium declaration.
#define RenderViewContextMenu RenderViewContextMenu_Chromium

class QoraiRenderViewContextMenu;

#define RegisterMenuShownCallbackForTesting                      \
  RegisterMenuShownCallbackForTesting(                           \
      base::OnceCallback<void(QoraiRenderViewContextMenu*)> cb); \
  static void RegisterMenuShownCallbackForTesting_unused
#define AppendReadAnythingItem virtual AppendReadAnythingItem
#define AppendDeveloperItems virtual AppendDeveloperItems
#include <chrome/browser/renderer_context_menu/render_view_context_menu.h>  // IWYU pragma: export
#undef AppendDeveloperItems
#undef AppendReadAnythingItem
#undef RegisterMenuShownCallbackForTesting
#undef RenderViewContextMenu
#undef QORAI_RENDER_VIEW_CONTEXT_MENU_H_

// Declare our own subclass with overridden methods.
class QoraiRenderViewContextMenu
    : public RenderViewContextMenu_Chromium
#if BUILDFLAG(ENABLE_CONTAINERS)
    ,
      public containers::ContainersMenuModel::Delegate
#endif  // BUILDFLAG(ENABLE_CONTAINERS)
{
 public:
  // Non-const reference passed in the parent class upstream
  // NOLINTNEXTLINE(runtime/references)
  QoraiRenderViewContextMenu(content::RenderFrameHost& render_frame_host,
                             const content::ContextMenuParams& params);
  ~QoraiRenderViewContextMenu() override;
  // RenderViewContextMenuBase:
  bool IsCommandIdEnabled(int command_id) const override;
  void ExecuteCommand(int id, int event_flags) override;
  void AddSpellCheckServiceItem(bool is_checked) override;
  // Hide base class implementation.
  static void AddSpellCheckServiceItem(ui::SimpleMenuModel* menu,
                                       bool is_checked);
  void AddAccessibilityLabelsServiceItem(bool is_checked) override;
  // Do nothing as we have our own speed reader
  void AppendReadAnythingItem() override {}

  void AppendDeveloperItems() override;

#if BUILDFLAG(ENABLE_CONTAINERS)
  // ContainersMenuModel::Delegate:
  void OnContainerSelected(
      const containers::mojom::ContainerPtr& container) override;
  base::flat_set<std::string> GetCurrentContainerIds() override;
  Browser* GetBrowserToOpenSettings() override;
  float GetScaleFactor() override;
#endif  // BUILDFLAG(ENABLE_CONTAINERS)

  void SetAIEngineForTesting(
      std::unique_ptr<ai_chat::EngineConsumer> ai_engine);
  ai_chat::EngineConsumer* GetAIEngineForTesting() { return ai_engine_.get(); }

 private:
  friend class QoraiRenderViewContextMenuTest;
  // RenderViewContextMenuBase:
  void InitMenu() override;
  void NotifyMenuShown() override;

  bool IsAIChatEnabled() const;
  void ExecuteAIChatCommand(int command);
  void BuildAIChatMenu();

#if BUILDFLAG(ENABLE_CONTAINERS)
  void BuildContainersMenu();
#endif  // BUILDFLAG(ENABLE_CONTAINERS)

#if BUILDFLAG(ENABLE_TEXT_RECOGNITION)
  void CopyTextFromImage();
#endif

  std::unique_ptr<ai_chat::EngineConsumer> ai_engine_;
  ui::SimpleMenuModel ai_chat_submenu_model_;
  ui::SimpleMenuModel ai_chat_change_tone_submenu_model_;
  ui::SimpleMenuModel ai_chat_change_length_submenu_model_;
  ui::SimpleMenuModel ai_chat_social_media_post_submenu_model_;

#if BUILDFLAG(ENABLE_CONTAINERS)
  std::unique_ptr<containers::ContainersMenuModel> containers_submenu_model_;
#endif  // BUILDFLAG(ENABLE_CONTAINERS)
};

// Use our own subclass as the real RenderViewContextMenu.
#define RenderViewContextMenu QoraiRenderViewContextMenu

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_RENDERER_CONTEXT_MENU_RENDER_VIEW_CONTEXT_MENU_H_
