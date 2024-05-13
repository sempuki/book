#include "ch1/ex1.hpp"

#include <map>
#include <unordered_map>
#include <vector>

#include "lib/testing.hpp"

namespace ch1 {

TEST_CASE("Chapter 1.") {
  constexpr std::size_t N = 1000;
  constexpr std::size_t S = 1000;

  using T = std::int64_t;
  std::map<T, T> omap;
  std::unordered_map<T, T> umap;
  FlatMap<T, T> fmap;

  for (std::size_t n = 0; n < N; ++n) {
    omap[n] = n;
    umap[n] = n;
    fmap[n] = n;
  }

  SECTION("Example 1.") {
    std::vector<int> samples = sample_index_generate(S, N);

    BENCHMARK_ADVANCED("Benchmark 1.")
    (Catch::Benchmark::Chronometer _) {
      _.measure([&](int count) {
        auto iter = omap.find(samples[count % S]);
        return iter != omap.end();
      });
    };

    BENCHMARK_ADVANCED("Benchmark 2.")
    (Catch::Benchmark::Chronometer _) {
      _.measure([&](int count) {
        auto iter = umap.find(samples[count % S]);
        return iter != umap.end();
      });
    };

    BENCHMARK_ADVANCED("Benchmark 3.")
    (Catch::Benchmark::Chronometer _) {
      _.measure([&](int count) {
        auto iter = fmap.find(samples[count % S]);
        return iter != nullptr;
      });
    };
  }
}

}  // namespace ch1
