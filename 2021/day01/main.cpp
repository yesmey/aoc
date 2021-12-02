#include <common.h>

u32 first_solution(input_range_of<u32> auto&& range) {
    u32 prev = std::numeric_limits<u32>::max();
    u32 increases = 0;

    for (u32 curr : range) {
        if (prev < curr) {
            increases++;
        }
        prev = curr;
    }

    return increases;
}

u32 second_solution(input_range_of<u32> auto&& range) {
    auto sum_next_three = [prev_1 = 0, prev_2 = 0](u32 curr) mutable {
        const u32 sum = curr + prev_1 + prev_2;
        prev_2 = prev_1;
        prev_1 = curr;
        return sum;
    };

    return first_solution(range
        | rviews::transform(sum_next_three)
        | rviews::drop(2));
}

int main() {
    {
        std::ifstream ifs("input");
        const auto first = first_solution(ranges::istream_view<u32>(ifs));
        std::cout << "first answer: " << first << std::endl;
    }

    {
        std::ifstream ifs("input");
        const auto second = second_solution(ranges::istream_view<u32>(ifs));
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
