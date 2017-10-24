
#ifndef PANDORA_SUPPORT_COMPILER_H
#define PANDORA_SUPPORT_COMPILER_H

/// \macro PANDORA_DLLEXPORT
/// \brief Export symbols to Windows dll library.

// pandora_EXPORTS is defined by CMake when building a shared library.
#if defined(_WIN32) && defined(pandora_EXPORTS)
#define PANDORA_DLLEXPORT __declspec(dllexport)
#else
#define PANDORA_DLLEXPORT
#endif

/// \macro PANDORA_GNUC_PRERED
/// \brief Extend the default __GNUC_PRERED even if glibc's features.h isn't
/// available.
#ifndef PANDORA_GNUC_PRERED
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
#define PANDORA_GNUC_PRERED(maj, min, patch)                                   \
  ((__GNUC__ << 20) + (__GNUC_MINOR__ << 10) + __GNUC_PATCHLEVEL__ >=          \
   ((maj) << 20) + ((min) << 10) + (patch))
#elif defined(__GNUC__) && defined(__GNUC_MINOR__)
#define PANDORA_GNUC_PRERED(maj, min, patch)                                   \
  ((__GNUC__ << 20) + (__GNUC_MINOR__ << 10) >= ((maj) << 20) + ((min) << 10))
#else
#define PANDORA_GNUC_PRERED(maj, min, patch) 0
#endif
#endif

/// \macro PANDORA_ATTRIBUTE_ALWAYS_INLINE
/// \brief Use compiler speicific directive to mark a method "always inline" for
/// performance sensitive. Only support with Clang and GCC 4.0 or later.
#if __has_attribute(always_inline) || PANDORA_GNUC_PRERED(4, 0, 0)
#define PANDORA_ATTRIBUTE_ALWAYS_INLINE __attribute((always_inline))
#elif defined(_MSC_VER)
#define PANDORA_ATTRIBUTE_ALWAYS_INLINE __forceinline
#else
#define PANDORA_ATTRIBUTE_ALWAYS_INLINE
#endif

#endif
