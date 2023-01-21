#include "math_machine.h"

bool math_machine::LogicAnalyzer::IsNegative(int num) {
    return (num >> 1) & int_const::kSignBitMask;
}

bool math_machine::LogicAnalyzer::IsIntMin(int num) {
    return (num ^ int_const::kIntMin) == 0;
}

bool math_machine::LogicAnalyzer::IsValid(const std::string& str) {
    for (auto cur_sym = str.begin()+1; cur_sym != str.end(); ++cur_sym) {
        if  (IsNaN(*cur_sym)) {
            return false;
        }
    }

    return true;
}

bool math_machine::LogicAnalyzer::IsNaN(char symbol) {
    return (symbol < char_const::kZero) || (symbol > char_const::kNine);
}

bool math_machine::LogicAnalyzer::CharXOR(const std::string& str) {
    return (*str.begin() != char_const::kCharMinus) == (*str.begin() == char_const::kCharPlus);
}

bool math_machine::LogicAnalyzer::CheckStrBegin(const std::string& str) {
    return !LogicAnalyzer::IsNaN(*str.begin()) || LogicAnalyzer::CharXOR(str);
}

bool math_machine::LogicAnalyzer::IsOverflow(int num) {
    return num >= int_const::kDecRadix;
}

bool math_machine::LogicAnalyzer::IsUnderflow(int num1, int num2) {
    return num1 < num2;
}

bool math_machine::LogicAnalyzer::IsEven(const std::string& num) {
    StringManager automaton;

    if ((automaton.CharToNum(*num.rbegin()) % 2) == 0) {
        return true;
    }
    return false;
}

bool math_machine::LogicAnalyzer::IsOverInt(const std::string& number, char sign) const {
    if (sign == char_const::kCharPlus && CompareStrNumber(number, str_const::kIntMax) != int_const::kGreater) {
        return false;
    }

    if (sign == char_const::kCharMinus && CompareStrNumber(number , str_const::kIntMin) != int_const::kGreater) {
        return false;
    }

    return true;
}

int math_machine::LogicAnalyzer::CompareStrNumber(const std::string& number1, const std::string& number2) const {
    StringManager automaton;
    std::string cp_number1 = number1;
    std::string cp_number2 = number2;

    automaton.DeleteLeadingZero(cp_number1);
    automaton.DeleteLeadingZero(cp_number2);

    if (cp_number1.size() < cp_number2.size()) {
        return int_const::kLess;
    }

    if (cp_number1.size() > cp_number2.size()) {
        return int_const::kGreater;
    }

    auto cur_dig_number1 = cp_number1.begin();
    auto cur_dig_number2 = cp_number2.begin();
    for (; cur_dig_number1 != cp_number1.end(); ++cur_dig_number1, ++cur_dig_number2) {
        if (*cur_dig_number1 < *cur_dig_number2) {
            return int_const::kLess;
        }

        if (*cur_dig_number1 > *cur_dig_number2) {
            return int_const::kGreater;
        }
    }

    return int_const::kEqual;
}