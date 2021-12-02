// don't do this at home lol

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <fstream>
#include <algorithm>
#include <optional>
#include <limits>
#include <utility>

typedef int8_t i8;
typedef uint8_t u8;

typedef int16_t i16;
typedef uint16_t u16;

typedef int32_t i32;
typedef uint32_t u32;

typedef int64_t i64;
typedef uint64_t u64;

namespace ranges = std::ranges;
namespace rviews = ranges::views;

// source: https://www.reedbeta.com/blog/ranges-compatible-containers/
template <typename R, typename T>
concept input_range_of =
	std::ranges::input_range<R> &&
	std::convertible_to<std::ranges::range_value_t<R>, T>;
