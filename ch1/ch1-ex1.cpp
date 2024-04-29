#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "../nanobench.h"

int main() {
  using namespace ankerl;

  using Type = std::int64_t;
  std::map<Type, Type> omap;
  std::unordered_map<Type, Type> umap;
  std::vector<std::pair<Type, Type>> vec;

  const Type N = 100;
  for (Type i = 0; i < N; ++i) {
    omap[i] = 5;
    umap[i] = 5;
    vec.emplace_back(i, 5);
  }

  nanobench::Bench().run("find-in-omap", [&] {
    // for (Type i = 0; i < N; ++i) {
    for (const auto& p : omap) {
      nanobench::doNotOptimizeAway(omap.find(p.first) != omap.end());
    }
  });

  nanobench::Bench().run("find-in-umap", [&] {
    // for (Type i = 0; i < N; ++i) {
    for (const auto& p : omap) {
      nanobench::doNotOptimizeAway(umap.find(p.first) != umap.end());
    }
  });

  nanobench::Bench().run("find-in-vec", [&] {
    // for (Type i = 0; i < N; ++i) {
    for (const auto& p : vec) {
      nanobench::doNotOptimizeAway(
        std::find_if(vec.begin(), vec.end(), [i = p.first](const auto& p) {
          return p.first == i;
        }) != vec.end());
    }
  });

  return 0;
}
