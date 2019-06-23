/**
 * Copyright (c) 2019 meritozh
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <variant>

#include <foundation/option.hpp>

namespace prototype {
namespace foundation {

inline namespace types {
template <typename T> struct Ok final {
private:
  T val;

public:
  constexpr Ok(T &&val) : val(std::forward<T>(val)) {}

  constexpr auto get() const noexcept { return this->val; }
};

template <typename E> struct Err final {
private:
  E val;

public:
  constexpr Err(E &&val) : val(std::forward<E>(val)) {}

  constexpr auto get() const noexcept { return this->val; }
};

} // namespace types

/// The generic result type, either Ok<T> or Err<E>.
template <typename T, typename E> class Result final {
  static_assert(!std::is_same_v<T, void>, "T must not be void");
  static_assert(!std::is_same_v<E, void>, "E must not be void");

private:
  std::variant<types::Ok<T>, types::Err<E>> storage;

public:
  Result() = delete;

  constexpr Result(const Ok<T> &val) : storage(val) {}
  constexpr Result(Ok<T> &&val) : storage(std::move(val)) {}

  constexpr Result(const Err<E> &val) : storage(val) {}
  constexpr Result(Err<E> &&val) : storage(std::move(val)) {}

  constexpr bool is_ok() const &noexcept { return this->storage.index() == 0; }

  constexpr bool is_err() const &noexcept { return this->storage.index() == 1; }

  constexpr Option<T> ok() const &noexcept {
    if (auto val = std::get_if<0>(&this->storage)) {
      return val->get();
    }
    return std::nullopt;
  }

  constexpr Option<E> err() const &noexcept {
    if (auto val = std::get_if<1>(&this->storage)) {
      return val->get();
    }
    return std::nullopt;
  }
};

} // namespace foundation
} // namespace prototype
