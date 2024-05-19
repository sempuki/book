#include "ch1/ex1.hpp"

#include <map>
#include <unordered_map>
#include <vector>

#include "lib/testing.hpp"

namespace ch1 {

struct Value final {
  std::int64_t a;
  std::int64_t b;
  std::int64_t c;
  std::int64_t d;
};

TEST_CASE("Chapter 1.") {
  constexpr std::size_t N = 100;
  constexpr std::size_t M = 64 * 1024 * 1024;
  constexpr std::size_t S = 1000;
  constexpr std::size_t I = 1000;
  constexpr std::size_t J = 100;
  std::vector<std::any> fragments;

  using K = std::int32_t;
  using V = Value;

  std::map<K, V> omap;
  std::unordered_map<K, V> umap;
  FlatMap<K, V> fmap;

  for (std::size_t n = 0; n < N; ++n) {
    fragments.push_back(memory_fragment(I, J));
    omap[n] = {};
    fragments.push_back(memory_fragment(I, J));
    umap[n] = {};
    fragments.push_back(memory_fragment(I, J));
    fmap[n] = {};
  }

  std::vector<int> samples = sample_index_generate(S, N);

  SECTION("Example 1.") {
    BENCHMARK_ADVANCED("Benchmark 1: Ordered Map.")
    (Catch::Benchmark::Chronometer _) {
      cache_clobber(M);
      _.measure([&](int count) {
        auto iter = omap.find(samples[count % S]);
        return iter != omap.end();
      });
    };

    BENCHMARK_ADVANCED("Benchmark 2: Unordered Map.")
    (Catch::Benchmark::Chronometer _) {
      cache_clobber(M);
      _.measure([&](int count) {
        auto iter = umap.find(samples[count % S]);
        return iter != umap.end();
      });
    };

    BENCHMARK_ADVANCED("Benchmark 3: Flat Map.")
    (Catch::Benchmark::Chronometer _) {
      cache_clobber(M);
      _.measure([&](int count) {
        auto iter = fmap.find(samples[count % S]);
        return iter != nullptr;
      });
    };
  }
}

}  // namespace ch1
