#include <iostream>
#include <map>
#include <unordered_map>

#include "ch1/ex1.hpp"
#include "lib/time.hpp"

struct Value final {
  std::int64_t a;
  std::int64_t b;
  std::int64_t c;
  std::int64_t d;
};

int main() {
  volatile int no_optimize;
  (void)no_optimize;

  using namespace lib;
  using namespace ch1;

  constexpr std::size_t N = 1000;
  constexpr std::size_t M = 32 * 1024 * 1024;
  constexpr std::size_t S = 100;
  constexpr std::size_t X = 100;
  constexpr std::size_t I = 1000;
  constexpr std::size_t J = 1000;

  using K = std::int32_t;
  using V = Value;

  std::map<K, V> omap;
  std::unordered_map<K, V> umap;
  FlatMap<K, V> fmap;

  for (std::size_t n = 0; n < N; ++n) {
    auto fr1 = memory_fragment(I, J);
    omap[n] = {};
    auto fr2 = memory_fragment(I, J);
    umap[n] = {};
    auto fr3 = memory_fragment(I, J);
    fmap[n] = {};
  }

  std::chrono::nanoseconds omap_time{};
  std::chrono::nanoseconds umap_time{};
  std::chrono::nanoseconds fmap_time{};

  std::vector<int> samples = sample_index_generate(S, N);

  for (int x = 0; x < X; ++x) {
    for (int count = 0; count < S; ++count) {
      cache_clobber(M);
      {
        auto t0 = time_point_now();
        auto iter = omap.find(samples[count % S]);
        auto t1 = time_point_now();
        no_optimize = iter != omap.end();
        omap_time += (t1 - t0);
      }

      cache_clobber(M);
      {
        auto t0 = time_point_now();
        auto iter = umap.find(samples[count % S]);
        auto t1 = time_point_now();
        no_optimize = iter != umap.end();
        umap_time += (t1 - t0);
      }

      cache_clobber(M);
      {
        auto t0 = time_point_now();
        auto iter = fmap.find(samples[count % S]);
        auto t1 = time_point_now();
        no_optimize = iter != nullptr;
        fmap_time += (t1 - t0);
      }
    }
  }
  std::cout << "omap: " << omap_time.count() << std::endl;
  std::cout << "umap: " << umap_time.count() << std::endl;
  std::cout << "fmap: " << fmap_time.count() << std::endl;
}
