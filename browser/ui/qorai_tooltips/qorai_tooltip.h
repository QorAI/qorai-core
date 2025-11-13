/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_TOOLTIPS_QORAI_TOOLTIP_H_
#define QORAI_BROWSER_UI_QORAI_TOOLTIPS_QORAI_TOOLTIP_H_

#include <string>
#include <utility>

#include "base/check.h"
#include "base/memory/weak_ptr.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_attributes.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_delegate.h"

namespace qorai_tooltips {

class QoraiTooltip {
 public:
  // Create a new tooltip with an |id| and |attributes|.  |delegate|
  // will influence the behaviour of this tooltip and receives events
  // on its behalf. The delegate may be omitted
  QoraiTooltip(const std::string& id,
               const QoraiTooltipAttributes& attributes,
               base::WeakPtr<QoraiTooltipDelegate> delegate);
  virtual ~QoraiTooltip();

  QoraiTooltip(const QoraiTooltip&) = delete;
  QoraiTooltip& operator=(const QoraiTooltip&) = delete;

  const std::string& id() const { return id_; }

  const QoraiTooltipAttributes& attributes() const { return attributes_; }
  void set_attributes(const QoraiTooltipAttributes& attributes) {
    attributes_ = attributes;
  }

  std::u16string accessible_name() const;

  QoraiTooltipDelegate* delegate() const { return delegate_.get(); }

  void set_delegate(base::WeakPtr<QoraiTooltipDelegate> delegate) {
    DCHECK(!delegate_);
    delegate_ = std::move(delegate);
  }

  virtual void PerformOkButtonAction() {}
  virtual void PerformCancelButtonAction() {}

 protected:
  std::string id_;
  QoraiTooltipAttributes attributes_;

 private:
  base::WeakPtr<QoraiTooltipDelegate> delegate_;
};

}  // namespace qorai_tooltips

#endif  // QORAI_BROWSER_UI_QORAI_TOOLTIPS_QORAI_TOOLTIP_H_
