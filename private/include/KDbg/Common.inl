// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#pragma once

#include <KDbg/Detail/Config.h>
#include <KDbg/ANT.h>

#define kBlank "\e[0;30m"
#define kRed "\e[0;31m"
#define kWhite "\e[0;97m"

#define kStdOut (std::cout << kRed << "kdbg: " << kWhite)

inline bool kKeepRunning = false;

inline KDbg::ANT::IKrnlDebugger kKernelDebugger;

inline KDbg::ProcessID kPID           = 0L;

inline KDbg::CAddress  kActiveAddress = nullptr;

inline Tier0Kit::STLString     kPath          = "";
