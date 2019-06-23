/**
 * Copyright (c) 2019 meritozh
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#pragma once

namespace prototype {
namespace foundation {

template <typename T> class CRTP {
public:
  using self_type = T;

  constexpr self_type &self() & noexcept {
    return static_cast<self_type &>(*this);
  }
};

} // namespace foundation
} // namespace prototype