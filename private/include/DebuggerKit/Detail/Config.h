// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#ifndef TIER0KIT_DEBUGGERKIT_DETAIL_CONFIG_H
#define TIER0KIT_DEBUGGERKIT_DETAIL_CONFIG_H

/// =========================================================== ///
/// @author Amlal El Mahrouss
/// =========================================================== ///

#include <Tier0Kit/Detail/Config.h>

#ifndef DEBUGGERKIT_WINDOWS
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#ifdef DEBUGGERKIT_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include <unordered_map>

#ifdef __APPLE__
#include <dlfcn.h>

#include <mach-o/dyld.h>
#include <mach/mach.h>
#include <mach/mach_error.h>
#endif

#ifndef kDistRelease

#define kDistVersion "v0.1.3-debuggerkit"
#define kDistVersionBCD 0x0103

#define ToString(X) Stringify(X)
#define Stringify(X) #X

#define kDistRelease ToString(kDistReleaseBranch)

#endif  // !kDistRelease

namespace DebuggerKit {
/// =========================================================== ///
/// \brief Process ID
/// =========================================================== ///
typedef uint64_t ProcessID;

/// =========================================================== ///
/// \brief Address type, a la BSD.
/// =========================================================== ///
typedef char* CAddress;

/// @note This is an open protocol; it is updated accordingly to Ant latest specs here.
namespace Detail {
  constexpr auto     kDebugCmdLen  = 256U;
  constexpr auto     kDebugPort    = 51820;
  constexpr auto     kDebugMagic   = "AN1.0.1;";
  constexpr uint16_t kDebugVersion = 0x0101;
  constexpr auto     kDebugDelim   = ';';
  constexpr auto     kDebugEnd     = '\r';
  
  using dk_socket_type             = int64_t;
}  // namespace Detail
}  // namespace DebuggerKit

#endif  // TIER0KIT_DEBUGGERKIT_DETAIL_CONFIG_H
