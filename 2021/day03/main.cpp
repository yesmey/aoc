#include <common.h>
#include <bitset>

const i32 convert_to_binary(const std::string& str) {
    const int binary_base = 2;
    return std::stoi(str, 0, binary_base);
}

auto parse_input() {
    std::ifstream ifs("input");
    std::vector<std::string> vec;
    ranges::copy(ranges::istream_view<std::string>(ifs), std::back_inserter(vec));
    return vec;
}

u32 first_solution(const std::vector<std::string>& input) {
    /*
        todo: should be able to rewrite with bitset instead, something like this
        const size_t width = 12;
        std::array<u32, width> oneCount;
        oneCount.fill(0);

        u32 length = 0;
        for (auto set : std::ranges::istream_view<std::bitset<width>>(s)) {
            for (int i = 0; i < width; i++) {
                oneCount[i] += set[i];
            }
            length++;
        }
    */

    const auto input_length = input.size();
    const auto row_length = input[0].length();

    std::map<u32, u32> gamma;
    for (int i = 0; i < row_length; i++) {
        gamma[i] = 0;
    }

    for (int i = 0; i < row_length; i++) {
        for (int j = 0; j < input_length; j++) {
            if (input[j][i] == '1')
                gamma[i]++;
        }
    }

    std::string gamma_rate = std::string(row_length, '0');
    std::string flipped_gamma_rate = std::string(row_length, '1');
    for (int i = 0; i < row_length; i++) {
        if (gamma[i] > input_length / 2) {
            gamma_rate[i] = '1';
            flipped_gamma_rate[i] = '0';
        }
    }

    i32 gamma_number = convert_to_binary(gamma_rate);
    i32 flipped_gamma_number = convert_to_binary(flipped_gamma_rate);

    return gamma_number * flipped_gamma_number;
}

u32 second_solution(const std::vector<std::string>& input) {
    
    std::vector<std::string> oxygen_rating = input;
    u32 index = 0;
    while (oxygen_rating.size() > 1) {
        u32 oneBitCount = 0;
        for (auto&& x : oxygen_rating) {
            if (x[index] == '1')
                oneBitCount++;
        }
        
        char mostCommonValue =
            oxygen_rating.size() - oneBitCount <= oneBitCount ? '1' : '0';

        std::erase_if(oxygen_rating, [&index, &mostCommonValue](std::string& x) {
            return x[index] != mostCommonValue;
        });

        index++;
    }

    std::vector<std::string> co2_rating = input;
    index = 0;
    while (co2_rating.size() > 1) {
        u32 oneBitCount = 0;
        for (auto&& x : co2_rating) {
            if (x[index] == '1')
                oneBitCount++;
        }

        char mostCommonValue =
            co2_rating.size() - oneBitCount <= oneBitCount ? '1' : '0';

        std::erase_if(co2_rating, [&index, &mostCommonValue](std::string& x) {
            return x[index] == mostCommonValue;
        });

        index++;
    }

    return convert_to_binary(oxygen_rating[0]) * convert_to_binary(co2_rating[0]);
}

int main() {
    const auto input = parse_input();

    const auto first = first_solution(input);
    std::cout << "first answer: " << first << std::endl;

    const auto second = second_solution(input);
    std::cout << "second answer: " << second << std::endl;

    return 0;
}
