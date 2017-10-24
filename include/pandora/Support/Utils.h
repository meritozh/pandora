#ifndef PANDORA_SUPPORT_UTILS_H
#define PANDORA_SUPPORT_UTILS_H

#include "Compiler.h"

#include <boost/filesystem.hpp>

#include <cmath>
#include <limits>
#include <string>

namespace fs = boost::filesystem;

namespace pandora {

/// @name Char & String
/// @{

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool AlmostEqual(double a, double b) noexcept {
  return std::abs(a - b) <= (std::numeric_limits<double>::epsilon() *
                             std::max(std::abs(a), std::abs(b)));
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsLowercase(char letter) noexcept {
  return 'a' <= letter && letter <= 'z';
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsUppercase(char letter) noexcept {
  return 'A' <= letter && letter <= 'Z';
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsLowercase(const std::string &text) noexcept {
  for (char letter : text) {
    if (IsUppercase(letter))
      return false;
  }
  return true;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsAscii(char letter) noexcept { return !(letter & 0x80); }

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsAlpha(char letter) noexcept {
  return IsLowercase(letter) || IsUppercase(letter);
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsPrintable(char letter) noexcept {
  return ' ' <= letter && letter <= '~';
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsPrintable(const std::string &text) noexcept {
  for (char letter : text) {
    if (!IsPrintable(letter))
      return false;
  }
  return true;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool IsPunctuation(char letter) noexcept {
  return ('!' <= letter && letter <= '/') || (':' <= letter && letter <= '@') ||
         ('[' <= letter && letter <= '`') || ('{' <= letter && letter <= '~');
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool Lowercase(char letter) {
  if (IsUppercase(letter))
    return letter ^ 0x20;
  return letter;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
std::string Lowercase(const std::string &text) {
  std::string result;
  for (char letter : text)
    result.push_back(Lowercase(letter));
  return result;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool HasLowercase(const std::string &text) {
  for (char letter : text)
    if (IsLowercase(letter))
      return true;
  return false;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
char Uppercase(char letter) {
  if (IsLowercase(letter))
    return letter ^ 0x20;
  return letter;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
std::string Uppercase(const std::string &text) {
  std::string result;
  for (char letter : text)
    result.push_back(Uppercase(letter));
  return result;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
bool HasUppercase(const std::string &text) {
  for (char letter : text)
    if (IsUppercase(letter))
      return true;
  return false;
}

PANDORA_ATTRIBUTE_ALWAYS_INLINE
char SwapCase(char letter) {
  if (IsAlpha(letter))
    return letter ^ 0x20;
  return letter;
}

/// @}
/// @name File
/// @{

/// Reads the entire contents of the specified file. If the file does not exist,
/// an exception is thrown.
std::string ReadUtf8File(const fs::path &filepath);

/// Writes the entire contents of the specified file. If the file does not
/// exist, an exception is thrown.
void WriteUtf8File(const fs::path &fiflepath, const std::string &contents);

template <class Container, class Key>
typename Container::mapped_type &
GetValueElseInsert(Container &container, const Key key,
                   const typename Container::mapped_type &value) {
  return container.insert(typename Container::value_type(key, value))
      .first->second;
}

template <class Container, class Key>
bool ContainsKey(Container &container, const Key *key) {
  return container.find(key) != container.end();
}

template <class Container, class Key>
typename Container::mapped_type
FindWithDefault(Container &container, const Key &key,
                const typename Container::mapped_type &value) {
  typename Container::const_iterator it = container.find(key);
  return it != container.end() ? it->second : value;
}

template <class Container, class Key>
bool Erase(Container &container, const Key &key) {
  typename Container::iterator it = container.find(key);

  if (it != container.end()) {
    container.erase(it);
    return true;
  }
  return false;
}

/// Shrink a vector to its sorted \c num_sorted_elements smallest. If
/// \c num_sorted_elements is 0 or larger than the vector size, sort the whole
/// vector.
template <typename Element>
void PartialSort(std::vector<Element> &elements,
                 const size_t num_sorted_elements) {
  size_t nb_elements = elements.size();
  size_t max_elements =
      num_sorted_elements > 0 && nb_elements >= num_sorted_elements
          ? num_sorted_elements
          : nb_elements;

  // When the number of elements to sort is more than 1024 and one sixty-fourth
  // of the total number of elements, switch to \c std::nth_element followed by
  // \c std::sort. This heuristic is based on the observation that
  // \c std::partial_sort (heapsort) is the most efficient algorithm when the
  // number of elements to sort is small and that \c std::nth_element
  // (introselect) combined with \c std::sort (introsort) always perform better
  // than \c std::sort alone in other case.
  if (max_elements <= std::max(static_cast<size_t>(1024), nb_elements / 64)) {
    std::partial_sort(elements.begin(), elements.begin() + max_elements,
                      elements.end());
  } else {
    std::nth_element(elements.begin(), elements.begin() + max_elements,
                     elements.end());
    std::sort(elements.begin(), elements.begin() + max_elements);
  }

  // Remove the unsorted elements. Use erase instead of resize as it doesn't
  // require a default constructor on Element.
  elements.erase(elements.begin() + max_elements, elements.end());
}
/// @}

} // namespace pandora

#endif
