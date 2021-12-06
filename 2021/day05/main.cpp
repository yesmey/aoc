#include <common.h>

using Coordinate = std::pair<int, int>;

struct VentCoordinate {
    std::vector<Coordinate> points;
};

auto parse_input(bool diagonal) {
    std::ifstream ifs("input");
    std::vector<std::string> vec;
    ranges::copy(ranges::istream_view<std::string>(ifs), std::back_inserter(vec));

    std::vector<VentCoordinate> result;
    for (int i = 0; i < vec.size(); i += 3) {
        auto comma = vec[i].find(",");
        Coordinate point1{};
        point1.first = std::stoi(vec[i].substr(0, comma));
        point1.second = std::stoi(vec[i].substr(comma + 1));

        auto comma2 = vec[i + 2].find(",");
        Coordinate point2{};
        point2.first = std::stoi(vec[i + 2].substr(0, comma2));
        point2.second = std::stoi(vec[i + 2].substr(comma2 + 1));

        std::vector<Coordinate> points;
        if (point1.first == point2.first) {
            // vertical line
            auto [start, end] = std::minmax(point1.second, point2.second);
            for (auto i = start; i <= end; i++) {
                points.push_back({ point1.first, i });
            }
        }
        else if (point1.second == point2.second) {
            // horizontal line
            auto [start, end] = std::minmax(point1.first, point2.first);
            for (auto i = start; i <= end; i++) {
                points.push_back({ i, point1.second });
            }
        }
        else if (diagonal) {
            // diagonal
            auto xDirection = point1.first < point2.first ? 1 : -1;
            auto yDirection = point1.second < point2.second ? 1 : -1;
            auto to = std::abs(point1.first - point2.first);
            for (auto i = 0; i <= to; i++) {
                points.push_back({ point1.first + (i * xDirection), point1.second + (i * yDirection) });
            }
        }

        result.push_back({ points });
    }

    return result;
}

u32 first_solution(const std::vector<VentCoordinate>& input) {
    std::set<Coordinate> overlapped;
    std::set<Coordinate> all_points;
    for (auto&& coordinate : input) {
        for (auto&& point : coordinate.points) {
            if (all_points.contains(point)) {
                overlapped.insert(point);
            }
            else {
                all_points.insert(point);
            }
        }
    }

    return overlapped.size();
}

int main() {
    {
        auto input = parse_input(false);
        const auto first = first_solution(input);
        std::cout << "first answer: " << first << std::endl;
    }

    {
        auto input = parse_input(true);
        const auto second = first_solution(input);
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
