#include <common.h>
#include <sstream>

struct InputRow {
    std::vector<std::string> patterns;
    std::vector<std::string> output_values;
};

auto parse_input() {
    auto to_string = [](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); };
    auto not_empty = [](const std::string& str) { return str.length() > 0; };

    std::vector<InputRow> result;
    std::ifstream ifs("input");

    std::string line; // = "acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | fdgacbe cefdb cefbgd gcbe";
    while (std::getline(ifs, line)) {
        std::stringstream streamData(line);
        std::string patterns_str, output_values_str;
        std::getline(streamData, patterns_str, '|');
        std::getline(streamData, output_values_str, '|');

        std::vector<std::string> patterns;
        std::vector<std::string> output_values;

        ranges::copy(patterns_str | rviews::split(' ') | rviews::transform(to_string) | rviews::filter(not_empty), std::back_inserter(patterns));
        ranges::copy(output_values_str | rviews::split(' ') | rviews::transform(to_string) | rviews::filter(not_empty), std::back_inserter(output_values));

        result.push_back({ patterns, output_values });
    }

    return result;
}

u32 first_solution(const std::vector<InputRow>& input) {
    u32 known_digit = 0;
    for (auto&& row : input) {
        for (auto&& output_value : row.output_values) {
            switch (output_value.length()) {
                case 2:
                    known_digit++;
                    break;
                case 3:
                    known_digit++;
                    break;
                case 4:
                    known_digit++;
                    break;
                case 7:
                    known_digit++;
                    break;
            }
        }
    }
    return known_digit;
}

bool is_pattern_in_text(const std::string str, const std::string& pattern) {
    if (str.length() != pattern.length()) return false;

    for (auto chr : pattern) {
        if (ranges::find(str, chr) == str.end())
            return false;
    }
    return true;
}

u32 second_solution(const std::vector<InputRow>& input) {
    u32 output = 0;

    for (auto&& row : input) {
        /*
             0000
            1    2
            1    2
             3333
            4    5
            4    5
             6666
        */

        std::array<std::string, 10> digit_texts = {};
        std::array<char, 7> pattern = {};

        std::map<char, u32> occurances;
        for (auto&& input_pattern : row.patterns) {
            for (auto chr : input_pattern) {
                occurances[chr]++;
            }

            // already know these based on length
            switch (input_pattern.length()) {
                case 2:
                    digit_texts[1] = input_pattern;
                    break;
                case 3:
                    digit_texts[7] = input_pattern;
                    break;
                case 4:
                    digit_texts[4] = input_pattern;
                    break;
                case 7:
                    digit_texts[8] = input_pattern;
                    break;
            }
        }

        // some only occur in specific numbers
        for (const auto& [chr, count] : occurances) {
            switch (count) {
                case 4:
                    pattern[4] = chr;
                    break;
                case 6:
                    pattern[1] = chr;
                    break;
                case 9:
                    pattern[5] = chr;
                    break;
            }
        }

        // determine the letter for 2 since one only has two letters
        pattern[2] = (digit_texts[1][0] != pattern[5]) ? digit_texts[1][0] : digit_texts[1][1];

        // 0 and 2 has 8 chars and we already know pattern 2
        for (const auto& [chr, count] : occurances) {
            if (count == 8 && chr != pattern[2]) {
                pattern[0] = chr;
                break;
            }
        }

        // only 3 and 6 left
        /*
             xxxx
            x    x
            x    x
             3333
            x    x
            x    x
             6666
        */

        // 6 isn't in the known letter 4
        for (auto chr : digit_texts[4]) {
            if (ranges::find(pattern, chr) == pattern.end()) {
                pattern[3] = chr;
                break;
            }
        }

        // only 6 left, just check which char that hasnt been added yet
        const std::string allChars = "abcdefg";
        for (auto chr : allChars) {
            if (ranges::find(pattern, chr) == pattern.end()) {
                pattern[6] = chr;
                break;
            }
        }

        /*
             0000
            1    2
            1    2
             3333
            4    5
            4    5
             6666
        */
        std::string display_text;
        // dont know how to do this, this will have to do for now, lol
        for (auto& output_value : row.output_values) {
            if (is_pattern_in_text(output_value, { pattern[0], pattern[1], pattern[2], pattern[4], pattern[5], pattern[6] })) {
                display_text += "0";
            }

            if (is_pattern_in_text(output_value, {pattern[2], pattern[5]})) {
                display_text += "1";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[2], pattern[3], pattern[4], pattern[6] })) {
                display_text += "2";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[2], pattern[3], pattern[5], pattern[6] })) {
                display_text += "3";
            }

            else if (is_pattern_in_text(output_value, { pattern[1], pattern[2], pattern[3], pattern[5] })) {
                display_text += "4";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[1], pattern[3], pattern[5], pattern[6] })) {
                display_text += "5";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[1], pattern[3], pattern[4], pattern[5], pattern[6] })) {
                display_text += "6";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[2], pattern[5] })) {
                display_text += "7";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[1], pattern[2], pattern[3], pattern[4], pattern[5], pattern[6] })) {
                display_text += "8";
            }

            else if (is_pattern_in_text(output_value, { pattern[0], pattern[1], pattern[2], pattern[3], pattern[5], pattern[6] })) {
                display_text += "9";
            }
        }

        output += std::stoi(display_text);
    }

    return output;
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
