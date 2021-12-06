#include <common.h>
#include <set>

class BingoBoard {
public:
    std::vector<std::vector<u32>> data;
    std::vector<std::vector<bool>> marked;

    BingoBoard(const std::vector<std::vector<u32>>& _board) {
        data = _board;
        for (auto&& vec : data) {
            std::vector<bool> marks;
            for (auto&& item : vec) {
                marks.push_back(false);
            }
            marked.push_back(marks);
        }
    }
};

class BingoSystem {
public:
    std::vector<u32> numbers;
    std::vector<BingoBoard> boards;

    BingoSystem(const std::vector<u32>& _numbers, const std::vector<BingoBoard>& _boards) {
        numbers = _numbers;
        boards = _boards;
    }
};

auto parse_input() {
    std::ifstream ifs("input");
    std::vector<std::string> vec;
    ranges::copy(ranges::istream_view<std::string>(ifs), std::back_inserter(vec));

    std::vector<u32> numbers;

    auto view = vec[0] | rviews::split(',');
    auto f = std::vector<std::string>(view.begin(), view.end());
    std::transform(f.begin(), f.end(), std::back_inserter(numbers),
        [](const std::string& str) { return std::stoi(str); });

    std::vector<BingoBoard> boards;
    for (int i = 1; i < vec.size(); i += 25) {

        auto itr = vec.begin() + i;

        std::vector<std::vector<u32>> data;
        for (int j = 0; j < 5; j++) {
            std::vector<u32> board;
            std::transform(itr, itr + 5, std::back_inserter(board),
                [](const std::string& str) { return std::stoi(str); });
            data.push_back(board);
            itr += 5;
        }

        boards.push_back(BingoBoard(data));
    }

    return BingoSystem(numbers, boards);
}

u32 first_solution(BingoSystem& bingoSystem) {
    for (auto number : bingoSystem.numbers) {
        for (auto& board : bingoSystem.boards) {

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (board.data[i][j] == number) {
                        board.marked[i][j] = true;
                    }
                }
            }
        }

        for (int k = 0; k < bingoSystem.boards.size(); k++) {
            auto& board = bingoSystem.boards[k];
            for (int i = 0; i < 5; i++) {
                bool rowsTrue = true;
                bool columnsTrue = true;
                for (int j = 0; j < 5; j++) {
                    if (!board.marked[j][i]) {
                        columnsTrue = false;
                    }
                    if (!board.marked[i][j]) {
                        rowsTrue = false;
                    }
                }

                if (columnsTrue || rowsTrue) {
                    int unmarkedSum = 0;
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (!board.marked[i][j]) {
                                unmarkedSum += board.data[i][j];
                            }
                        }
                    }

                    return unmarkedSum * number;
                }
            }
        }
    }

    return 0;
}

u32 second_solution(BingoSystem& bingoSystem) {
    std::set<u32> winning_boards;
    for (auto number : bingoSystem.numbers) {
        for (auto& board : bingoSystem.boards) {

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (board.data[i][j] == number) {
                        board.marked[i][j] = true;
                    }
                }
            }
        }

        for (int k = 0; k < bingoSystem.boards.size(); k++) {
            auto& board = bingoSystem.boards[k];
            for (int i = 0; i < 5; i++) {
                bool rowsTrue = true;
                bool columnsTrue = true;
                for (int j = 0; j < 5; j++) {
                    if (!board.marked[j][i]) {
                        columnsTrue = false;
                    }
                    if (!board.marked[i][j]) {
                        rowsTrue = false;
                    }
                }

                if (columnsTrue || rowsTrue) {
                    if (bingoSystem.boards.size() - 1 == winning_boards.size()) {
                        if (winning_boards.contains(k)) {
                            continue;
                        }
                    }
                    else {
                        winning_boards.insert(k);
                        continue;
                    }

                    int unmarkedSum = 0;
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (!board.marked[i][j]) {
                                unmarkedSum += board.data[i][j];
                            }
                        }
                    }

                    return unmarkedSum * number;
                }
            }
        }
    }

    return 0;
}

int main() {
    {
        auto input = parse_input();
        const auto first = first_solution(input);
        std::cout << "first answer: " << first << std::endl;
    }

    {
        auto input = parse_input();
        const auto second = second_solution(input);
        std::cout << "second answer: " << second << std::endl;
    }

    return 0;
}
