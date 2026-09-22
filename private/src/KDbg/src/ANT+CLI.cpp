// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#ifdef DK_KRNL_DEBUGGER

#include <KDbg/ANT.h>
#include <ThirdParty/Dialogs/Dialogs.h>
#include <ThirdParty/XML/XML.h>
#include <KDbg/Common.inl>

using namespace KDbg::ANT;

static void dbgi_ctrlc_handler(std::int32_t) {
  if (!kPID || kPath.empty()) return;

  kKernelDebugger.Break();

  pfd::notify("ANT Kernel Debugger Event", "Breakpoint has been hit!");

  kKeepRunning = false;
}

TIER0KIT_MODULE(DebuggerAnt) {
  pfd::notify("ANT Kernel Debugger Event",
              "ANT Kernel Debugger\n(C) 2025-2026 Ne.app, all "
              "rights reserved.");

  KDbg::INavHintsDelegate del;

  if (del.Load(argv[1])) {
    kPath = del.Pragma("SystemURI");
    kPath += ":";
    kPath += del.Pragma("SystemPort");
    kPath += "?macro=" + del.Pragma("PreprocessorMacro");
    kPath += "&img_type=" + del.Pragma("ImageType");
    kPath += "&img_arr=";

    auto img = del.Images();

    for (const auto& imgs : img) {
      kPath += imgs.url;
      kPath += "%20";
    }

    kStdOut << "[+] KIP (Kernel:IP) set to: " << kPath << "\n";

    Tier0Kit::install_signal(SIGINT, dbgi_ctrlc_handler);

    kKernelDebugger.Attach(kPath, del.Pragma("SystemCopyPath"), kPID);

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

        kKernelDebugger.Attach(kPath, cmd, kPID);
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
