#pragma once
#include <atomic>
#include <cassert>
#include <limits>
#include <vector>

namespace flog {
template <typename T> class channel {
public:
  explicit channel(uint32_t capactiy) : _mask(aligned_to_pow2(capactiy) - 1) {
    _storage.reserve(_mask + 1);
    {
      for (auto i = 0U; i < _storage.capacity(); i++) {
        _storage.emplace_back();
      }
    }
  }

  auto capacity() const { return _storage.capacity(); }
  auto size() const {
    auto head = _head.load(std::memory_order_acquire);
    auto tail = _tail.load(std::memory_order_acquire);

    assert(tail >= head);
    return tail - head;
  }

  template <typename... ARGS> auto emplace(ARGS &&...args) {
    auto head = _head.load(std::memory_order_acquire);
    auto tail = _tail.load(std::memory_order_acquire);
    if (tail - head == capacity()) {
      return false;
    }

    auto idx = to_idx(tail);
    new (&_storage[idx]) T(std::forward<ARGS>(args)...);

    _tail.fetch_add(1, std::memory_order_release);
    return true;
  }

  T *recv() {
    auto head = _head.load(std::memory_order_acquire);
    auto tail = _tail.load(std::memory_order_acquire);

    if (tail == head) {
      return nullptr;
    }

    auto idx = to_idx(head);
    auto t = &_storage[idx];

    _head.fetch_add(1, std::memory_order_release);
    return &_storage[idx];
  }

private:
  auto to_idx(uint32_t val) const { return val & _mask; }

  static auto aligned_to_pow2(uint32_t size) {
    auto digits = std::numeric_limits<uint32_t>::digits;
    auto shift = (digits - __builtin_clz(size * 2 - 1) - 1);
    return 1U << shift;
  }

private:
  std::atomic_uint _head{0};
  std::atomic_uint _tail{0};

  uint32_t _mask;

  std::vector<T> _storage;
};
} // namespace flog