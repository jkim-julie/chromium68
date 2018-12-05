// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_FAKE_CLIPBOARD_DELEGATE_H_
#define UI_OZONE_PUBLIC_FAKE_CLIPBOARD_DELEGATE_H_

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_refptr.h"
#include "ui/ozone/public/clipboard_delegate.h"

namespace ui {

// Fake clipboard delegate, which just stores offered clipboard data and sends
// it back on requests. It's created automatically if ozone platforms do not
// implement and create ClipboardDelegate.
class FakeClipboardDelegate : public ClipboardDelegate {
 public:
  FakeClipboardDelegate();
  ~FakeClipboardDelegate() override;

  void OfferClipboardData(const DataMap& data_map,
                          OfferDataClosure callback) override;
  void RequestClipboardData(const std::string& mime_type,
                            DataMap* data_map,
                            RequestDataClosure callback) override;
  void GetAvailableMimeTypes(GetMimeTypesClosure callback) override;
  bool IsSelectionOwner() override;

 private:
  ClipboardDelegate::DataMap offered_data_map_;

  DISALLOW_COPY_AND_ASSIGN(FakeClipboardDelegate);
};

}  // namespace ui

#endif  // UI_OZONE_PUBLIC_CLIPBOARD_DELEGATE_H_
