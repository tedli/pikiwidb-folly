/*
 * Copyright (c) 2023-present, Qihoo, Inc.  All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cmath>

namespace folly {

#if !defined(__ANDROID__) && !defined(__UCLIBC__)

/**
 * Most platforms hopefully provide std::nextafter, std::remainder.
 */

/* using override */ using std::nextafter;
/* using override */ using std::remainder;

#else // !__ANDROID__ && !__UCLIBC__

/**
 * On Android and uclibc, std::nextafter or std::remainder isn't implemented.
 * However, the C functions and compiler builtins are still provided. Using the
 * GCC builtin is actually slightly faster, as they're constexpr and the use
 * cases within folly are in constexpr context.
 */

#if defined(__GNUC__) && !defined(__clang__)

constexpr float nextafter(float x, float y) {
  return __builtin_nextafterf(x, y);
}

constexpr double nextafter(double x, double y) {
  return __builtin_nextafter(x, y);
}

constexpr long double nextafter(long double x, long double y) {
  return __builtin_nextafterl(x, y);
}

#else // __GNUC__

inline float nextafter(float x, float y) { return ::nextafterf(x, y); }

inline double nextafter(double x, double y) { return ::nextafter(x, y); }

inline long double nextafter(long double x, long double y) {
  return ::nextafterl(x, y);
}

#endif // __GNUC__

/**
 * On uclibc, std::remainder isn't implemented.
 * Implement it using builtin versions
 */
#ifdef __UCLIBC__
constexpr float remainder(float x, float y) {
  return __builtin_remainderf(x, y);
}

constexpr double remainder(double x, double y) {
  return __builtin_remainder(x, y);
}

constexpr long double remainder(long double x, long double y) {
  return __builtin_remainderl(x, y);
}
#endif // __UCLIBC__

#endif // !__ANDROID__ && !__UCLIBC__
} // namespace folly
