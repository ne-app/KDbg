// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app/kdbg

#pragma once

#include <libidl/config.hpp>

#ifndef _LIBIDL
#define _LIBIDL (202609)
#endif

#define LIBIDL_MAGIC_NUMBER ("IDLBUF")
#define LIBIDL_MAGIC_NUMBER_LEN (6)
#define LIBIDL_MAX_LAYOUT_LEN (128U)

#define LIBIDL_FILE_EXT ".idl"

#define LIBIDL_ALIGN (8)

#ifndef LIBIDL_DECL_STRUCT
#define LIBIDL_DECL_STRUCT(KEY, VALUE, FP)                                           \
  {                                                                           \
    ::libidl::detail::libidl_interface<decltype(KEY), decltype(VALUE)> idl;   \
    ::memset(&idl, 0, sizeof(idl));                                           \
    idl.key_.layout_ = 0;                                                     \
    ::memcpy(idl.key_.val_, KEY, ::strlen(KEY));                              \
    idl.value_.layout_ = ::strlen(KEY) + LIBIDL_MAX_LAYOUT_LEN;               \
    ::memcpy(idl.value_.val_, VALUE, ::strlen(VALUE));                        \
    ::memcpy(idl.magic_, LIBIDL_MAGIC_NUMBER, ::strlen(LIBIDL_MAGIC_NUMBER)); \
    FP.write((char*) &idl, sizeof(idl));                                      \
    FP.flush();                                                               \
  }

#endif

namespace libidl {

namespace detail {

  template <typename Key, class Value>
  struct libidl_interface;

  template <typename Value>
  struct libidl_wrapper;

  template <typename Key, class Value>
  struct alignas LIBIDL_ALIGN libidl_interface final {
    using magic_type = uint8_t[LIBIDL_MAGIC_NUMBER_LEN];

    magic_type            magic_;
    libidl_wrapper<Key>   key_;
    libidl_wrapper<Value> value_;
  };

  template <typename Value>
  struct alignas LIBIDL_ALIGN libidl_wrapper final {
    using type = uint8_t[LIBIDL_MAX_LAYOUT_LEN];
    using int_type = int32_t;

    int_type  layout_;
    type val_;
  };

}  // namespace detail

}  // namespace libidl