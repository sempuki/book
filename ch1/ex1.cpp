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

  return 0;
}
