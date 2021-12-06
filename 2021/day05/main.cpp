#include <common.h>

using Coordinate = std::pair<int, int>;

struct VentCoordinate {
    std::vector<Coordinate> points;
};

const Coordinate parse_coordinate(const std::string& str) {
    const auto comma = str.find(',');
    return { std::stoi(str.substr(0, comma)), std::stoi(str.substr(comma + 1)) };
}

auto parse_input() {
    std::ifstream ifs("input");
    std::vector<std::string> vec;
    ranges::copy(ranges::istream_view<std::string>(ifs), std::back_inserter(vec));
    return vec;
}

template <bool include_diagonal>
auto calculate_coordinates(const std::vector<std::string>& vec) {
    std::vector<VentCoordinate> result;
    result.reserve(vec.size() / 3);
    for (int i = 0; i < vec.size(); i += 3) {
        const auto [x1, y1] = parse_coordinate(vec[i]);
        const auto [x2, y2] = parse_coordinate(vec[i + 2]);

        std::vector<Coordinate> points;
        if (x1 == x2) {
            // vertical line
            auto [start, end] = std::minmax(y1, y2);
            points.reserve((end - start) + 1);
            for (auto i = start; i <= end; i++) {
                points.push_back({ x1, i });
            }
        }
        else if (y1 == y2) {
            // horizontal line
            auto [start, end] = std::minmax(x1, x2);
            points.reserve((end - start) + 1);
            for (auto i = start; i <= end; i++) {
                points.push_back({ i, y1 });
            }
        }
        else if (include_diagonal) {
            // diagonal
            auto xDirection = x1 < x2 ? 1 : -1;
            auto yDirection = y1 < y2 ? 1 : -1;
            auto to = std::abs(x1 - x2);
            points.reserve(to + 1);
            for (auto i = 0; i <= to; i++) {
                points.push_back({ x1 + (i * xDirection), y1 + (i * yDirection) });
            }
        }

        result.push_back({ points });
    }

    return result;
}

u32 calculate_intersects(const std::vector<VentCoordinate>& input) {
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
    const auto input = parse_input();
    {
        auto coordinates = calculate_coordinates<false>(input);
        const auto first = calculate_intersects(coordinates);
        std::cout << "first answer: " << first << std::endl;
    }

    {
        auto coordinates = calculate_coordinates<true>(input);
        const auto second = calculate_intersects(coordinates);
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
