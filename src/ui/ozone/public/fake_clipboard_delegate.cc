// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/ozone/public/fake_clipboard_delegate.h"

namespace ui {

FakeClipboardDelegate::FakeClipboardDelegate() = default;

FakeClipboardDelegate::~FakeClipboardDelegate() = default;

void FakeClipboardDelegate::OfferClipboardData(const DataMap& data_map,
                                               OfferDataClosure callback) {
  offered_data_map_ = data_map;
  std::move(callback).Run();
}

void FakeClipboardDelegate::RequestClipboardData(const std::string& mime_type,
                                                 DataMap* data_map,
                                                 RequestDataClosure callback) {
  auto it = offered_data_map_.find(mime_type);
  if (it == offered_data_map_.end()) {
    std::move(callback).Run(base::Optional<ClipboardDelegate::Data>());
    return;
  }
  *data_map = offered_data_map_;
  std::move(callback).Run(std::move(it->second));
}

void FakeClipboardDelegate::GetAvailableMimeTypes(
    GetMimeTypesClosure callback) {
  std::vector<std::string> mime_types;
  for (const auto& item : offered_data_map_) {
    mime_types.push_back(item.first);
  }
  std::move(callback).Run(std::move(mime_types));
}

bool FakeClipboardDelegate::IsSelectionOwner() {
  return !offered_data_map_.empty();
}

}  // namespace ui
