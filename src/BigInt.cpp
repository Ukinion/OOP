#include "big_int.h"

big_int::BigInt::BigInt() {
    sign_ = char_const::kCharPlus;
}

big_int::BigInt::BigInt(int small_int) {
    if(IsNegative(small_int)) {
        sign_ = char_const::kCharMinus;

        if (IsIntMin(small_int)) {
            big_int_ = std::to_string(int_const::kIntMinNoSign);
        } else {
            small_int *= -1;
            big_int_ = std::to_string(small_int);
        }
    } else {
        sign_ = char_const::kCharPlus;
        big_int_ = std::to_string(small_int);
    }
}

big_int::BigInt::BigInt(std::string input) {
    if (CheckStrBegin(input)) {
        if (IsValid(input)) {
            if (IsNaN(*input.begin())) {
                sign_ = *input.begin();
                big_int_ = RemoveSign(input);
            } else{
                sign_ = char_const::kCharPlus;
                big_int_ = std::move(input);
            }
        } else {
            throw std::invalid_argument("NaN");
        }
    } else {
        throw std::invalid_argument("NaN");
    }
}

big_int::BigInt::BigInt(const BigInt& obj) : big_int_ (obj.big_int_) {
    sign_ = obj.sign_;;
}

big_int::BigInt::BigInt(BigInt&& obj) noexcept : big_int_ (std::move(obj.big_int_)) {
    std::swap(sign_, obj.sign_);
}

big_int::BigInt& big_int::BigInt::operator=(const BigInt& obj) {
    sign_ = obj.sign_;
    big_int_ = obj.big_int_;

    return *this;
}

big_int::BigInt& big_int::BigInt::operator=(BigInt&& obj) noexcept {
    big_int_ = std::move(obj.big_int_);
    std::swap(sign_, obj.sign_);

    return *this;
}

big_int::BigInt& big_int::BigInt::operator++() {
    BigInt obj (str_const::kIdentity);
    *this += obj;

    return *this;
}

const big_int::BigInt big_int::BigInt::operator++(int) {
    BigIntPtrU prev_val (new BigInt(*this));
    ++(*this);

    return *prev_val;
}

big_int::BigInt& big_int::BigInt::operator--() {
    BigInt obj (str_const::kIdentity);
    *this -= obj;

    return *this;
}

big_int::BigInt big_int::BigInt::operator~() const {
    math_machine::Binary binary (*this);
    binary = (~binary);
    BigIntPtrU complement (new BigInt(binary.BinaryToBigInt()));

    return *complement;
}

const big_int::BigInt big_int::BigInt::operator--(int) {
    BigIntPtrU prev_val (new BigInt(*this));
    --(*this);

    return *prev_val;
}

