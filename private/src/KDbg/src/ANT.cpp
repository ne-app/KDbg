// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#ifndef DEBUGGERKIT_WINDOWS
#include <netinet/in.h>
#else
#include <winsock.h>
#endif

#ifdef DK_KRNL_DEBUGGER

/// @author Amlal El Mahrouss
/// @brief Kernel Debugger Protocol for Ne.app Ant

#include <KDbg/ANT.h>
#include <ThirdParty/Dialogs/Dialogs.h>

using namespace KDbg::Detail;
using namespace KDbg::ANT;

IKrnlDebugger::IKrnlDebugger()  = default;
IKrnlDebugger::~IKrnlDebugger() = default;

bool IKrnlDebugger::Attach(const Tier0Kit::STLString& path,
                              const Tier0Kit::STLString& argv, ProcessID& pid) noexcept {
  if (path.empty() || argv.empty()) return NO;

  m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

  if (m_socket == -1) return NO;

  struct sockaddr_in server_addr;
  ::memset(&server_addr,0, sizeof(struct sockaddr_in));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(kDebugPort);

  if (::inet_pton(AF_INET, argv.c_str(), &server_addr.sin_addr) <= 0) return NO;

  auto ret = (::connect(m_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1);

  if (ret) return NO;

  Tier0Kit::STLString pkt = Detail::kDebugMagic;

  if (pkt.empty()) return NO;

  pkt += ";\r";
  //! common enough baud rate for a debugger.
  pkt += "BAUD=38400;\r";

  ret = ::send(m_socket, pkt.data(), pkt.size(), 0) > 0;
  return ret;
}

bool IKrnlDebugger::BreakAt(const Tier0Kit::STLString& symbol) noexcept {
  Tier0Kit::STLString pkt = Detail::kDebugMagic;

  if (pkt.empty()) return NO;

  pkt += ";SYM=\"";
  pkt += symbol;
  pkt += "\";\r";

  if (pkt.size() > kDebugCmdLen) return NO;

  auto ret = ::send(m_socket, pkt.data(), pkt.size(), 0) > 0;
  return ret;
}

bool IKrnlDebugger::Break() noexcept {
  Tier0Kit::STLString pkt = Detail::kDebugMagic;
  pkt += ";BRK=1;\r";

  auto ret = ::send(m_socket, pkt.data(), pkt.size(), 0) > 0;
  return ret;
}

bool IKrnlDebugger::Continue() noexcept {
  Tier0Kit::STLString pkt = Detail::kDebugMagic;
  if (pkt.empty()) return NO;

  pkt += ";CONT=1;\r";

  auto ret = ::send(m_socket, pkt.data(), pkt.size(), 0) > 0;
  return ret;
}

#ifndef DEBUGGERKIT_WINDOWS
#define closesocket close
#endif

bool IKrnlDebugger::Detach() noexcept {
  Tier0Kit::STLString pkt = Detail::kDebugMagic;
  pkt += ";DTCH=1;\r";

  auto ret = ::send(m_socket, pkt.data(), pkt.size(), 0) > 0;

  if (ret)
    ::closesocket(m_socket);
  else
    return NO;

  return ret;
}

#endif  // DK_KRNL_DEBUGGER
