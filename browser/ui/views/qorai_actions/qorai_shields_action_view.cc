// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/views/qorai_actions/qorai_shields_action_view.h"

#include <memory>
#include <string>
#include <utility>

#include "base/check_deref.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string_number_conversions.h"
#include "qorai/browser/ui/qorai_icon_with_badge_image_source.h"
#include "qorai/browser/ui/webui/qorai_shields/shields_panel_ui.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/url_constants.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/omnibox/omnibox_theme.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/ui/views/bubble/webui_bubble_manager.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/browser/ui/views/toolbar/toolbar_ink_drop_util.h"
#include "components/grit/qorai_components_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/url_constants.h"
#include "extensions/common/constants.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/base/models/image_model.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/color/color_provider_manager.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/skia_conversions.h"
#include "ui/gfx/image/image_skia_rep.h"
#include "ui/views/animation/ink_drop_impl.h"
#include "ui/views/controls/button/label_button_border.h"
#include "ui/views/controls/highlight_path_generator.h"
#include "ui/views/view.h"
#include "ui/views/view_class_properties.h"
#include "url/gurl.h"

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/ui/speedreader/speedreader_tab_helper.h"
#endif

namespace {
constexpr SkColor kBadgeBg = SkColorSetRGB(0x63, 0x64, 0x72);
class QoraiShieldsActionViewHighlightPathGenerator
    : public views::HighlightPathGenerator {
 public:
  QoraiShieldsActionViewHighlightPathGenerator() = default;
  QoraiShieldsActionViewHighlightPathGenerator(
      const QoraiShieldsActionViewHighlightPathGenerator&) = delete;
  QoraiShieldsActionViewHighlightPathGenerator& operator=(
      const QoraiShieldsActionViewHighlightPathGenerator&) = delete;
  ~QoraiShieldsActionViewHighlightPathGenerator() override = default;

  SkPath GetHighlightPath(const views::View* view) override {
    return static_cast<const QoraiShieldsActionView*>(view)->GetHighlightPath();
  }
};
}  // namespace

DEFINE_CLASS_ELEMENT_IDENTIFIER_VALUE(QoraiShieldsActionView,
                                      kShieldsActionIcon);

QoraiShieldsActionView::QoraiShieldsActionView(
    BrowserWindowInterface* browser_window_interface)
    : LabelButton(base::BindRepeating(&QoraiShieldsActionView::ButtonPressed,
                                      base::Unretained(this),
                                      browser_window_interface),
                  std::u16string()),
      browser_window_interface_(browser_window_interface),
      profile_(CHECK_DEREF(browser_window_interface->GetProfile())),
      tab_strip_model_(
          CHECK_DEREF(browser_window_interface->GetTabStripModel())) {
  auto* web_contents = tab_strip_model_->GetActiveWebContents();
  if (web_contents) {
    qorai_shields::QoraiShieldsTabHelper::FromWebContents(web_contents)
        ->AddObserver(this);
  }

  SetAccessibleName(l10n_util::GetStringUTF16(IDS_QORAI_SHIELDS));
  SetHorizontalAlignment(gfx::ALIGN_CENTER);
  SetProperty(views::kElementIdentifierKey, kShieldsActionIcon);
  tab_strip_model_->AddObserver(this);

  // The MenuButtonController makes sure the panel closes when clicked if the
  // panel is already open.
  auto menu_button_controller = std::make_unique<views::MenuButtonController>(
      this,
      base::BindRepeating(&QoraiShieldsActionView::ButtonPressed,
                          base::Unretained(this), browser_window_interface),
      std::make_unique<views::Button::DefaultButtonControllerDelegate>(this));
  menu_button_controller_ = menu_button_controller.get();
  SetButtonController(std::move(menu_button_controller));
}

QoraiShieldsActionView::~QoraiShieldsActionView() {
  auto* web_contents = tab_strip_model_->GetActiveWebContents();
  if (web_contents) {
    qorai_shields::QoraiShieldsTabHelper::FromWebContents(web_contents)
        ->RemoveObserver(this);
  }
}

void QoraiShieldsActionView::Init() {
  UpdateIconState();
  views::HighlightPathGenerator::Install(
      this, std::make_unique<QoraiShieldsActionViewHighlightPathGenerator>());
}

