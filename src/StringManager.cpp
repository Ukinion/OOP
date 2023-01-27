#include "math_machine.h"

std::string math_machine::StringManager::RemoveSign(const std::string& str) {
    std::string res (str.begin() + 1, str.end());
    return res;
}

std::string math_machine::StringManager::GetLeadingNum(const std::string& str1, const std::string& str2, std::string& sub_str) {
    LogicAnalyzer analyzer;

    if ((analyzer.CompareStrNumber(str1, str2) == int_const::kLess) || (analyzer.CompareStrNumber(str1, str2) == int_const::kEqual)) {
        sub_str = str1;
        return str2;
    } else {
        sub_str = str2;
        return str1;
    }
}

void math_machine::StringManager::EqualizeStrNums(std::string& number1, std::string& number2) {
    if (number1.size() > number2.size()) {
        auto count = (number1.size() - number2.size());

        for (StringSize i = 0; i < count; ++i) {
            number2.insert(number2.begin(), char_const::kZero);
        }
    } else {
        if (number1.size() < number2.size()) {
            auto count = (number2.size() - number1.size());

            for (StringSize i = 0; i < count; ++i) {
                number1.insert(number1.begin(), char_const::kZero);
            }
        }
    }
}

void math_machine::StringManager::DeleteLeadingZero(std::string& str) {
    auto cur_sym = str.begin();
    while (cur_sym != (str.end() - 1) && *cur_sym == char_const::kZero) {
        ++cur_sym;
    }

    std::string tmp (cur_sym, str.end());
    str = std::move(tmp);
}

int math_machine::StringManager::CharToNum(char sym) const {
    return sym - char_const::kZero;
}

long long math_machine::StringManager::StringToNum(const std::string& str) {
    Multiplier multiplier;
    long long num = 0;
    long long i = 0;

    for (kStringIterR sym = str.rbegin(); sym != str.rend(); ++sym) {
        num += CharToNum(*sym)*multiplier.Power<long long>(int_const::kDecRadix, i);
        ++i;
    }

    return num;
}

char math_machine::StringManager::ChangeSign(const char prev_sign) const {
    return static_cast<char>(int_const::kSignChanger - prev_sign);
}

char math_machine::StringManager::DefineNewSign(char sign1, char sign2) {
    int hash = sign1 + sign2;

    if (hash == int_const::kSignChanger) {
        return char_const::kCharMinus;
    }

    if (hash == int_const::kPlusPlus || hash == int_const::kMinusMinus) {
        return char_const::kCharPlus;
    }

    return char_const::kZero;
}

void math_machine::StringManager::AddBits(const std::string& bigger_num, std::string& smaller_num) {
    if (*smaller_num.begin() == bin_const::kBitMinus) {
        while (smaller_num.size() != bigger_num.size()) {
            smaller_num.insert(smaller_num.begin(), bin_const::kBitMinus);
        }
    } else {
        while (smaller_num.size() != bigger_num.size()) {
            smaller_num.insert(smaller_num.begin(), bin_const::kBitPlus);
        }
    }
}



