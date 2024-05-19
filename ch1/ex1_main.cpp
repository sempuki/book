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
  volatile int no_optimize = 0;
  (void)no_optimize;
  std::vector<std::any> fragments;

  using namespace lib;
  using namespace ch1;

  constexpr std::size_t N = 1000;
  constexpr std::size_t M = 64 * 1024 * 1024;
  constexpr std::size_t S = 100;
  constexpr std::size_t X = 10;
  constexpr std::size_t I = 1000;
  constexpr std::size_t J = 100;

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

  std::chrono::nanoseconds omap_time{};
  std::chrono::nanoseconds umap_time{};
  std::chrono::nanoseconds fmap_time{};

  for (std::size_t x = 0; x < X; ++x) {
    for (std::size_t count = 0; count < S; ++count) {
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
