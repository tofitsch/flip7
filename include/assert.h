#pragma once

#include <iostream>

#define ASSERT(expr) \
  do { \
    if (!(expr)) { \
      std::cerr << "[failed ASSERT] " << #expr << " "\
      << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
      std::abort(); \
    } \
  } while (0)
