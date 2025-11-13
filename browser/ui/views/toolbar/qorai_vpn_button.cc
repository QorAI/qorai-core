/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/toolbar/qorai_vpn_button.h"

#include <optional>
#include <utility>

#include "base/check.h"
#include "base/memory/raw_ptr.h"
#include "qorai/app/qorai_command_ids.h"
#include "qorai/app/vector_icons/vector_icons.h"
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/ui/qorai_icon_with_badge_image_source.h"
#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/color/chrome_color_id.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/browser/ui/views/toolbar/toolbar_ink_drop_util.h"
#include "components/grit/qorai_components_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/compositor/layer.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/color_utils.h"
#include "ui/gfx/geometry/rect_f.h"
#include "ui/gfx/geometry/rrect_f.h"
#include "ui/gfx/paint_vector_icon.h"
#include "ui/gfx/skia_util.h"
#include "ui/menus/simple_menu_model.h"
#include "ui/views/animation/ink_drop.h"
#include "ui/views/animation/ink_drop_host.h"
#include "ui/views/background.h"
#include "ui/views/border.h"
#include "ui/views/controls/highlight_path_generator.h"

using ConnectionState = qorai_vpn::mojom::ConnectionState;
using PurchasedState = qorai_vpn::mojom::PurchasedState;

namespace {

constexpr int kBadgeSize = 10;

// For error icon's inner color.
class ConnectErrorIconBackground : public views::Background {
 public:
  explicit ConnectErrorIconBackground(SkColor color) { SetColor(color); }

  ConnectErrorIconBackground(const ConnectErrorIconBackground&) = delete;
  ConnectErrorIconBackground& operator=(const ConnectErrorIconBackground&) =
      delete;

  void Paint(gfx::Canvas* canvas, views::View* view) const override {
    auto bounds = view->GetLocalBounds();
    bounds.Inset(gfx::Insets::TLBR(2, 4, 2, 4));
    canvas->FillRect(bounds,
                     color().ResolveToSkColor(view->GetColorProvider()));
  }
};

class VPNButtonMenuModel : public ui::SimpleMenuModel,
                           public ui::SimpleMenuModel::Delegate,
                           public qorai_vpn::QoraiVPNServiceObserver {
 public:
  explicit VPNButtonMenuModel(Browser* browser)
      : SimpleMenuModel(this),
        browser_(browser),
        service_(qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
            browser_->profile())) {
    CHECK(service_);
    Observe(service_);
    Build(service_->is_purchased_user());
  }

  ~VPNButtonMenuModel() override = default;
  VPNButtonMenuModel(const VPNButtonMenuModel&) = delete;
  VPNButtonMenuModel& operator=(const VPNButtonMenuModel&) = delete;

 private:
  // ui::SimpleMenuModel::Delegate override:
  void ExecuteCommand(int command_id, int event_flags) override {
    chrome::ExecuteCommand(browser_, command_id);
  }

  // QoraiVPNServiceObserver overrides:
  void OnPurchasedStateChanged(
      qorai_vpn::mojom::PurchasedState state,
      const std::optional<std::string>& description) override {
    // Rebuild menu items based on purchased state change.
    Build(service_->is_purchased_user());
  }

  void Build(bool purchased) {
    // Clear all menu items and re-build as purchased state can be updated
    // during the runtime.
    Clear();
    AddItemWithStringId(IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON,
                        IDS_QORAI_VPN_HIDE_VPN_BUTTON_MENU_ITEM);
    if (purchased) {
      AddItemWithStringId(IDC_SEND_QORAI_VPN_FEEDBACK,
                          IDS_QORAI_VPN_SHOW_FEEDBACK_MENU_ITEM);
      AddItemWithStringId(IDC_ABOUT_QORAI_VPN,
                          IDS_QORAI_VPN_ABOUT_VPN_MENU_ITEM);
      AddItemWithStringId(IDC_MANAGE_QORAI_VPN_PLAN,
                          IDS_QORAI_VPN_MANAGE_MY_PLAN_MENU_ITEM);
    }
  }

  raw_ptr<Browser, DanglingUntriaged> browser_ = nullptr;
  raw_ptr<qorai_vpn::QoraiVpnService, DanglingUntriaged> service_ = nullptr;
};

const ui::ColorProvider* GetColorProviderForView(
    base::WeakPtr<QoraiVPNButton> view) {
  if (view) {
    return view->GetColorProvider();
  }

  return ui::ColorProviderManager::Get().GetColorProviderFor(
      ui::NativeTheme::GetInstanceForNativeUi()->GetColorProviderKey(nullptr));
}

