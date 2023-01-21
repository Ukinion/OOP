#include "math_machine.h"

std::string math_machine::Summator::AddStrNums(std::string& str1, std::string& str2) {
    LogicAnalyzer analyzer;
    StringManager automaton;
    std::string res_number;
    int remainder = 0;

    automaton.EqualizeStrNums(str1, str2);
    for(auto cur_sym_str1 = str1.rbegin(), cur_sym_str2 = str2.rbegin(); cur_sym_str1 != str1.rend(); ++cur_sym_str1, ++cur_sym_str2) {
        int num1 = automaton.CharToNum(*cur_sym_str1);
        int num2 = automaton.CharToNum(*cur_sym_str2);
        int sum = num1 + num2 + remainder;

        if (analyzer.IsOverflow(sum)) {
            remainder = 1;
            res_number.insert(res_number.begin(), automaton.NumToChar(sum - int_const::kDecRadix));
        } else {
            remainder = 0;
            res_number.insert(res_number.begin(), automaton.NumToChar(sum));
        }
    }

    if (remainder) {
        res_number.insert(res_number.begin(), char_const::kRemainder);
    }

    return res_number;
}
