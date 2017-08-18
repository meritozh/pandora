
#ifndef PANDORA_ADT_STRINGREF_H
#define PANDORA_ADT_STRINGREF_H

#include "pandora/Support/Compiler.h"
#include <string>

namespace pandora {

/// \brief Represent a constant reference to a string, i.e. a character
/// array and a length, which need not be null terminated.
///
/// This class does not own the string data, it is expected to be used in
/// situations where the character data resides in some other buffer, whose
/// lifetime extends past that of the StringRef. For this reason, it is not
/// in general safe to store a StringRef.
class StringRef {
public:
  using iterator = const char *;
  using const_iterator = const char *;
  using size_type = size_t;

private:
  /// The start of the string, which is in an external buffer.
  const char *Data = nullptr;

  /// The length of the string.
  size_t Length = 0;

  PANDORA_ATTRIBUTE_ALWAYS_INLINE
  static int compareMemory(const char *Lhs, const char *Rhs, size_t Length) {
    if (Length == 0) {
      return 0;
    }
    return std::memcmp(Lhs, Rhs, Length);
  }

public:
  /// @name Constructors
  /// @{

  /// Construct an empty string ref.
  StringRef() = default;

  /// Disable conversiob from nullptr. This prevents things like
  /// if (S == nullptr)
  StringRef(std::nullptr_t) = delete;

  /// Construct a string ref from a cstring.
  PANDORA_ATTRIBUTE_ALWAYS_INLINE
  StringRef(const char *Str)
    : Data(Str), Length(Str ? std::strlen(Str) : 0) {}

  /// Construct a string ref from a pointer and length.
  PANDORA_ATTRIBUTE_ALWAYS_INLINE
  constexpr StringRef(const char *data, size_t length)
    : Data(data), Length(length) {}

  /// Construct a string ref from an std::string.
  PANDORA_ATTRIBUTE_ALWAYS_INLINE
  StringRef(const std::string &Str)
    : Data(Str.data()), Length(Str.length()) {}

  static StringRef willNullAsEmpty(const char *data) {
    return StringRef(data ? data : "");
  }

  /// @}
  /// @name Iterators
  /// @{

  iterator begin() const noexcept {
    return Data;
  }

  iterator end() const noexcept {
    return Data + Length;
  }

  const unsigned char *byte_begin() const noexcept {
    return reinterpret_cast<const unsigned char *>(begin());
  }

  const unsigned char *byte_end() const noexcept {
    return reinterpret_cast<const unsigned char *>(end());
  }
};

} // namespace end pandora

#endif
