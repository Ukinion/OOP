#include "big_int.h"

using big_int::BigInt;
typedef std::unique_ptr<math_machine::Binary> BinaryUPtr;

math_machine::Binary::Binary() {
    bit_sign_ = bin_const::kBitPlus;
}

math_machine::Binary::Binary(const BigInt& bigInt) {
    two_complement_ = GetBinary(bigInt);
    bit_sign_ = *two_complement_.begin();
    two_complement_.erase(two_complement_.begin());
}

math_machine::Binary::Binary(const Binary& binary) : bit_sign_ (binary.bit_sign_) {
    two_complement_ = binary.two_complement_;
}

std::string math_machine::Binary::PrintBinary() const {
    std::string ret_bin = two_complement_;
    ret_bin.insert(ret_bin.begin(), bit_sign_);
    return ret_bin;
}

void math_machine::Binary::EqualizeBinNums(std::string& number1, std::string& number2) const {
    if (number1.size() == number2.size()) {
        return;
    }

    StringManager automaton;
    if (number1.size() > number2.size()) {
        automaton.AddBits(number1, number2);
    } else {
        automaton.AddBits(number2, number1);
    }
}

math_machine::Binary math_machine::Binary::operator~() const {
    BinaryUPtr complement (new Binary());
    StringManager automaton;

    for (auto cur_bit = two_complement_.rbegin(); cur_bit != two_complement_.rend(); ++cur_bit) {
        if (automaton.CharToNum(*cur_bit) ^ bin_const::kFlipBit) {
            complement->two_complement_.insert(complement->two_complement_.begin(), bin_const::kBitMinus);
        } else {
            complement->two_complement_.insert(complement->two_complement_.begin(), bin_const::kBitPlus);
        }
    }

    complement->bit_sign_ = automaton.NumToChar(bin_const::kFlipBit ^ automaton.CharToNum(bit_sign_));
    return *complement;
}

math_machine::Binary& math_machine::Binary::operator=(const Binary& obj) {
    two_complement_ = obj.two_complement_;
    bit_sign_ = obj.bit_sign_;

    return *this;
}

math_machine::Binary& math_machine::Binary::operator++() {
    BigInt bigInt_one (str_const::kIdentity);
    Binary binary_one (bigInt_one);
    *this = *this + binary_one;
    return *this;
}

const math_machine::Binary math_machine::Binary::operator++(int) {
    Binary prev_val (*this);
    Binary one;
    *this = *this + one;
    return prev_val;
}

math_machine::Binary& math_machine::Binary::operator^=(const Binary& rt_operand) {
    *this = *this ^ rt_operand;
    return *this;
}

math_machine::Binary& math_machine::Binary::operator&=(const Binary& rt_operand) {
    *this = *this & rt_operand;
    return *this;
}

math_machine::Binary& math_machine::Binary::operator|=(const Binary& rt_operand) {
    *this = *this | rt_operand;
    return *this;
}

math_machine::Binary math_machine::operator+(const Binary& op1, const Binary& op2) {
    StringManager automaton;
    BinaryUPtr sum_product (new Binary());
    std::string number1 = op1.PrintBinary();
    std::string number2 = op2.PrintBinary();
    int carry_flag = 0;

    sum_product->EqualizeBinNums(number1, number2);

    auto cur_bit_num1 = number1.rbegin();
    auto cur_bit_num2 = number2.rbegin();
    for (; cur_bit_num1 != number1.rend(); ++cur_bit_num1, ++cur_bit_num2) {
        int i_bit1 = automaton.CharToNum(*cur_bit_num1);
        int i_bit2 = automaton.CharToNum(*cur_bit_num2);

        if (i_bit1 ^ i_bit2 ^ carry_flag) {
            sum_product->two_complement_.insert(sum_product->two_complement_.begin(), bin_const::kBitMinus);
        } else {
            sum_product->two_complement_.insert(sum_product->two_complement_.begin(), bin_const::kBitPlus);
        }
        carry_flag = (i_bit2 & carry_flag) ^ (i_bit1 & carry_flag) ^ (i_bit1 & i_bit2);
    }

    sum_product->bit_sign_ = *sum_product->two_complement_.begin();
    sum_product->two_complement_.erase(sum_product->two_complement_.begin());
    return *sum_product;
}

math_machine::Binary math_machine::operator^(const Binary& op1, const Binary& op2) {
    BinaryUPtr result (new Binary());
    std::string number1 = op1.PrintBinary();
    std::string number2 = op2.PrintBinary();

    result->EqualizeBinNums(number1, number2);

    auto cur_bit_num1 = number1.rbegin();
    auto cur_bit_num2 = number2.rbegin();
    for(; cur_bit_num1 != number1.rend(); ++cur_bit_num1, ++cur_bit_num2) {
        if (*cur_bit_num1 == *cur_bit_num2) {
            result->two_complement_.insert(result->two_complement_.begin(), bin_const::kBitPlus);
        } else {
            result->two_complement_.insert(result->two_complement_.begin(), bin_const::kBitMinus);
        }
    }

    result->bit_sign_ = *result->two_complement_.begin();
    result->two_complement_.erase(result->two_complement_.begin());
    return *result;
}

