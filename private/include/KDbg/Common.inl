// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#pragma once

#include <KDbg/ANT.h>
#include <KDbg/Detail/Config.h>

#define kStdOut (std::cout << "kdbg: ")

inline bool kKeepRunning = false;

inline KDbg::ANT::IKrnlDebugger kKernelDebugger;

inline KDbg::ProcessID kPID = 0L;

inline KDbg::CAddress kActiveAddress = nullptr;

inline Tier0Kit::STLString kPath = "";
