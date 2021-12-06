// don't do this at home lol

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <ranges>
#include <fstream>
#include <algorithm>
#include <optional>
#include <limits>
#include <string_view>
#include <charconv>
#include <utility>
#include <cassert>


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

const i64 convert_to_int(std::string_view sv)
{
    i64 result;
    std::from_chars(sv.data(), sv.data() + sv.size(), result);
    return result;
}
