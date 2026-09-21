// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app/kdbg

#include <libidl/libidl.hpp>

/// @brief You have to provide IDL fields, thus the min count.
static const auto kMinArgs{4};
static const auto kStartArgs{2};

int main(int argc, char** argv) {
  if (argc < kMinArgs) {
    std::cout << "cl.idl.exe: invalid argument count, a minimum of 3 arguments is required.\n";
    return EXIT_FAILURE;
  }

  std::ofstream out_fp(std::string{argv[1]} + LIBIDL_FILE_EXT);

  for (int i = {kStartArgs}; i < argc; i += 2) {
    if ((i + 1) > argc) break;

    const char* key   = argv[i];
    const char* value = argv[i + 1];

    if (!value || !key) {
      std::filesystem::remove(argv[1]);
      return EXIT_FAILURE;
    }

    if (::strlen(value) > LIBIDL_MAX_LAYOUT_LEN) break;
    if (::strlen(key) > LIBIDL_MAX_LAYOUT_LEN) break;

    LIBIDL_DECL_STRUCT(key, value, out_fp);
  }

  return EXIT_SUCCESS;
}
