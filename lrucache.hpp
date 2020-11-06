#ifndef _LRU_CACHE_H_
#define _LRU_CACHE_H_
#include <unordered_map>
#include <list>
#include <stdexcept>

namespace cache {

template <typename key_t, typename val_t>
class lru_cache {
public:
  typedef typename std::pair<key_t, val_t> key_val_pair_t;
  typedef typename std::list<key_val_pair_t>::iterator list_itr_t;

  lru_cache(size_t size) : _max_size(size) {}

  void put(const key_t& key, const val_t& val) {
    auto it = _cache_map.find(key);
    _cache_list.emplace_front(key, val);
    if(it != _cache_map.end()) {
      _cache_list.erase(it->second);
      _cache_map.erase(it);
    }
    _cache_map[key] = _cache_list.begin();
    if(_cache_list.size() > _max_size) {
      auto last = _cache_list.end();
      --last;
      _cache_map.erase(it->first);
      _cache_list.pop_back();
    }
  }

  const val_t& get(const key_t& key) {
    auto it = _cache_map.find(key);
    if(it != _cache_map.end()) {
      _cache_list.splice(_cache_list.begin(), _cache_list, it->second);
      return it->second->second;
    } else {
      throw std::range_error("Key does not exist in cache");
    }
  }

  bool exists(key_t key) const {
    return (_cache_map.find(key) != _cache_map.end());
  }

  size_t size() const {
    return _cache_map.size();
  }

private:
  std::unordered_map<key_t, list_itr_t> _cache_map;
  std::list<key_val_pair_t> _cache_list;
  size_t _max_size;
};

}
#endif