// An image with custom badge image(not text).
class QoraiVPNBadgeImageSource : public qorai::QoraiIconWithBadgeImageSource {
 public:
  QoraiVPNBadgeImageSource(const gfx::Size& image_size,
                           int icon_size,
                           GetColorProviderCallback get_color_provider_callback,
                           const gfx::VectorIcon& badge_icon,
                           SkColor badge_icon_color)
      : QoraiIconWithBadgeImageSource(image_size,
                                      std::move(get_color_provider_callback),
                                      icon_size,
                                      /* image_left_margin_extra */ 0),
        badge_icon_(badge_icon),
        badge_icon_color_(badge_icon_color) {
    // true as this image is for badge with image not text.
    SetAllowEmptyText(true);
  }

 private:
  // qorai::QoraiIconWithBadgeImageSource:
  void PaintBadgeWithoutText(const gfx::Rect& badge_rect,
                             gfx::Canvas* canvas) override {
    auto image =
        gfx::CreateVectorIcon(*badge_icon_, kBadgeSize, badge_icon_color_);
    cc::PaintFlags image_flags;
    image_flags.setStyle(cc::PaintFlags::kFill_Style);
    image_flags.setAntiAlias(true);

    // badge is located at the right bottom of image area.
    const int x_offset = size().width() - kBadgeSize;
    const int y_offset = size().height() - kBadgeSize;
    canvas->DrawImageInt(image, x_offset, y_offset, image_flags);
  }

  raw_ref<const gfx::VectorIcon> badge_icon_;
  SkColor badge_icon_color_ = SK_ColorTRANSPARENT;
};

}  // namespace

QoraiVPNButton::QoraiVPNButton(Browser* browser)
    : ToolbarButton(base::BindRepeating(&QoraiVPNButton::OnButtonPressed,
                                        base::Unretained(this)),
                    std::make_unique<VPNButtonMenuModel>(browser),
                    nullptr,
                    false),  // Long-pressing is not intended for something that
                             // already shows a panel on click
      browser_(browser),
      service_(qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
          browser_->profile())) {
  CHECK(service_);
  UpdateButtonState();
  Observe(service_);

  // The MenuButtonController makes sure the panel closes when clicked if the
  // panel is already open.
  auto menu_button_controller = std::make_unique<views::MenuButtonController>(
      this,
      base::BindRepeating(&QoraiVPNButton::OnButtonPressed,
                          base::Unretained(this)),
      std::make_unique<views::Button::DefaultButtonControllerDelegate>(this));
  menu_button_controller_ = menu_button_controller.get();
  SetButtonController(std::move(menu_button_controller));
  SetAccessibleName(
      l10n_util::GetStringUTF16(IDS_QORAI_VPN_TOOLBAR_BUTTON_TEXT));
}

QoraiVPNButton::~QoraiVPNButton() = default;

void QoraiVPNButton::OnConnectionStateChanged(ConnectionState state) {
  if (IsErrorState() && (state == ConnectionState::CONNECTING ||
                         state == ConnectionState::DISCONNECTING)) {
    // Skip attempts to connect/disconnet if we had an error before and keep
    // the button in the error state until we get it clearly fixed.
    return;
  }
  UpdateButtonState();
  UpdateColorsAndInsets();
}

void QoraiVPNButton::UpdateButtonState() {
  is_error_state_ = IsConnectError();
  is_connected_ = IsConnected();
}

void QoraiVPNButton::OnPurchasedStateChanged(
    qorai_vpn::mojom::PurchasedState state,
    const std::optional<std::string>& description) {
  UpdateButtonState();
  UpdateColorsAndInsets();
}

std::unique_ptr<views::Border> QoraiVPNButton::GetBorder(
    SkColor border_color) const {
  constexpr auto kTargetInsets = gfx::Insets::VH(6, 8);
  constexpr auto kBorderThickness = 1;
  const int radius = ChromeLayoutProvider::Get()->GetCornerRadiusMetric(
      views::Emphasis::kMaximum, {});
  std::unique_ptr<views::Border> border = views::CreateRoundedRectBorder(
      kBorderThickness, radius, gfx::Insets(), border_color);
  const gfx::Insets extra_insets = kTargetInsets - border->GetInsets();
  return views::CreatePaddedBorder(std::move(border), extra_insets);
}

