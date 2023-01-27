#ifndef LAB1_BIGINT_MATH_MACHINE_H
#define LAB1_BIGINT_MATH_MACHINE_H

#include "constants.h"

namespace math_machine {

    class LogicAnalyzer {
    public:
        bool IsNegative(int);
        bool IsIntMin(int);
        bool IsValid(const std::string&);
        bool IsNaN(char);
        bool CharXOR(const std::string&);
        bool CheckStrBegin(const std::string&);
        bool IsOverflow(int);
        bool IsUnderflow(int, int);
        bool IsEven(const std::string&);
        bool IsOverInt(const std::string&, char) const;
        int CompareStrNumber(const std::string&, const std::string&) const;
      };

    class StringManager {
    public:
        std::string RemoveSign(const std::string&);
        std::string GetLeadingNum(const std::string&, const std::string&, std::string&);
        void EqualizeStrNums(std::string&, std::string&);
        void DeleteLeadingZero(std::string&);
        int CharToNum(char) const;
        long long StringToNum(const std::string&);
        template<typename T>
        char NumToChar(T num) {
            return static_cast<char>(num + static_cast<T>(char_const::kZero));
        }
        char ChangeSign(char) const;
        char DefineNewSign(char, char);
        void AddBits(const std::string&, std::string&);
    };

    class Summator {
    public:
        std::string AddStrNums(std::string&, std::string&);
    };

    class Subtractor {
    public:
        std::string DiffStrNums(std::string&, std::string&);
    };

    class Multiplier {
    public:
        template<typename T>
        T Power(const T value, const T degree)  {
            T pow = 1;
            T remainder = 1;

            for (T i = 0; i < degree; ++i) {
                pow = remainder * value;
                remainder = pow;
            }

            return pow;
        }
        std::string ColMultiplication(const std::string&, const std::string&);
    };

    class Divider {
    public:
        unsigned long long DivideAndRemind(const std::string&, const std::string&, std::string&);
        std::string CornerDivision(const std::string&, const std::string&);
    };
};

#endif //LAB1_BIGINT_MATH_MACHINE_H
