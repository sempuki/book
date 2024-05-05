#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

int main() {
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

  // nanobench::Bench().run("find-in-omap", [&] {
  //   // for (Type i = 0; i < N; ++i) {
  //   for (const auto& p : omap) {
  //     nanobench::doNotOptimizeAway(omap.find(p.first) != omap.end());
  //   }
  // });

  // nanobench::Bench().run("find-in-umap", [&] {
  //   // for (Type i = 0; i < N; ++i) {
  //   for (const auto& p : omap) {
  //     nanobench::doNotOptimizeAway(umap.find(p.first) != umap.end());
  //   }
  // });

  // nanobench::Bench().run("find-in-vec-stl", [&] {
  //   for (const auto& p : vec) {
  //     auto begin = vec.begin();
  //     auto end = vec.end();
  //     auto pred = [i = p.first](const auto& p) {
  //       return p.first == i;
  //     };
  //     nanobench::doNotOptimizeAway(std::find_if(begin, end, pred));
  //   }
  // });

  // auto f = [](const auto& v, auto i) {
  //   for (const auto& p : v) {
  //     if (p.first == i) {
  //       break;
  //     }
  //   }
  //   return i;
  // };

  // nanobench::Bench().run("find-in-vec-loop", [&] {
  //   for (const auto& p : vec) {
  //     nanobench::doNotOptimizeAway(f(vec, p.first));
  //   }
  // });

  return 0;
}
