// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "Chiika/renderer/client_app_renderer.h"
#include "Chiika/renderer/client_renderer.h"
#include "Chiika/renderer/performance_test.h"
#include "Chiika/renderer/chiika_renderer_delegate.h"

namespace client {

// static
void ClientAppRenderer::CreateDelegates(DelegateSet& delegates) {
  renderer::CreateDelegates(delegates);
  performance_test::CreateDelegates(delegates);
  Chiika::CreateDelegates(delegates);
}

}  // namespace client