math_machine::Binary math_machine::operator&(const Binary& op1, const Binary& op2) {
    BinaryUPtr result (new Binary());
    std::string number1 = op1.PrintBinary();
    std::string number2 = op2.PrintBinary();

    result->EqualizeBinNums(number1, number2);

    auto cur_bit_num1 = number1.rbegin();
    auto cur_bit_num2 = number2.rbegin();
    for(; cur_bit_num1 != number1.rend(); ++cur_bit_num1, ++cur_bit_num2) {
        if ((*cur_bit_num1 == bin_const::kBitMinus) && (*cur_bit_num2 == bin_const::kBitMinus)) {
            result->two_complement_.insert(result->two_complement_.begin(), bin_const::kBitMinus);
        } else {
            result->two_complement_.insert(result->two_complement_.begin(), bin_const::kBitPlus);
        }
    }

    result->bit_sign_ = *result->two_complement_.begin();
    result->two_complement_.erase(result->two_complement_.begin());
    return *result;
}

math_machine::Binary math_machine::operator|(const Binary& op1, const Binary& op2) {
    BinaryUPtr result (new Binary());
    std::string number1 = op1.PrintBinary();
    std::string number2 = op2.PrintBinary();

    result->EqualizeBinNums(number1, number2);

    auto cur_bit_num1 = number1.rbegin();
    auto cur_bit_num2 = number2.rbegin();
    for(; cur_bit_num1 != number1.rend(); ++cur_bit_num1, ++cur_bit_num2) {
        if ((*cur_bit_num1 == bin_const::kBitPlus) && (*cur_bit_num2 == bin_const::kBitPlus)) {
            result->two_complement_.insert(result->two_complement_.begin(), bin_const::kBitPlus);
        } else {
            result->two_complement_.insert(result->two_complement_.begin(), bin_const::kBitMinus);
        }
    }

    result->bit_sign_ = *result->two_complement_.begin();
    result->two_complement_.erase(result->two_complement_.begin());
    return *result;
}

std::string math_machine::Binary::GetBinary(const BigInt& num) {
    BigInt divider (str_const::kBinRadix);
    BigInt one (str_const::kIdentity);
    BigInt zero (str_const::kZero);
    BigInt bigInt (num);
    Binary res_val;

    if (+bigInt == zero) {
        res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitPlus);
        res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitPlus);
        return res_val.two_complement_;
    }

    while (+bigInt > one) {
        if (bigInt.IsEven(bigInt.GetNumberNoSign())) {
            res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitPlus);
        } else {
            res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitMinus);
        }
        bigInt /= divider;
    }

    if (+bigInt == zero) {
        res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitPlus);
    } else {
        res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitMinus);
    }

    if (bigInt.GetSign() == char_const::kCharPlus) {
        res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitPlus);
    } else {
        res_val.two_complement_ = res_val.GetTwoComplement();
        res_val.two_complement_.insert(res_val.two_complement_.begin(), bin_const::kBitMinus);
    }

    return res_val.two_complement_;
}

std::string math_machine::Binary::GetTwoComplement() const {
    Binary complement = ~(*this);
    (++complement).two_complement_.insert(complement.two_complement_.begin(), complement.bit_sign_);
    return complement.two_complement_;
}

std::string math_machine::Binary::GetStdForm() const {
    if (bit_sign_ == bin_const::kBitMinus) {
        return this->GetTwoComplement();
    } else {
        return two_complement_;
    }
}

big_int::BigInt math_machine::Binary::BinaryToBigInt() const {
    Multiplier multiplier;
    Summator summator;
    std::string bin_bigInt = this->GetStdForm();
    std::string dec_bigInt = str_const::kZero;
    std::string base = str_const::kBinRadix;
    std::string remainder = str_const::kIdentity;

    for (auto cur_bit = bin_bigInt.rbegin(); cur_bit != bin_bigInt.rend(); ++cur_bit) {
        if (*cur_bit == bin_const::kBitMinus) {
            dec_bigInt = summator.AddStrNums(dec_bigInt, remainder);
        }
        remainder = multiplier.ColMultiplication(base, remainder);
    }

    if (bit_sign_ == bin_const::kBitMinus) {
        dec_bigInt.insert(dec_bigInt.begin(), char_const::kCharMinus);
    }

    big_int::BigIntPtrU bigInt (new big_int::BigInt(dec_bigInt));
    return *bigInt;
}
