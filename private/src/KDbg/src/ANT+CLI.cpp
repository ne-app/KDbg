// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#ifdef DK_KRNL_DEBUGGER

#include <KDbg/ANT.h>
#include <ThirdParty/Dialogs/Dialogs.h>
#include <ThirdParty/XML/XML.h>

#ifndef kStdOut
#define kStdOut (std::cout << "kdbg: ")
#endif

using namespace ::KDbg::ANT;

static bool kKeepRunning = false;

static IKrnlDebugger kKernelDebugger;

static KDbg::ProcessID kPID = 0L;

static KDbg::CAddress kActiveAddress = nullptr;

static Tier0Kit::STLString kProgPath = "";

static void dbgi_ctrlc_handler(std::int32_t) {
  if (!kPID || kProgPath.empty()) return;

  kKernelDebugger.Break();

  pfd::notify("ANT Event", "Breakpoint hit!\nWaiting for input...");

  kKeepRunning = false;
}

TIER0KIT_MODULE(DebuggerAnt) {
  pfd::notify("ANT Event",
              "ANT Kernel Debugger\n(C) 2025-2026 Ne.app, all "
              "rights reserved.");

  KDbg::INavHintsDelegate del;

  if (strcmp(argv[1], "--Xmanifest") == 0 && del.Load(argv[2])) {
    kProgPath = del.Pragma("SystemURI");
    kProgPath += ":";
    kProgPath += del.Pragma("SystemPort");
    kProgPath += "?macro=" + del.Pragma("PreprocessorMacro");
    kProgPath += "&img_type=" + del.Pragma("ImageType");
    kProgPath += "&img_arr=";

    auto img = del.Images();

    for (const auto& imgs : img) {
      kProgPath += imgs.url;
      kProgPath += "%20";
    }

    kStdOut << "[+] KIP (Kernel:IP) set to: " << kProgPath << "\n";

    Tier0Kit::t0_install_signal(SIGINT, dbgi_ctrlc_handler);

    kKernelDebugger.Attach(kProgPath, del.Pragma("SystemCopyPath"), kPID);

    while (YES) {
      if (kKeepRunning) {
        continue;
      }

      std::string cmd;
      if (!std::getline(std::cin, cmd)) break;

      if (cmd == "c" || cmd == "cont" || cmd == "continue") {
        if (kKernelDebugger.Continue()) {
          kKeepRunning = true;

          kStdOut << "[+] Continuing...\n";

          pfd::notify("ANT Kernel Debugger Event", "Continuing...");
        }
      }

      if (cmd == "d" || cmd == "detach") kKernelDebugger.Detach();

      if (cmd == "start") {
        kStdOut << "[?] Enter a argument to use: ";
        std::getline(std::cin, cmd);

        kKernelDebugger.Attach(kProgPath, cmd, kPID);
      }

      if (cmd == "exit") {
        if (kPID > 0) kKernelDebugger.Detach();

        break;
      }

      if (cmd == "break" || cmd == "b") {
        kStdOut << "[?] Enter a symbol to break on: ";

        std::getline(std::cin, cmd);

        if (kKernelDebugger.BreakAt(cmd)) {
          pfd::notify("ANT Kernel Debugger Event", "Add breakpoint at: " + cmd);
        }
      }
    }

    return EXIT_SUCCESS;
  }

  kStdOut << "usage: " << argv[0] << " -k <kernel_path> -ip <ip4>\n";
  kStdOut << "example: " << argv[0] << " -k /path/to/ne_kernel -ip 127.0.0.1\n";

  return EXIT_FAILURE;
}

#endif  // DK_KRNL_DEBUGGER
