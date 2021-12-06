#include <common.h>

using FishStates = std::map<u64, u64>;

auto parse_input() {
    std::vector<u64> result;

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

FishStates initialize_fish_states(const std::vector<u64>& input) {
    FishStates fish_states;
    for (auto timer : input) {
        fish_states[timer]++;
    }
    return fish_states;
}

FishStates run_iteration(const FishStates& old_state) {
    FishStates new_fish_state;
    for (auto&& [stage, fish_count] : old_state) {
        if (stage == 0) {
            new_fish_state[6] += fish_count; // we are now parents
            new_fish_state[8] += fish_count; // spawn our new babies
        }
        else {
            new_fish_state[stage - 1] += fish_count;
        }
    }
    return new_fish_state;
}

template <i32 days>
u64 run_iterations(const std::vector<u64>& input) {
    auto fish_states = initialize_fish_states(input);
    for (i32 i = 0; i < days; i++) {
        fish_states = run_iteration(fish_states);
    }

    // summarize the fishes in all states
    u64 sum = 0;
    for (auto value : rviews::values(fish_states)) {
        sum += value;
    }
    return sum;
}

int main() {
    const auto input = parse_input();
    {
        const auto first = run_iterations<80>(input);
        assert(first == 386536);
        std::cout << "first answer: " << first << std::endl;
    }

    {
        const auto second = run_iterations<256>(input);
        assert(second == 1732821262171);
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