SkPath QoraiShieldsActionView::GetHighlightPath() const {
  // Set the highlight path for the toolbar button,
  // making it inset so that the badge can show outside it in the
  // fake margin on the right that we are creating.
  auto highlight_insets =
      gfx::Insets::TLBR(0, 0, 0, -1 * kQoraiActionLeftMarginExtra);
  gfx::Rect rect(GetPreferredSize());
  rect.Inset(highlight_insets);
  const int radii = ChromeLayoutProvider::Get()->GetCornerRadiusMetric(
      views::Emphasis::kHigh, rect.size());
  SkPath path;
  path.addRoundRect(gfx::RectToSkRect(rect), radii, radii);
  return path;
}

views::Widget* QoraiShieldsActionView::GetBubbleWidget() {
  if (!webui_bubble_manager_) {
    return nullptr;
  }
  return webui_bubble_manager_->GetBubbleWidget();
}

std::unique_ptr<IconWithBadgeImageSource>
QoraiShieldsActionView::GetImageSource() {
  auto preferred_size = GetPreferredSize();
  auto* web_contents = tab_strip_model_->GetActiveWebContents();

  auto get_color_provider_callback = base::BindRepeating(
      [](base::WeakPtr<content::WebContents> weak_web_contents) {
        const auto* const color_provider =
            weak_web_contents
                ? &weak_web_contents->GetColorProvider()
                : ui::ColorProviderManager::Get().GetColorProviderFor(
                      ui::NativeTheme::GetInstanceForNativeUi()
                          ->GetColorProviderKey(nullptr));
        return color_provider;
      },
      web_contents ? web_contents->GetWeakPtr()
                   : base::WeakPtr<content::WebContents>());

  std::unique_ptr<IconWithBadgeImageSource> image_source(
      new qorai::QoraiIconWithBadgeImageSource(
          preferred_size, std::move(get_color_provider_callback),
          GetLayoutConstant(LOCATION_BAR_TRAILING_ICON_SIZE),
          kQoraiActionLeftMarginExtra));
  std::unique_ptr<IconWithBadgeImageSource::Badge> badge;
  bool is_enabled = false;
  std::string badge_text;

  if (web_contents) {
    auto* shields_data_controller =
        qorai_shields::QoraiShieldsTabHelper::FromWebContents(web_contents);

    int count = shields_data_controller->GetTotalBlockedCount();
    if (count > 0) {
      badge_text = count > 99 ? "99+" : base::NumberToString(count);
    }

    is_enabled = shields_data_controller->GetQoraiShieldsEnabled() &&
                 !IsPageInReaderMode(web_contents);

    if (!badge_text.empty()) {
      badge = std::make_unique<IconWithBadgeImageSource::Badge>(
          badge_text, SK_ColorWHITE, kBadgeBg);
    }
  }

  image_source->SetIcon(gfx::Image(GetIconImage(is_enabled)));

  if (is_enabled &&
      profile_->GetPrefs()->GetBoolean(kShieldsStatsBadgeVisible)) {
    image_source->SetBadge(std::move(badge));
  }

  return image_source;
}

gfx::ImageSkia QoraiShieldsActionView::GetIconImage(bool is_enabled) {
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();
  gfx::ImageSkia image;
  const SkBitmap bitmap =
      rb.GetImageNamed(is_enabled ? IDR_QORAI_SHIELDS_ICON_64
                                  : IDR_QORAI_SHIELDS_ICON_64_DISABLED)
          .AsBitmap();
  float scale = static_cast<float>(bitmap.width()) /
                GetLayoutConstant(LOCATION_BAR_TRAILING_ICON_SIZE);
  image.AddRepresentation(gfx::ImageSkiaRep(bitmap, scale));
  return image;
}

void QoraiShieldsActionView::UpdateIconState() {
  const gfx::ImageSkia icon(GetImageSource(), GetPreferredSize());
  // Use badge-and-icon source for button's image in all states
  SetImageModel(views::Button::STATE_NORMAL,
                ui::ImageModel::FromImageSkia(icon));
}

void QoraiShieldsActionView::ButtonPressed(
    BrowserWindowInterface* browser_window_interface) {
  auto* web_content = tab_strip_model_->GetActiveWebContents();
  if (!ShouldShowBubble(web_content)) {
    return;
  }

  if (webui_bubble_manager_ && webui_bubble_manager_->GetBubbleWidget()) {
    webui_bubble_manager_->CloseBubble();
    return;
  }

  ShowBubble(GURL(kShieldsPanelURL));
}

bool QoraiShieldsActionView::IsPageInReaderMode(
    content::WebContents* web_contents) {
  if (!web_contents) {
    return false;
  }
#if BUILDFLAG(ENABLE_SPEEDREADER)
  if (auto* speedreader_tab_helper =
          speedreader::SpeedreaderTabHelper::FromWebContents(web_contents)) {
    return speedreader::DistillStates::IsDistilled(
        speedreader_tab_helper->PageDistillState());
  }
#endif
  return false;
}

