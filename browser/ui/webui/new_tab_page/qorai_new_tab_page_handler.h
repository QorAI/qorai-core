// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_QORAI_NEW_TAB_PAGE_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_QORAI_NEW_TAB_PAGE_HANDLER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_ui.h"
#include "qorai/components/qorai_new_tab_ui/qorai_new_tab_page.mojom.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/search_engines/template_url_service.h"
#include "components/search_engines/template_url_service_observer.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "ui/shell_dialogs/select_file_dialog.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

namespace base {
class FilePath;
}  // namespace base

namespace content {
class WebContents;
}  // namespace content

class CustomBackgroundFileManager;
class NtpCustomBackgroundService;
class Profile;

class QoraiNewTabPageHandler : public qorai_new_tab_page::mojom::PageHandler,
                               public ui::SelectFileDialog::Listener,
                               public TemplateURLServiceObserver {
 public:
  QoraiNewTabPageHandler(
      mojo::PendingReceiver<qorai_new_tab_page::mojom::PageHandler>
          pending_page_handler,
      mojo::PendingRemote<qorai_new_tab_page::mojom::Page> pending_page,
      Profile* profile,
      content::WebContents* web_contents);
  ~QoraiNewTabPageHandler() override;

  QoraiNewTabPageHandler(const QoraiNewTabPageHandler&) = delete;
  QoraiNewTabPageHandler& operator=(const QoraiNewTabPageHandler&) = delete;

 private:
  // qorai_new_tab_page::mojom::PageHandler overrides:
  void ChooseLocalCustomBackground() override;
  void UseCustomImageBackground(
      const std::string& selected_background) override;
  void GetCustomImageBackgrounds(
      GetCustomImageBackgroundsCallback callback) override;
  void RemoveCustomImageBackground(const std::string& background) override;

  void UseQoraiBackground(const std::string& selected_background) override;
  void GetQoraiBackgrounds(GetQoraiBackgroundsCallback callback) override;
  void TryQoraiSearchPromotion(const std::string& input,
                               bool open_new_tab) override;
  void DismissQoraiSearchPromotion() override;
  void IsSearchPromotionEnabled(
      IsSearchPromotionEnabledCallback callback) override;
  void UseColorBackground(const std::string& color,
                          bool use_random_color) override;
  void GetSearchEngines(GetSearchEnginesCallback callback) override;
  void SearchWhatYouTyped(const std::string& host,
                          const std::string& query,
                          bool alt_key,
                          bool ctrl_key,
                          bool meta_key,
                          bool shift_key) override;

#if BUILDFLAG(ENABLE_QORAI_VPN)
  void RefreshVPNState() override;
  void LaunchVPNPanel() override;
  void OpenVPNAccountPage(qorai_vpn::mojom::ManageURLType type) override;
  void ReportVPNWidgetUsage() override;
#endif

  // Observe QoraiNTPCustomBackgroundService.
  void OnBackgroundUpdated();
  void OnCustomImageBackgroundsUpdated();

  // SelectFileDialog::Listener overrides:
  void FileSelected(const ui::SelectedFileInfo& file, int index) override;
  void MultiFilesSelected(
      const std::vector<ui::SelectedFileInfo>& files) override;
  void FileSelectionCanceled() override;

  // TemplateURLServiceObserver overrides:
  void OnTemplateURLServiceChanged() override;
  void OnTemplateURLServiceShuttingDown() override;

  bool IsCustomBackgroundImageEnabled() const;
  bool IsColorBackgroundEnabled() const;
  void OnSavedCustomImage(const base::FilePath& path);
  void OnRemoveCustomImageBackground(const base::FilePath& path, bool success);

  void OnSearchPromotionDismissed();
  void NotifySearchPromotionDisabledIfNeeded() const;
  void InitForSearchPromotion();

  PrefChangeRegistrar pref_change_registrar_;
  base::ScopedObservation<TemplateURLService, TemplateURLServiceObserver>
      template_url_service_observation_{this};
  const mojo::Receiver<qorai_new_tab_page::mojom::PageHandler> page_handler_;
  const mojo::Remote<qorai_new_tab_page::mojom::Page> page_;
  const raw_ptr<Profile> profile_ = nullptr;
  const raw_ptr<content::WebContents> web_contents_ = nullptr;

  scoped_refptr<ui::SelectFileDialog> select_file_dialog_;
  const std::unique_ptr<CustomBackgroundFileManager> file_manager_;

  base::WeakPtrFactory<QoraiNewTabPageHandler> weak_factory_{this};
};

#endif  // QORAI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_QORAI_NEW_TAB_PAGE_HANDLER_H_
