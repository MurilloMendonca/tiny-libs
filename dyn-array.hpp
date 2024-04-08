#define DYN_ARRAY_IMPL
#include "dyn-array.h"
template <typename T> class DynamicArray {
  Dyn_array _array;

public:
  class Iterator {
  private:
    T *ptr;

  public:
    Iterator(T *p) : ptr(p) {}

    T &operator*() const { return *ptr; }

    Iterator &operator++() {
      ++ptr;
      return *this;
    }

    bool operator==(const Iterator &other) const { return ptr == other.ptr; }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  Iterator begin() {
    return Iterator(reinterpret_cast<T *>(
        _array._data));
  }

  Iterator end() {
    return Iterator(
        reinterpret_cast<T *>(_array._data) +
        size());
  }
  DynamicArray() { _array = dyn_array_create(sizeof(T)); }
  ~DynamicArray() { dyn_array_destroy(&_array); }

  T get(size_t index) { return *(reinterpret_cast<T*>(dyn_array_get(&_array, index))); }
  void push_back(T val) { dyn_array_push_back(&_array, &val); }

  size_t size() { return _array.size; }

  size_t cap() { return _array.cap; }
};
