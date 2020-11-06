#include <cstddef>
#include <iostream>
#include "lrucache.hpp"

int main() {
  cache::lru_cache<int, int> lru(2);
  lru.put(1,2);
  lru.put(2,3);
  std::cout << lru.get(1) << "\n";
  std::cout << lru.get(2) << "\n";
  return 0;
}