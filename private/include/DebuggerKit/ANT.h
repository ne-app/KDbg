// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#ifndef DK_KRNL_CONTRACT_H
#define DK_KRNL_CONTRACT_H

/// @brief ANT Debugging Protocol
/// @author Amlal El Mahrouss

#ifdef DK_KRNL_DEBUGGER

#include <Tier0Kit/Detail/Config.h>
#include <DebuggerKit/IDebugger.h>

namespace DebuggerKit::ANT {

class KrnlDebugger;

/// =========================================================== ///
/// \brief ANT Debugger Contract for its debugging.
/// \author Amlal El Mahrouss
/// =========================================================== ///
class KrnlDebugger DK_DEBUGGER_CONTRACT {
 public:
  KrnlDebugger();
  virtual ~KrnlDebugger() override;

 public:
  KrnlDebugger& operator=(const KrnlDebugger&) = default;
  KrnlDebugger(const KrnlDebugger&)            = default;

 public:
  bool Attach(const Tier0Kit::STLString& path, const Tier0Kit::STLString& arg_v,
              ProcessID& pid) noexcept override;
  bool BreakAt(const Tier0Kit::STLString& symbol) noexcept override;
  bool Break() noexcept override;
  bool Continue() noexcept override;
  bool Detach() noexcept override;

 private:
  Tier0Kit::STLString m_kernel_path{};
  Detail::dk_socket_type m_socket{0};
};

}  // namespace DebuggerKit::ANT

#endif  // ifdef DK_KRNL_DEBUGGER

#endif  // DK_KRNL_CONTRACT_H
