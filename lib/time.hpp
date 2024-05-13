// Copyright 2024 -- CONTRIBUTORS. See LICENSE.
#pragma once

#include <chrono>

namespace lib {

auto time_point_now() {
  if constexpr (std::chrono::high_resolution_clock::is_steady) {
    return std::chrono::high_resolution_clock::now();
  } else {
    return std::chrono::steady_clock::now();
  }
}

}  // namespace lib
