#include <common.h>

auto parse_input() {
    std::vector<i64> result;

    std::ifstream ifs("input");
    std::string line;
    if (!std::getline(ifs, line))
        return result;

    auto int_view =
        line | rviews::split(',')
             | rviews::transform([](auto&& subrange) {
                return convert_to_int(std::string_view(subrange.begin(), subrange.end()));
             });

    ranges::copy(int_view, std::back_inserter(result));
    return result;
}

auto first_solution(const std::vector<i64>& input) {
    i64 max = *std::max_element(input.begin(), input.end());

    i64 min_fuel = std::numeric_limits<i64>::max();
    for (i64 i = 1; i < max; i++) {
        i64 fuel = 0;
        for (i64 num : input) {
            fuel += std::abs(num - i);
        }

        min_fuel = std::min(min_fuel, fuel);
    }

    return min_fuel;
}

i64 second_solution(const std::vector<i64>& input) {
    i64 max = *std::max_element(input.begin(), input.end());

    i64 min_fuel = std::numeric_limits<i64>::max();
    for (i64 i = 1; i < max; i++) {
        i64 fuel = 0;
        for (i64 num : input) {
            auto distance = std::abs(num - i);
            fuel += (distance * (distance + 1) / 2);
        }

        min_fuel = std::min(min_fuel, fuel);
    }

    return min_fuel;
}

int main() {
    auto input = parse_input();

    {
        const auto first = first_solution(input);
        assert(first == 336721);
        std::cout << "first answer: " << first << std::endl;
    }

    {
        const auto second = second_solution(input);
        assert(second == 91638945);
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
