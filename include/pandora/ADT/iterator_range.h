
#ifndef PANDORA_ADT_ITERATOR_RANGE_H
#define PANDORA_ADT_ITERATOR_RANGE_H

#include <iterator>
#include <utility>

namespace pandora {

/// \brief A range adaptor for a pair of iterators.
///
/// This just wraps two iterators into a range-compatible interface. Nothing
/// fancy at all.
template<typename IteratorT>
class iterator_range {
  IteratorT begin_iterator, end_iterator;

public:
  // TODO: Add SFINAE to test that the Container's iterators match the range's
  //       iterators.
  template<typename Container>
  iterator_range(Container &&c)
    : begin_iterator(c.begin()), end_iterator(c.end()) {}

  iterator_range(IteratorT begin_iterator, IteratorT end_iterator)
    : begin_iterator(std::move(begin_iterator)),
      end_iterator(std::move(end_iterator)) {}

  constexpr IteratorT begin() const noexcept {
    return begin_iterator;
  }

  constexpr IteratorT end() const noexcept {
    return end_iterator;
  }
};

/// \brief Convenience function for iterating over sub-ranges.
///
/// This is provides a bit if syntactic sugar to make using sub-ranges
/// in for loops a bit easier. Analogous to std::make_pair().
template<class T>
constexpr iterator_range<T> make_range(T x, T y) noexcept {
  return iterator_range<T>(std::move(x), std::move(y));
}

template<typename T>
constexpr iterator_range<T> make_range(std::pair<T, T> p) noexcept {
  return iterator_range<T>(std::move(p.first), std::move(p.second));
}

template<typename T> constexpr
iterator_range<decltype(begin(std::declval<T>()))> drop_begin(T &&t, int n)
noexcept {
  return make_range(std::next(begin(t), n), end(t));
}

} // namespace end pandora

#endif