void QoraiVPNButton::UpdateColorsAndInsets() {
  ui::ColorProvider* cp = GetColorProvider();
  if (!cp) {
    return;
  }

  const auto bg_color =
      cp->GetColor(is_error_state_ ? kColorQoraiVpnButtonErrorBackgroundNormal
                                   : kColorQoraiVpnButtonBackgroundNormal);
  const int radius = ChromeLayoutProvider::Get()->GetCornerRadiusMetric(
      views::Emphasis::kMaximum, {});
  SetBackground(views::CreateRoundedRectBackground(bg_color, radius));

  constexpr gfx::Size kImageSizeWithBadge(22, 24);
  const int button_size = GetLayoutConstant(TOOLBAR_BUTTON_HEIGHT);
  const auto size_diff =
      gfx::Size(button_size, button_size) - kImageSizeWithBadge;

  // Outside of image should be filled with border.
  SetBorder(views::CreateEmptyBorder(
      gfx::Insets::VH(size_diff.height() / 2, size_diff.width() / 2)));
  auto image_source = std::make_unique<QoraiVPNBadgeImageSource>(
      kImageSizeWithBadge, GetIconSize(),
      base::BindRepeating(&GetColorProviderForView,
                          weak_ptr_factory_.GetWeakPtr()),
      GetBadgeIcon(), GetBadgeColor());

  if (IsPurchased()) {
    // Don't need to have text badge here but custom badge is not painted
    // if it's null. Set dummy badge.
    image_source->SetBadge(std::make_unique<IconWithBadgeImageSource::Badge>(
        std::string(), gfx::kPlaceholderColor, gfx::kPlaceholderColor));
  }
  image_source->SetIcon(gfx::Image(gfx::CreateVectorIcon(
      kQoraProductVpnIcon, GetIconSize(), GetIconColor())));
  SetImageModel(views::Button::STATE_NORMAL,
                ui::ImageModel::FromImageSkia(gfx::ImageSkia(
                    std::move(image_source), kImageSizeWithBadge)));
}

SkColor QoraiVPNButton::GetIconColor() {
  ui::ColorProvider* cp = GetColorProvider();
  CHECK(cp);

  if (is_error_state_) {
    return cp->GetColor(kColorQoraiVpnButtonIconError);
  }

  const auto ink_drop_state =
      views::InkDrop::Get(this)->GetInkDrop()->GetTargetInkDropState();
  ui::ColorId icon_color_id = kColorToolbarButtonIcon;
  if (ink_drop_state == views::InkDropState::ACTIVATED) {
    icon_color_id = kColorToolbarButtonActivated;
  }

  return cp->GetColor(icon_color_id);
}

SkColor QoraiVPNButton::GetBadgeColor() {
  ui::ColorProvider* cp = GetColorProvider();
  CHECK(cp);

  if (is_error_state_) {
    return cp->GetColor(kColorQoraiVpnButtonIconError);
  }

  return cp->GetColor(is_connected_ ? kColorQoraiVpnButtonIconConnected
                                    : kColorQoraiVpnButtonIconDisconnected);
}

const gfx::VectorIcon& QoraiVPNButton::GetBadgeIcon() {
  if (is_error_state_) {
    return kVpnIndicatorErrorIcon;
  }

  return is_connected_ ? kVpnIndicatorOnIcon : kVpnIndicatorOffIcon;
}

std::u16string QoraiVPNButton::GetRenderedTooltipText(
    const gfx::Point& p) const {
  if (!IsPurchased()) {
    return l10n_util::GetStringUTF16(IDS_QORAI_VPN);
  }

  return l10n_util::GetStringUTF16(IsConnected()
                                       ? IDS_QORAI_VPN_CONNECTED_TOOLTIP
                                       : IDS_QORAI_VPN_DISCONNECTED_TOOLTIP);
}

void QoraiVPNButton::OnThemeChanged() {
  ToolbarButton::OnThemeChanged();

  // Configure vpn button specific ink drop config as ink drop is reset
  // whenever theme changes.

  // Set 0.0f to use same color for activated state.
  views::InkDrop::Get(this)->SetVisibleOpacity(0.00f);

  // Different base color is set per themes and it has alpha.
  views::InkDrop::Get(this)->SetHighlightOpacity(1.0f);

  UpdateColorsAndInsets();
}

void QoraiVPNButton::InkDropRippleAnimationEnded(views::InkDropState state) {
  // To use different icon color when activated.
  UpdateColorsAndInsets();
}

bool QoraiVPNButton::IsConnected() const {
  return service_->IsConnected();
}

ConnectionState QoraiVPNButton::GetVpnConnectionState() const {
  if (connection_state_for_testing_) {
    return connection_state_for_testing_.value();
  }
  return service_->GetConnectionState();
}

bool QoraiVPNButton::IsConnectError() const {
  const auto state = GetVpnConnectionState();
  return (state == ConnectionState::CONNECT_NOT_ALLOWED ||
          state == ConnectionState::CONNECT_FAILED);
}

bool QoraiVPNButton::IsPurchased() const {
  return service_->is_purchased_user();
}
void QoraiVPNButton::OnButtonPressed(const ui::Event& event) {
  chrome::ExecuteCommand(browser_, IDC_SHOW_QORAI_VPN_PANEL);
}

BEGIN_METADATA(QoraiVPNButton)
END_METADATA
