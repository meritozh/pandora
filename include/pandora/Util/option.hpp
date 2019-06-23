/**
 * Copyright (c) 2019 meritozh
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#pragma once

#include <optional>

namespace prototype {
namespace foundation {

template <typename T> struct Option final {
private:
  std::optional<T> internal;

  
};

} // namesapce foundation
} // namespace prototype