#include <common.h>

auto read_input() {
    std::vector<std::string> buffer;
    std::string line;
    std::ifstream ifs("input");
    while (std::getline(ifs, line)) {
        buffer.push_back(line);
    }
    return buffer;
}

auto parse_information(const std::string& line) {
    auto view = line | rviews::split(' ');
    auto f = std::vector<std::string>(view.begin(), view.end());
    return std::make_tuple(f[0], std::stoi(f[1]));
}

u32 first_solution(const std::vector<std::string>& input) {
    u32 depth = 0;
    u32 position = 0;

    for (auto&& [direction, number] : input | rviews::transform(parse_information)) {
        if (direction == "forward") {
            position += number;
        }
        else if (direction == "down") {
            depth += number;
        }
        else if (direction == "up") {
            depth -= number;
        }
    }

    return depth * position;
}

u32 second_solution(const std::vector<std::string>& input) {
    u32 depth = 0;
    u32 position = 0;
    u32 aim = 0;

    for (auto&& [direction, number] : input | rviews::transform(parse_information)) {
        if (direction == "forward") {
            if (aim > 0) {
                depth += number * aim;
            }
            position += number;
        }
        else if (direction == "down") {
            aim += number;
        }
        else if (direction == "up") {
            aim -= number;
        }
    }

    return depth * position;
}

int main() {
    const auto input = read_input();

    const auto first = first_solution(input);
    std::cout << "first answer: " << first << std::endl;

    const auto second = second_solution(input);
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
