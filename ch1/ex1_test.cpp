#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "lib/testing.hpp"
#include "lib/type_macros.hpp"

namespace ch1 {

template <typename K, typename V>
V* find_stl(std::vector<K>& ks, std::vector<V>& vs, const K& key) {
  auto iter = std::find(ks.begin(), ks.end(), key);
  auto index = std::distance(ks.begin(), iter);
  return iter != ks.end() ? std::addressof(vs[index]) : nullptr;
}

template <typename K, typename V>
V* find_loop(std::vector<K>& ks, std::vector<V>& vs, const K& key) {
  std::size_t index = 0;
  for (; index < ks.size(); ++index) {
    if (ks[index] == key) {
      break;
    }
  }
  return index < ks.size() ? std::addressof(vs[index]) : nullptr;
}

template <typename K, typename V>
class FlatMap final {
 public:
  V* find(const K& key) noexcept {
    return find_stl(ks_, vs_, key);  //
  }

  V& operator[](const K& key) noexcept {
    V* ptr = find(key);  //
    if (!ptr) {
      ks_.emplace_back(key);
      vs_.emplace_back();
      ptr = std::addressof(vs_.back());
    }
    return *ptr;
  }

 private:
  std::vector<K> ks_;
  std::vector<V> vs_;
};

TEST_CASE("Chapter 1.") {
  constexpr std::size_t N = 1000;

  SECTION("Example 1.") {
    BENCHMARK_ADVANCED("Benchmark 1.")
    (Catch::Benchmark::Chronometer _) {
      std::map<std::int64_t, std::int64_t> omap;

      for (std::size_t n = 0; n < N; ++n) {
        omap[n] = n;
      }

      _.measure([&](int count) {
        auto iter = omap.find(count % N);
        return iter != omap.end();
      });
    };

    BENCHMARK_ADVANCED("Benchmark 2.")
    (Catch::Benchmark::Chronometer _) {
      std::unordered_map<std::int64_t, std::int64_t> umap;

      for (std::size_t n = 0; n < N; ++n) {
        umap[n] = n;
      }

      _.measure([&](int count) {
        auto iter = umap.find(count % N);
        return iter != umap.end();
      });
    };

    BENCHMARK_ADVANCED("Benchmark 3.")
    (Catch::Benchmark::Chronometer _) {
      FlatMap<std::int64_t, std::int64_t> fmap;

      for (std::size_t n = 0; n < N; ++n) {
        fmap[n] = n;
      }

      _.measure([&](int count) {
        auto iter = fmap.find(count % N);
        return iter != nullptr;
      });
    };
  }
}

}  // namespace ch1
