// Copyright 2024 -- CONTRIBUTORS. See LICENSE.
#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#include "lib/type_macros.hpp"

namespace ch1 {

template <typename K, typename V>
class FlatMap final {
 public:
  V& operator[](const K& key) noexcept {
    V* ptr = find(key);  //
    if (!ptr) {
      ks_.emplace_back(key);
      vs_.emplace_back();
      ptr = std::addressof(vs_.back());
    }
    return *ptr;
  }

  V* find(const K& key) noexcept {
    return find_stl_(key);  //
  }

 private:
  V* find_stl_(const K& key) noexcept {
    auto iter = std::find(ks_.begin(), ks_.end(), key);
    auto index = std::distance(ks_.begin(), iter);
    return iter != ks_.end() ? std::addressof(vs_[index]) : nullptr;
  }

  V* find_loop_(const K& key) noexcept {
    std::size_t index = 0;
    for (; index < ks_.size(); ++index) {
      if (ks_[index] == key) {
        break;
      }
    }
    return index < ks_.size() ? std::addressof(vs_[index]) : nullptr;
  }

  std::vector<K> ks_;
  std::vector<V> vs_;
};

std::vector<int> sample_index_generate(int sample_count, int index_count) {
  std::random_device dev;
  std::seed_seq seeds{dev(), dev(), dev(), dev()};
  std::mt19937 generator{seeds};
  std::uniform_int_distribution<int> distribution{0, index_count};
  std::vector<int> samples(sample_count);
  std::generate_n(samples.begin(), sample_count, [&] {
    return distribution(generator);  //
  });
  return samples;
}

void cache_clobber(std::size_t cache_size) {
  volatile int no_optimize;
  std::vector<std::size_t> m(cache_size / sizeof(std::size_t));
  std::fill(m.begin(), m.end(), 1);
  no_optimize = m.front();
  no_optimize = m.back();
  (void)no_optimize;
}

}  // namespace ch1
