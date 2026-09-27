// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#pragma once

#include <ThirdParty/XML/Config.h>
#include <vector>

/// =========================================================== ///
/// @file ThirdParty/XML/XML.h
/// @author Amlal El Mahrouss
/// @brief libxml2 delegate for .navhints files.
/// =========================================================== ///

namespace KDbg {

/// =========================================================== ///
/// \brief Parses .navhints XML file via libxml2.
/// \author Amlal El Mahrouss
/// =========================================================== ///
class INavHintsDelegate {
 public:
  INavHintsDelegate()  = default;
  virtual ~INavHintsDelegate() = default;

  INavHintsDelegate(const INavHintsDelegate&)            = default;
  INavHintsDelegate& operator=(const INavHintsDelegate&) = default;

 public:
  virtual bool Load(const std::string& path) noexcept;

  const std::vector<NavHintsPragma>& Pragmas() const noexcept;
  const std::vector<NavHintsImage>&  Images()  const noexcept;

  bool IsValid() const noexcept;

  std::string Pragma(const std::string& key) const noexcept;


 private:
  std::vector<NavHintsPragma> m_pragmas;
  std::vector<NavHintsImage>  m_images;
  bool                        m_valid{false};
};

}  // namespace KDbg
