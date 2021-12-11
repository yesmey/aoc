#include <common.h>
#include <stack>

u64 first_solution(input_range_of<std::string> auto&& range) {
    u64 totalPoints = 0;

    for (auto&& row : range) {
        std::map<char, char> map = {
            { '(', ')' },
            { '{', '}' },
            { '[', ']' },
            { '<', '>' }
        };

        std::stack<char> stack;
        for (auto chr : row) {
            if (map.contains(chr)) {
                stack.push(chr);
            }
            else {
                if (chr != map[stack.top()]) {
                    switch (chr) {
                        case ')': totalPoints += 3; break;
                        case ']': totalPoints += 57; break;
                        case '}': totalPoints += 1197; break;
                        case '>': totalPoints += 25137; break;
                    }
                }
                stack.pop();
            }
        }
    }

    return totalPoints;
}

u64 second_solution(input_range_of<std::string> auto&& range) {

    std::vector<u64> all_points;

    for (std::string& row : range) {
        std::map<char, char> map = {
            { '(', ')' },
            { '{', '}' },
            { '[', ']' },
            { '<', '>' }
        };

        bool isCorrupted = false;
        std::stack<char> stack;
        for (auto chr : row) {
            if (map.contains(chr)) {
                stack.push(chr);
            }
            else {
                if (chr != map[stack.top()]) {
                    isCorrupted = true;
                    break;
                }
                stack.pop();
            }
        }

        if (isCorrupted) {
            continue;
        }

        u64 total_score = 0;
        while (stack.size() > 0) {
            total_score *= 5;
            switch (stack.top()) {
                case '(': total_score += 1; break;
                case '[': total_score += 2; break;
                case '{': total_score += 3; break;
                case '<': total_score += 4; break;
            }
            stack.pop();
        }

        all_points.push_back(total_score);
    }

    ranges::sort(all_points);
    return all_points[all_points.size() / 2];
}

int main() {
    {
        std::ifstream ifs("input");
        const auto first = first_solution(ranges::istream_view<std::string>(ifs));
        std::cout << "first answer: " << first << std::endl;
    }

    {
        std::ifstream ifs("input");
        const auto second = second_solution(ranges::istream_view<std::string>(ifs));
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