big_int::BigInt& big_int::BigInt::operator+=(const BigInt& obj) {
    *this = *this + obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator-=(const BigInt& obj) {
    *this = *this - obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator*=(const BigInt& obj) {
    *this = *this * obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator^=(const BigInt& obj) {
    *this = *this ^ obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator/=(const BigInt& obj) {
    *this = *this / obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator%=(const BigInt& obj) {
    *this = *this % obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator&=(const BigInt& obj) {
    *this = *this & obj;
    return *this;
}

big_int::BigInt& big_int::BigInt::operator|=(const BigInt& obj) {
    *this = *this | obj;
    return *this;
}

big_int::BigInt big_int::BigInt::operator+() const {
    BigIntPtrU ptr (new BigInt(*this));
    ptr->sign_ = char_const::kCharPlus;

    return *ptr;
};

big_int::BigInt big_int::BigInt::operator-() const {
    BigIntPtrU bigInt (new BigInt(*this));
    bigInt->sign_ = ChangeSign(sign_);

    return *bigInt;
}

bool big_int::BigInt::operator==(const BigInt& obj) const {
    if (sign_ == obj.sign_) {
        if (big_int_ == obj.big_int_) {
            return true;
        }
    }
    return false;
}

bool big_int::BigInt::operator!=(const BigInt& obj) const {
    return !(*this == obj);
}

bool big_int::BigInt::operator<(const BigInt& obj) const {
    if (sign_ < obj.sign_) {
        return false;
    }

    if (sign_ > obj.sign_) {
        return true;
    }

    if (sign_ == char_const::kCharPlus) {
        if (CompareStrNumber(this->big_int_, obj.big_int_) == int_const::kLess) {
            return true;
        }
    } else {
        if (CompareStrNumber(this->big_int_, obj.big_int_) == int_const::kGreater) {
            return true;
        }
    }

    return false;
}

bool big_int::BigInt::operator>(const BigInt& obj) const {
    if (obj.sign_ == sign_) {
        if (obj.big_int_ == big_int_) {
            return false;
        }
    }

    return !(*this < obj);
}

bool big_int::BigInt::operator<=(const BigInt&obj) const {
    if ((*this < obj) || (*this == obj)) {
        return true;
    }

    return false;
}

bool big_int::BigInt::operator>=(const BigInt& obj) const {
    if ((*this > obj) || (*this == obj)) {
        return true;
    }

    return false;
}

big_int::BigInt::operator int() const {
    if (IsOverInt(big_int_, sign_)) {
        BigInt int_min (int_const::kIntMin);
        BigInt int_max (int_const::kIntMax);
        BigInt one (str_const::kIdentity);
        BigInt int_range_length (str_const::kIntRange);
        BigInt steps;
        BigInt casted;

        if (sign_ == char_const::kCharPlus) {
            steps = (*this - int_max) % int_range_length;
            casted = int_min + steps - one;
        } else {
            steps = (+(*this) + int_min) % int_range_length;
            casted = int_max - steps + one;
        }

        return casted.BigIntToInt();
    }

    return this->BigIntToInt();
}

int big_int::BigInt::BigIntToInt() const {
    Multiplier multiplier;
    int i_num = 0;
    int i = 0;

    for (kStringIterR cur_sym = big_int_.rbegin(); cur_sym != big_int_.rend(); ++cur_sym) {
        i_num += CharToNum(*cur_sym)*multiplier.Power<int>(int_const::kDecRadix, i);
        ++i;
    }

    if (sign_ == char_const::kCharMinus) {
        i_num *= -1;
    }

    return i_num;
}

big_int::BigInt::operator std::string() const {
    return GetRealNumber();
}

size_t big_int::BigInt::size() const {
    return sizeof(*this);
}

std::string big_int::BigInt::GetNumberNoSign() const {
    return big_int_;
};

std::string big_int::BigInt::GetRealNumber() const {
    if (sign_ == char_const::kCharPlus) {
        return big_int_;
    }

    std::string neg_number = sign_ + big_int_;
    return neg_number;
}

char big_int::BigInt::GetSign() const {
    return sign_;
}

big_int::BigInt big_int::operator+(const BigInt& op1, const BigInt& op2) {
    if (op1.sign_ == op2.sign_) {
        BigIntPtrU res_number (new BigInt());
        res_number->sign_ = op1.sign_;
        std::string num1 = op1.big_int_;
        std::string num2 = op2.big_int_;

        res_number->big_int_ = res_number->AddStrNums(num1, num2);
        return *res_number;
    } else {
        if (op1.sign_ == char_const::kCharPlus) {
            return op1 - (-op2);
        }

        return op2 - (-op1);
    }
}

big_int::BigInt big_int::operator-(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    if (op1.sign_ != op2.sign_) {
        return op1 + -op2;
    } else {
        BigIntPtrU res_number (new BigInt());
        std::string ld_number;
        std::string sub_number;
        ld_number = res_number->GetLeadingNum(op1.big_int_, op2.big_int_, sub_number);

        if (ld_number == op1.big_int_) {
            res_number->sign_ = op1.sign_;
        } else {
            res_number->sign_ = res_number->ChangeSign(op2.sign_);
        }

        res_number->big_int_ = res_number->DiffStrNums(ld_number, sub_number);
        return *res_number;
    }
}

big_int::BigInt big_int::operator*(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    BigIntPtrU res_number (new BigInt());
    std::string ld_number;
    std::string sub_number;

    ld_number = res_number->GetLeadingNum(op1.big_int_, op2.big_int_, sub_number);
    res_number->sign_ = res_number->DefineNewSign(op1.sign_, op2.sign_);
    res_number->big_int_ = res_number->ColMultiplication(ld_number, sub_number);
    return *res_number;
}



big_int::BigInt big_int::operator/(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    BigInt zero (str_const::kZero);

    if (op2 != zero) {
        if (op1 == zero) {
            return zero;
        }

        BigIntPtrU res_number (new BigInt());

        if (res_number->CompareStrNumber(op2.big_int_, str_const::kLongLongMax) == int_const::kGreater) {
            BigInt dividend (+op1);
            BigInt divider = +op2;
            std::string product = str_const::kZero;
            std::string help_add = str_const::kIdentity;

            char sign_in_product = res_number->DefineNewSign(op1.sign_, op2.sign_);

            while (dividend >= divider) {
                dividend -= +op2;
                product = res_number->AddStrNums(product, help_add);
            }

            res_number->big_int_ = std::move(product);
            res_number->sign_ = sign_in_product;
        } else {
            res_number->big_int_ = res_number->CornerDivision(op1.big_int_, op2.big_int_);
            res_number->sign_ =  res_number->DefineNewSign(op1.sign_, op2.sign_);
        }
        return *res_number;
    } else {
        throw std::invalid_argument("Division by zero");
    }
}

big_int::BigInt big_int::operator%(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    return op1 - (op1/op2)*op2;
}

big_int::BigInt big_int::operator^(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    math_machine::Binary num1_res (op1);
    math_machine::Binary num2 (op2);

    num1_res ^= num2;;
    return num1_res.BinaryToBigInt();
}

big_int::BigInt big_int::operator&(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    math_machine::Binary num1_res (op1);
    math_machine::Binary num2 (op2);

    num1_res &= num2;;
    return num1_res.BinaryToBigInt();
}

big_int::BigInt big_int::operator|(const big_int::BigInt& op1, const big_int::BigInt& op2) {
    math_machine::Binary num1_res (op1);
    math_machine::Binary num2 (op2);

    num1_res |= num2;
    return num1_res.BinaryToBigInt();
}

std::ostream& big_int::operator<<(std::ostream& out, const big_int::BigInt& bigInt) {
    if (bigInt.sign_ == char_const::kCharPlus) {
        return out << bigInt.big_int_;
    }
    out << bigInt.sign_ << bigInt.big_int_;
    return out;
}

std::istream& big_int::operator>>(std::istream& in, BigInt& bigInt) {
    std::string input;
    in >> input;

    if (!bigInt.IsValid(input)) {
        throw std::invalid_argument("NaN");
    }

    BigInt tmp (input);
    bigInt = std::move(input);
    return in;
}

big_int::BigInt::~BigInt() {}
