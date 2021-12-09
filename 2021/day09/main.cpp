#include <common.h>

using Grid = std::vector<std::vector<u32>>;

auto parse_input() {
    std::ifstream ifs("input");

    std::vector<std::string> vec;
    ranges::copy(ranges::istream_view<std::string>(ifs), std::back_inserter(vec));

    Grid grid;

    for (auto&& row : vec) {
        std::vector<u32> row_vec;
        for (auto chr : row) {
            row_vec.push_back(chr - 48);
        }
        grid.push_back(row_vec);
    }


    return grid;
}

auto get_low_points(const Grid& input) {
    std::vector<std::pair<i32, i32>> low_points;

    const i32 col_size = input[0].size();
    const i32 row_size = input.size();

    for (i32 row = 0; row < row_size; row++) {
        for (i32 col = 0; col < col_size; col++) {
            auto point = input[row][col];

            // top
            if (row != 0) {
                if (input[row - 1][col] <= point) {
                    continue;
                }
            }

            // bottom
            if (row < row_size - 1) {
                if (input[row + 1][col] <= point) {
                    continue;
                }
            }

            // right
            if (col < col_size - 1) {
                if (input[row][col + 1] <= point) {
                    continue;
                }
            }

            // left
            if (col != 0) {
                if (input[row][col - 1] <= point) {
                    continue;
                }
            }

            low_points.push_back(std::make_pair(row, col));
        }
    }

    return low_points;
}

u32 first_solution(const Grid& input) {
    auto risk_level = 0;
    for (auto&& [row, col] : get_low_points(input)) {
        risk_level += (input[row][col] + 1);
    }
    return risk_level;
}

u32 find_basin(Grid& grid, i32 row, i32 col) {
    if (grid[row][col] == 9)
        return 0;

    grid[row][col] = 9; // mark current position as "walked" so we don't walk on it twice

    //std::cout << "Walking " << row << " " << col << "\n";

    u32 basins = 1;
    // walk top
    if (row != 0) {
        basins += find_basin(grid, row - 1, col);
    }

    // walk bottom
    if (row < grid.size() - 1) {
        basins += find_basin(grid, row + 1, col);
    }

    // walk right
    if (col != 0) {
        basins += find_basin(grid, row, col - 1);
    }

    // walk left
    if (col < grid[0].size() - 1) {
        basins += find_basin(grid, row, col + 1);
    }

    return basins;
}

u32 second_solution(const Grid& input) {
    const i32 col_size = input[0].size();
    const i32 row_size = input.size();

    Grid mutable_grid = input;

    std::array<u32, 3> largest_basins = { };
    for (i32 row = 0; row < row_size; row++) {
        for (i32 col = 0; col < col_size; col++) {
            u32 basin_size = find_basin(mutable_grid, row, col);
            if (basin_size == 0) continue;

            if (basin_size > largest_basins[0]) {
                largest_basins[2] = largest_basins[1];
                largest_basins[1] = largest_basins[0];
                largest_basins[0] = basin_size;
            }
            else if (basin_size > largest_basins[1]) {
                largest_basins[2] = largest_basins[1];
                largest_basins[1] = basin_size;
            }
            else if (basin_size > largest_basins[2]) {
                largest_basins[2] = basin_size;
            }
        }
    }

}

int main() {
    const auto input = parse_input();

    {
        const auto first = first_solution(input);
        std::cout << "first answer: " << first << std::endl;
    }

    {
        const auto second = second_solution(input);
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
