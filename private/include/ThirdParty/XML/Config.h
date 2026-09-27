// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>

struct NavHintsPragma final {
  std::string key;
  std::string value;
};

struct NavHintsImage final {
  std::string url;
};
