#ifndef TYPETRAITS_H
#define TYPETRAITS_H
#include <utility>

template <typename T>
  struct has_at {

  template <typename U>
  static constexpr
  decltype(std::declval<U>().at(), bool())
  test_at(int) {
    return true;
  }

  template <typename U>
  static constexpr bool test_at(...) {
    return false;
  }

  static constexpr bool value = test_at<T>(int());
};

#endif // TYPE_TRAITS_H
