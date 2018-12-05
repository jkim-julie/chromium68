// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/ozone/public/clipboard_delegate.h"

#include "ui/ozone/public/fake_clipboard_delegate.h"

namespace ui {

namespace {

ClipboardDelegate* g_delegate_instance = nullptr;

}  // namespace

ClipboardDelegate::ClipboardDelegate() {
  DCHECK(!g_delegate_instance)
      << "Only one instance of ClipboardDelegate is allowed.";
  g_delegate_instance = this;
}

ClipboardDelegate::~ClipboardDelegate() {
  DCHECK_EQ(g_delegate_instance, this);
  g_delegate_instance = nullptr;
}

ClipboardDelegate* ClipboardDelegate::GetInstance() {
  if (!g_delegate_instance) {
    LOG(ERROR) << "No ClipboardDelegate is available. Falling back to "
                  "FakeClipboardDelegate. Please note that each Ozone platform "
                  "must provide own ClipboardDelegate implementations in order "
                  "to be able to communicate with a system clipboard.";
    std::unique_ptr<FakeClipboardDelegate> delegate =
        std::make_unique<FakeClipboardDelegate>();
    CHECK(g_delegate_instance) << "Unable to create fake clipboard delegate";
    delegate.release();
  }
  return g_delegate_instance;
}

}  // namespace ui
