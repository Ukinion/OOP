#ifndef LAB1_BIGINT_BIG_INT_H
#define LAB1_BIGINT_BIG_INT_H

#include "constants.h"
#include "math_machine.h"

namespace big_int {

    class BigInt : public math_machine::LogicAnalyzer, math_machine::StringManager,
            math_machine::Summator, math_machine::Subtractor, math_machine::Multiplier, math_machine::Divider {
    public:
      BigInt();
      BigInt(int);
      BigInt(std::string);
      BigInt(const BigInt&);
      BigInt(BigInt&&) noexcept;
      ~BigInt();

      BigInt& operator=(const BigInt&);
      BigInt& operator=(BigInt&&) noexcept;

      BigInt operator~() const;

      BigInt& operator++();
      const BigInt operator++(int);
      BigInt& operator--();
      const BigInt operator--(int);

      BigInt& operator+=(const BigInt&);
      BigInt& operator*=(const BigInt&);
      BigInt& operator-=(const BigInt&);
      BigInt& operator/=(const BigInt&);
      BigInt& operator^=(const BigInt&);
      BigInt& operator%=(const BigInt&);
      BigInt& operator&=(const BigInt&);
      BigInt& operator|=(const BigInt&);

      BigInt operator+() const;
      BigInt operator-() const;

      bool operator==(const BigInt&) const;
      bool operator!=(const BigInt&) const;
      bool operator<(const BigInt&) const;
      bool operator>(const BigInt&) const;
      bool operator<=(const BigInt&) const;
      bool operator>=(const BigInt&) const;

      operator int() const;
      operator std::string() const;

      size_t size() const;

      friend BigInt operator+(const BigInt&, const BigInt&);
      friend BigInt operator-(const BigInt&, const BigInt&);
      friend BigInt operator*(const BigInt&, const BigInt&);
      friend BigInt operator/(const BigInt&, const BigInt&);
      friend BigInt operator%(const BigInt&, const BigInt&);
      friend BigInt operator^(const BigInt&, const BigInt&);
      friend BigInt operator&(const BigInt&, const BigInt&);
      friend BigInt operator|(const BigInt&, const BigInt&);
      friend std::ostream& operator<<(std::ostream&, const BigInt&);
      friend std::istream& operator>>(std::istream&, BigInt&);

      std::string GetNumberNoSign() const;
      std::string GetRealNumber() const;
      char GetSign() const;
    private:
        int BigIntToInt() const;

        char sign_;
        std::string big_int_;
    };
    typedef std::unique_ptr<BigInt> BigIntPtrU;
}

namespace math_machine {
    class Binary {
    public:
         Binary();
         Binary(const big_int::BigInt&);
         Binary(const Binary&);

         Binary& operator=(const Binary&);

         Binary operator~() const;

         Binary& operator++();
         const Binary operator++(int);

         Binary& operator^=(const Binary&);
         Binary& operator&=(const Binary&);
         Binary& operator|=(const Binary&);

         friend Binary operator+(const Binary&, const Binary&);
         friend Binary operator^(const Binary&, const Binary&);
         friend Binary operator&(const Binary&, const Binary&);
         friend Binary operator|(const Binary&, const Binary&);

         std::string PrintBinary() const;
         big_int::BigInt BinaryToBigInt() const;
    private:
        std::string GetBinary(const big_int::BigInt&);
        std::string GetTwoComplement() const;
        std::string GetStdForm() const;
        void EqualizeBinNums(std::string&, std::string&) const;

        char bit_sign_;
        std::string two_complement_;
    };
}

#endif //LAB1_BIGINT_BIG_INT_H