void QoraiShieldsActionView::ShowBubble(GURL webui_url) {
  if (!webui_bubble_manager_ || webui_url != last_webui_url_) {
    webui_bubble_manager_ = WebUIBubbleManager::Create<ShieldsPanelUI>(
        this, browser_window_interface_, webui_url, IDS_QORAI_SHIELDS);
  }
  last_webui_url_ = webui_url;

  webui_bubble_manager_->ShowBubble();
}

bool QoraiShieldsActionView::ShouldShowBubble(
    content::WebContents* web_contents) {
  if (!web_contents) {
    return false;
  }
  const GURL& url = web_contents->GetLastCommittedURL();

  if (url.SchemeIs(url::kAboutScheme) || url.SchemeIs(url::kBlobScheme) ||
      url.SchemeIs(url::kDataScheme) || url.SchemeIs(url::kFileSystemScheme) ||
      url.SchemeIs(kMagnetScheme) || url.SchemeIs(kQoraiUIScheme) ||
      url.SchemeIs(content::kChromeUIScheme) ||
      url.SchemeIs(extensions::kExtensionScheme)) {
    // Do not show bubble if it's a local scheme
    return false;
  }

  if (IsPageInReaderMode(web_contents)) {
    // Do not show bubble on speedreader pages.
    return false;
  }

  return true;
}

std::unique_ptr<views::LabelButtonBorder>
QoraiShieldsActionView::CreateDefaultBorder() const {
  std::unique_ptr<views::LabelButtonBorder> border =
      LabelButton::CreateDefaultBorder();
  border->set_insets(gfx::Insets::TLBR(0, 0, 0, 0));
  return border;
}

std::u16string QoraiShieldsActionView::GetRenderedTooltipText(
    const gfx::Point& p) const {
  auto* web_contents = tab_strip_model_->GetActiveWebContents();

  if (web_contents) {
    auto* shields_data_controller =
        qorai_shields::QoraiShieldsTabHelper::FromWebContents(web_contents);

    int count = shields_data_controller->GetTotalBlockedCount();

    if (count > 0) {
      return l10n_util::GetStringFUTF16Int(IDS_QORAI_SHIELDS_ICON_TOOLTIP,
                                           count);
    }
  }

  return l10n_util::GetStringUTF16(IDS_QORAI_SHIELDS);
}

void QoraiShieldsActionView::OnThemeChanged() {
  LabelButton::OnThemeChanged();

  const auto* const color_provider = GetColorProvider();
  if (!color_provider) {
    return;
  }

  // Apply same ink drop effect with location bar's other icon views.
  auto* ink_drop = views::InkDrop::Get(this);
  ink_drop->SetMode(views::InkDropHost::InkDropMode::ON);
  SetHasInkDropActionOnClick(true);
  views::InkDrop::Get(this)->SetVisibleOpacity(kOmniboxOpacitySelected);
  views::InkDrop::Get(this)->SetHighlightOpacity(kOmniboxOpacityHovered);
  ink_drop->SetBaseColor(color_provider->GetColor(kColorOmniboxText));
}

void QoraiShieldsActionView::Update() {
  UpdateIconState();
}

void QoraiShieldsActionView::OnResourcesChanged() {
  UpdateIconState();
}

void QoraiShieldsActionView::OnShieldsEnabledChanged() {
  UpdateIconState();
}

void QoraiShieldsActionView::OnRepeatedReloadsDetected() {
  auto* web_content = tab_strip_model_->GetActiveWebContents();
  if (!ShouldShowBubble(web_content)) {
    return;
  }

  ShowBubble(
      GURL(std::string(kShieldsPanelURL) + "?mode=afterRepeatedReloads"));
}

void QoraiShieldsActionView::OnTabStripModelChanged(
    TabStripModel* tab_strip_model,
    const TabStripModelChange& change,
    const TabStripSelectionChange& selection) {
  if (selection.active_tab_changed()) {
    if (selection.new_contents) {
      qorai_shields::QoraiShieldsTabHelper::FromWebContents(
          selection.new_contents)
          ->AddObserver(this);
    }

    if (selection.old_contents) {
      qorai_shields::QoraiShieldsTabHelper::FromWebContents(
          selection.old_contents)
          ->RemoveObserver(this);
    }
    UpdateIconState();
  }
}

BEGIN_METADATA(QoraiShieldsActionView)
END_METADATA
