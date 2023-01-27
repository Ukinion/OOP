#ifndef LAB1_BIGINT_CONSTANTS_H
#define LAB1_BIGINT_CONSTANTS_H

#include <iostream>
#include <memory>

typedef std::string::const_reverse_iterator kStringIterR;
typedef std::string::size_type StringSize;


namespace char_const {
    static const auto kCharPlus = '+';
    static const auto kCharMinus = '-';
    static const auto kZero = '0';
    static const auto kStop = 's';
    static const auto kNine = '9';
    static const auto kRemainder = '1';
}

namespace str_const {
    static const std::string kIntMax = "2147483647";
    static const std::string kIntMin = "2147483648";
    static const std::string kIntRange = "4294967296";
    static const std::string kZero = "0";
    static const std::string kIdentity = "1";
    static const std::string kLongLongMax = "9223372036854775807";
    static const std::string kBinRadix = "2";
}

namespace int_const {

    static const auto kSignBitMask = 1073741824;
    static const auto kIntMinNoSign = 2147483648;
    static const auto kIntMin = -2147483648;
    static const auto kIntMax = 2147483647;
    static const auto kDecRadix = 10;
    static const auto kLess = 0;
    static const auto kEqual = 1;
    static const auto kGreater = 2;
    static const auto kSignChanger = 88;
    static const auto kPlusPlus = 86;
    static const auto kMinusMinus = 90;
    static const auto kUnitLength = 1;
}

namespace bin_const {
    static const auto kBitPlus = '0';
    static const auto kBitMinus = '1';
    static const auto kFlipBit = 1;
}

#endif //LAB1_BIGINT_CONSTANTS_H
