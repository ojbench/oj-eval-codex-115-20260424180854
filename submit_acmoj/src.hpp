#pragma once
#include <new>
#include <utility>
// 你不可以使用其他任何头文件

namespace sjtu {

template <typename _Tp>
class unique_ptr {
 private:
  _Tp *ptr_;

 public:
  unique_ptr() : ptr_(nullptr) {}

  unique_ptr(const unique_ptr &) = delete;

  unique_ptr(unique_ptr &&other) : ptr_(other.ptr_) { other.ptr_ = nullptr; }

  ~unique_ptr() { delete ptr_; }

  unique_ptr &operator=(const unique_ptr &) = delete;

  unique_ptr &operator=(unique_ptr &&other) {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  explicit unique_ptr(_Tp *p) : ptr_(p) {}

  void reset() {
    delete ptr_;
    ptr_ = nullptr;
  }

  _Tp *release() {
    _Tp *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }

  _Tp *get() const { return ptr_; }

  _Tp &operator*() { return *ptr_; }

  _Tp *operator->() { return ptr_; }
};

static_assert(sizeof(unique_ptr<int>) <= sizeof(void *));

template <typename _Tp, typename... Args>
unique_ptr<_Tp> make_unique(Args &&...args) {
  return unique_ptr<_Tp>(new _Tp(std::forward<Args>(args)...));
}

}  // namespace sjtu

