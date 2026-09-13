// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#define kBlank "\e[0;30m"
#define kRed "\e[0;31m"
#define kWhite "\e[0;97m"

#define kStdOut (std::cout << kRed << "kdbg: " << kWhite)

inline bool kKeepRunning = false;

#ifdef DK_KRNL_DEBUGGER
inline DebuggerKit::ANT::IKrnlDebugger kKernelDebugger;
#endif

inline DebuggerKit::ProcessID kPID           = 0L;
inline DebuggerKit::CAddress  kActiveAddress = nullptr;
inline Tier0Kit::STLString     kPath          = "";
