#include <iostream>
#include <map>
#include <unordered_map>

#include "ch1/ex1.hpp"
#include "lib/time.hpp"

int main() {
  using namespace lib;
  using namespace ch1;

  constexpr std::size_t N = 1000;
  constexpr std::size_t M = 32 * 1024 * 1024;
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

  std::chrono::nanoseconds omap_time{};
  std::chrono::nanoseconds umap_time{};
  std::chrono::nanoseconds fmap_time{};

  std::vector<int> samples = sample_index_generate(S, N);
  volatile int no_optimize;
  (void)no_optimize;

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
  std::cout << "omap: " << omap_time.count() << std::endl;
  std::cout << "umap: " << umap_time.count() << std::endl;
  std::cout << "fmap: " << fmap_time.count() << std::endl;
}
