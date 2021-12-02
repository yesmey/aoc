#include <common.h>

auto read_input() {
    std::vector<u32> buffer;
    std::string line;
    std::ifstream ifs("input");
    while (std::getline(ifs, line)) {
        buffer.push_back(std::stoi(line));
    }
    return buffer;
}

auto first_solution(const std::vector<u32>& input) {
    u32 increases = 0;
    for (int i = 1; i < input.size(); i++) {
        if (input[i - 1] < input[i]) {
            increases++;
        }
    }
    return increases;
}

auto second_solution(const std::vector<u32>& input) {
    std::vector<u32> measurement_sums;
    for (int i = 0; i < input.size() - 2; i++) {
        measurement_sums.push_back(input[i] + input[i + 1] + input[i + 2]);
    }
    return first_solution(measurement_sums);
}

int main() {
    auto input = read_input();

    const auto first = first_solution(input);
    std::cout << "first answer: " << first << std::endl;

    const auto second = second_solution(input);
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
