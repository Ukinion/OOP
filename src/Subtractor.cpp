#include "math_machine.h"

std::string math_machine::Subtractor::DiffStrNums(std::string& str1, std::string& str2) {
    StringManager automaton;
    LogicAnalyzer analyzer;
    std::string res_number;

    automaton.EqualizeStrNums(str1, str2);

    for (auto cur_str1_sym = str1.rbegin(), cur_str2_sym = str2.rbegin(); cur_str1_sym != str1.rend(); ++cur_str1_sym, ++cur_str2_sym) {
        int num1 = automaton.CharToNum(*cur_str1_sym);
        int num2 = automaton.CharToNum(*cur_str2_sym);

        if (analyzer.IsUnderflow(num1, num2)) {
            auto next_str1_sym = cur_str1_sym + 1;

            while (*next_str1_sym == char_const::kZero) {
                *next_str1_sym = char_const::kNine;
                next_str1_sym++;
            }

            --(*next_str1_sym);
            res_number.insert(res_number.begin(), automaton.NumToChar(num1 + int_const::kDecRadix - num2));
        } else {
            res_number.insert(res_number.begin(), automaton.NumToChar(num1 - num2));
        }
    }

    automaton.DeleteLeadingZero(res_number);
    return res_number;
}