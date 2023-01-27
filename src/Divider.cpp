#include "math_machine.h"

unsigned long long math_machine::Divider::DivideAndRemind(const std::string& step_remainder, const std::string& str2, std::string& res_number) {
    StringManager automaton;
    unsigned long long num1 = automaton.StringToNum(step_remainder);
    unsigned long long num2 = automaton.StringToNum(str2);
    unsigned long long product = num1 / num2;

    res_number += std::to_string(product);
    return num1 - num2 * product;
}

std::string math_machine::Divider::CornerDivision(const std::string& op1, const std::string& divider) {
    LogicAnalyzer analyzer;
    std::string res_number;
    std::string step_remainder;
    std::string dividend = op1;
    unsigned long long diff_remainder;
    bool st_flag = true;

    if (divider.size() > dividend.size()) {
        return str_const::kZero;
    }

    if (dividend.size() == divider.size()) {
        if (analyzer.CompareStrNumber(dividend, divider) == int_const::kLess) {
            res_number.push_back(char_const::kZero);
        } else {
            DivideAndRemind(dividend, divider, res_number);
        }
        return  res_number;
    }

    dividend.push_back(char_const::kStop);
    auto cur_pos = dividend.begin();

    while (true) {
        if (cur_pos == dividend.end()) {
            break;
        }

        while (analyzer.CompareStrNumber(step_remainder, divider) == int_const::kLess) {
            if (*cur_pos == char_const::kStop) {
                break;
            }
            if (!st_flag) {
                res_number.push_back(char_const::kZero);
            }
            step_remainder.push_back(*(cur_pos++));
        }
        st_flag = false;

        diff_remainder = DivideAndRemind(step_remainder, divider, res_number);
        if (diff_remainder) {
            step_remainder = std::to_string(diff_remainder) + std::string (int_const::kUnitLength, *(cur_pos++));
        } else {
            step_remainder.clear();
            step_remainder.push_back(*(cur_pos++));
        }
    }

    return res_number;
}


