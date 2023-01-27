#include "math_machine.h"

std::string math_machine::Multiplier::ColMultiplication(const std::string& str1, const std::string& str2) {
    StringManager automaton;
    LogicAnalyzer analyzer;
    Summator summator;
    std::string res_number (str_const::kZero);
    int remainder = 0;
    int zero_count = 0;

    for (auto cur_str2_sym = str2.rbegin(); cur_str2_sym != str2.rend(); ++cur_str2_sym) {
        std::string intrmdte_mul;
        int num1 = automaton.CharToNum(*cur_str2_sym);

        for (auto cur_str1_sym = str1.rbegin(); cur_str1_sym != str1.rend(); ++cur_str1_sym) {
            int num2 = automaton.CharToNum(*cur_str1_sym);
            int product = num1 * num2 + remainder;

            if (analyzer.IsOverflow(product)) {
                remainder = product / int_const::kDecRadix;
                intrmdte_mul.insert(intrmdte_mul.begin(), automaton.NumToChar(product % int_const::kDecRadix));
            } else {
                remainder = 0;
                intrmdte_mul.insert(intrmdte_mul.begin(), automaton.NumToChar(product));
            }
        }

        if (remainder) {
            intrmdte_mul.insert(intrmdte_mul.begin(), automaton.NumToChar(remainder));
            remainder = 0;
        }

        for (int i = 0; i < zero_count; ++i) {
            intrmdte_mul.push_back(char_const::kZero);
        }

        ++zero_count;
        automaton.EqualizeStrNums(res_number, intrmdte_mul);
        res_number = summator.AddStrNums(res_number, intrmdte_mul);
    }

    automaton.DeleteLeadingZero(res_number);
    return res_number;
}