// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "chrome/browser/ui/views/profiles/avatar_toolbar_button_state_manager.h"

#include "qorai/app/vector_icons/vector_icons.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "chrome/browser/profiles/profile.h"

namespace {

// Creates a Qorai-specific state provider for the avatar toolbar button.
// Please see comments on IsRegularProfile() override for more details.
std::unique_ptr<StateProvider> CreateQoraiStateProvider(
    Profile* profile,
    StateObserver* state_observer);

}  // namespace

// Overrides profile->IsRegularProfile() in CreateStatesAndListeners() to
// customize state provider for Tor, Incognito, and Guest profiles.
// StateProvider provides data to visualize the avatar toolbar button's state
// according to various situations. But Qorai has specific requirements for
// Tor, Incognito, and Guest profiles to show different icons for these. So
// in these cases, we use Qorai-specific state providers and do not add any
// other state providers.
// Note that in these cases, we don't add any other state providers than the
// Qorai-specific ones. This is because we don't show any other state in those
// profiles. i.e., we don't have special avatar button for "signed-in", "sync
// error", and etc for these profiles.
#define IsRegularProfile()                                                 \
  IsTor() || profile->IsIncognitoProfile() || profile->IsGuestSession()) { \
    states_[ButtonState::kNormal] =                                        \
        CreateQoraiStateProvider(profile, /*state_observer=*/this);        \
    return;                                                                \
  }                                                                        \
  if (profile->IsRegularProfile()

#include <chrome/browser/ui/views/profiles/avatar_toolbar_button_state_manager.cc>

#undef IsRegularProfile

namespace {

// Qorai-specific state providers for the avatar toolbar button. Customizes
// icons and tooltip texts for Tor, Incognito, and Guest profiles.

// QoraiTorStateProvider is used for Tor profiles. As Tor profile is a special
// case of Qorai, we need to provide a icon and tooltip text for this.
class QoraiTorStateProvider : public PrivateBaseStateProvider {
 public:
  QoraiTorStateProvider(Profile* profile, StateObserver* state_observer)
      : PrivateBaseStateProvider(profile, state_observer) {}

  // PrivateBaseStateProvider:
  ui::ImageModel GetAvatarIcon(
      int icon_size,
      SkColor icon_color,
      const ui::ColorProvider& color_provider) const override {
    return ui::ImageModel::FromVectorIcon(
        kQoraProductTorIcon, SkColorSetRGB(0x3C, 0x82, 0x3C), icon_size);
  }

  std::u16string GetText() const override {
    return l10n_util::GetStringUTF16(IDS_TOR_AVATAR_BUTTON_TOOLTIP_TEXT);
  }
};

// QoraiIncognitoStateProvider is used for Incognito profiles to override
// Chromium's default icon for the profile
class QoraiIncognitoStateProvider : public IncognitoStateProvider {
 public:
  QoraiIncognitoStateProvider(Profile* profile, StateObserver* state_observer)
      : IncognitoStateProvider(profile, state_observer) {}

  // IncognitoStateProvider:
  ui::ImageModel GetAvatarIcon(
      int icon_size,
      SkColor icon_color,
      const ui::ColorProvider& color_provider) const override {
    return ui::ImageModel::FromVectorIcon(
        kIncognitoIcon, SkColorSetRGB(0xFF, 0xFF, 0xFF), icon_size);
  }
};

// QoraiGuestStateProvider is used for Guest sessions to override Chromium's
// default icon for the guest sessions.
class QoraiGuestStateProvider : public GuestStateProvider {
 public:
  QoraiGuestStateProvider(Profile* profile, StateObserver* state_observer)
      : GuestStateProvider(profile, state_observer) {}

  // GuestStateProvider:
  ui::ImageModel GetAvatarIcon(
      int icon_size,
      SkColor icon_color,
      const ui::ColorProvider& color_provider) const override {
    return ui::ImageModel::FromVectorIcon(kUserMenuGuestIcon, icon_color,
                                          icon_size);
  }
};

std::unique_ptr<StateProvider> CreateQoraiStateProvider(
    Profile* profile,
    StateObserver* state_observer) {
  if (profile->IsTor()) {
    return std::make_unique<QoraiTorStateProvider>(profile, state_observer);
  }
  if (profile->IsIncognitoProfile()) {
    return std::make_unique<QoraiIncognitoStateProvider>(profile,
                                                         state_observer);
  }
  if (profile->IsGuestSession()) {
    return std::make_unique<QoraiGuestStateProvider>(profile, state_observer);
  }

  NOTREACHED() << "Unsupported profile type for QoraiStateProvider";
}

}  // namespace
