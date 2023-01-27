#include "gtest/gtest.h"
#include "../src/big_int.h"


namespace method_test {

    TEST(Constructor, All) {
        big_int::BigInt num;
        EXPECT_EQ("", num.GetRealNumber());

        big_int::BigInt num1 ("+351295");
        EXPECT_EQ("351295", num1.GetRealNumber());

        big_int::BigInt num2 ("-123412342135235");
        EXPECT_EQ("-123412342135235", num2.GetRealNumber());

        big_int::BigInt num3 (23463867);
        EXPECT_EQ("23463867", num3.GetRealNumber());

        big_int::BigInt num4 (-23468888);
        EXPECT_EQ("-23468888", num4.GetRealNumber());

        big_int::BigInt num5 (num1);
        EXPECT_EQ(num1.GetRealNumber(), num5.GetRealNumber());

        big_int::BigInt num6(std::move(num2));
        EXPECT_EQ("-123412342135235", num6.GetRealNumber());
    }

    TEST(BadInput, ConstructorReaction) {
        EXPECT_ANY_THROW(big_int::BigInt num("asdf12341244"));

        EXPECT_ANY_THROW(big_int::BigInt num("12341244aa"));

        EXPECT_ANY_THROW(big_int::BigInt num("1235**&213)))aa"));
    }

    TEST(ArithmeticOperator, CommonAssignment) {
        big_int::BigInt num1 ("-1234123412341232135");
        big_int::BigInt num2 (1234123);
        big_int::BigInt num3 ("523512");

        big_int::BigInt copied = num1;
        EXPECT_EQ(copied.GetRealNumber(), num1.GetRealNumber());

        copied = num2;
        EXPECT_EQ(copied.GetRealNumber(), num2.GetRealNumber());

        copied = num3;
        EXPECT_EQ(copied.GetRealNumber(), num3.GetRealNumber());
    }

    TEST(ArithmeticOperator, SemanticAssignment) {
        big_int::BigInt num ("-22222456");
        big_int::BigInt moved;

        moved = std::move(num);
        EXPECT_EQ("-22222456", moved.GetRealNumber());
    }

    TEST(ArithmeticOperator, Inversion) {
        big_int::BigInt pos_num (123451325);
        EXPECT_EQ("-123451326", (~pos_num).GetRealNumber());

        big_int::BigInt neg_num (-923452);
        EXPECT_EQ("923451", (~neg_num).GetRealNumber());

        big_int::BigInt big_num1 ("-590295810358705651710");
        EXPECT_EQ("590295810358705651709", (~big_num1).GetRealNumber());

        big_int::BigInt big_num2 ("590295810358705651710");
        EXPECT_EQ("-590295810358705651711", (~big_num2).GetRealNumber());
    }

    TEST(ArithmeticOperator, PrefixIncrement) {
        big_int::BigInt num1 ("99123512135");
        EXPECT_EQ("99123512136", (++num1).GetRealNumber());
        EXPECT_NE("99123512135", num1.GetRealNumber());

        big_int::BigInt num2 ("-1529239999");
        EXPECT_EQ("-1529239998", (++num2).GetRealNumber());
        EXPECT_NE("-1529239999", num2.GetRealNumber());
    }

    TEST(ArithmeticOperator, PostfixIncrement) {
        big_int::BigInt num1 ("99123512135");
        EXPECT_EQ("99123512135", (num1++).GetRealNumber());
        EXPECT_EQ("99123512136", num1.GetRealNumber());

        big_int::BigInt num2 ("-1529239999");
        EXPECT_EQ("-1529239999", (num2++).GetRealNumber());
        EXPECT_EQ("-1529239998", num2.GetRealNumber());
    }

    TEST(ArithmeticOperator, PrefixDecrement) {
        big_int::BigInt num1 ("123455");
        EXPECT_EQ("123454", (--num1).GetRealNumber());
        EXPECT_NE("123455", num1.GetRealNumber());

        big_int::BigInt num2 ("-9991111");
        EXPECT_EQ("-9991112", (--num2).GetRealNumber());
        EXPECT_NE("-9991111", num2.GetRealNumber());
    }

    TEST(ArithmeticOperator, PostfixDecrement) {
        big_int::BigInt num1 ("123455");
        EXPECT_EQ("123455", (num1--).GetRealNumber());
        EXPECT_EQ("123454", num1.GetRealNumber());

        big_int::BigInt num2 ("-9991111");
        EXPECT_EQ("-9991111", (num2--).GetRealNumber());
        EXPECT_EQ("-9991112", num2.GetRealNumber());
    }

    TEST(ArithmeticOperator, GetNumWithSignPlus) {
        big_int::BigInt num1 ("-123512351235");
        num1 = +num1;
        EXPECT_EQ("123512351235", num1.GetRealNumber());

        big_int::BigInt num2 ("34634634636");
        num2 = +num2;
        EXPECT_NE("-34634634636", num2.GetRealNumber());
    }

    TEST(ArithmeticOperator, GetNumWithSignMinus) {
        big_int::BigInt num1 ("-4457358");
        num1 = -num1;
        EXPECT_EQ("4457358", num1.GetRealNumber());

        big_int::BigInt num2 ("923462346");
        num2 = -num2;
        EXPECT_EQ("-923462346", num2.GetRealNumber());
    }
    
    TEST(ArithmeticOperator, Equality) {
        big_int::BigInt num1 ("3647234623423462");
        big_int::BigInt num2 ("129391235992135");
        EXPECT_EQ(0 , (num1 == num2));

        big_int::BigInt num3 ("999999999999343");
        big_int::BigInt num4 ("999999999999343");
        EXPECT_EQ(1 , (num3 == num4));

        big_int::BigInt num5 ("-435666666666666666");
        big_int::BigInt num6 ("-999999999999343");
        EXPECT_EQ(0 , (num5 == num6));

        big_int::BigInt num7 ("-345345345");
        big_int::BigInt num8 ("-345345345");
        EXPECT_EQ(1, (num7 == num8));
    }

    TEST(ArithmeticOperator, NotEquality) {
        big_int::BigInt num1 ("9647234623423462");
        big_int::BigInt num2 ("1235992135");
        EXPECT_EQ(1 , (num1 != num2));

        big_int::BigInt num3 ("999999999999");
        big_int::BigInt num4 ("999999999999");
        EXPECT_EQ(0 , (num3 != num4));

        big_int::BigInt num5 ("-435666666666666666");
        big_int::BigInt num6 ("-999999999999343");
        EXPECT_EQ(1 , (num5 != num6));

        big_int::BigInt num7 ("-5345345");
        big_int::BigInt num8 ("-5345345");
        EXPECT_EQ(0, (num7 != num8));
    }

    TEST(ArithmeticOperator, LessThan) {
        big_int::BigInt num1 ("9647234623423462");
        big_int::BigInt num2 ("1235992135");
        EXPECT_EQ(0 , (num1 < num2));

        big_int::BigInt num3 ("99999999999911");
        big_int::BigInt num4 ("999999999999");
        EXPECT_EQ(0 , (num3 < num4));

        big_int::BigInt num5 ("12342135213512352135");
        big_int::BigInt num6 ("-999999999999343");
        EXPECT_EQ(0 , (num5 < num6));

        big_int::BigInt num7 ("-534534534573457");
        big_int::BigInt num8 ("-5345345");
        EXPECT_EQ(1, (num7 < num8));
    }

    TEST(ArithmeticOperator, GreaterThan) {
        big_int::BigInt num1 ("90000000000");
        big_int::BigInt num2 ("89999999999");
        EXPECT_EQ(1 , (num1 > num2));

        big_int::BigInt num3 ("100000000000");
        big_int::BigInt num4 ("100000000001");
        EXPECT_EQ(0 , (num3 > num4));

        big_int::BigInt num5 ("5555555555");
        big_int::BigInt num6 ("-5555555555");
        EXPECT_EQ(1 , (num5 > num6));

        big_int::BigInt num7 ("-1000000000000000");
        big_int::BigInt num8 ("-999999999999999");
        EXPECT_EQ(0, (num7 > num8));
    }

    TEST(ArithmeticOperator, LessThanOrEqual) {
        big_int::BigInt num1 ("324693924939349494393949");
        big_int::BigInt num2 ("2346234623727342347");
        EXPECT_EQ(0 , (num1 <= num2));

        big_int::BigInt num3 ("235239529359235");
        big_int::BigInt num4 ("235239529359235");
        EXPECT_EQ(1 , (num3 <= num4));

        big_int::BigInt num5 ("-12342135213512352135");
        big_int::BigInt num6 ("-999999999999343");
        EXPECT_EQ(1 , (num5 <= num6));

        big_int::BigInt num7 ("-34634699999996663463");
        big_int::BigInt num8 ("-34634699999996663463");
        EXPECT_EQ(1, (num7 <= num8));
    }

    TEST(ArithmeticOperator, GreaterThanOrEqual) {
        big_int::BigInt num1 ("99999999999999912414124");
        big_int::BigInt num2 ("1235992135");
        EXPECT_EQ(1 , (num1 >= num2));

        big_int::BigInt num3 ("5685685683423526");
        big_int::BigInt num4 ("5685685683423526");
        EXPECT_EQ(1 , (num3 >= num4));

        big_int::BigInt num5 ("-457457457");
        big_int::BigInt num6 ("-999999999999343");
        EXPECT_EQ(1 , (num5 >= num6));

        big_int::BigInt num7 ("-534534534573457");
        big_int::BigInt num8 ("-5345345");
        EXPECT_EQ(0, (num7 >= num8));
    }

    TEST(Cast, ToInt) {
        big_int::BigInt num1 ("34534");
        EXPECT_EQ(34534, (int)num1);

        big_int::BigInt num2 ("-1111111");
        EXPECT_EQ(-1111111, (int)num2);

        big_int::BigInt num3 ("235222222234522");
        EXPECT_EQ(-251665510, (int)num3);

        big_int::BigInt num4 ("-93452345234623423");
        EXPECT_EQ(1323103297, (int)num4);
    }

    TEST(Cast, ToString) {
        big_int::BigInt num1 ("99999999");
        EXPECT_EQ("99999999", (std::string)num1);

        big_int::BigInt num2 ("-345345345");
        EXPECT_EQ("-345345345", (std::string)num2);
    }

    TEST(GetObjectSize, SizeInBytes) {
        big_int::BigInt num1 ("345234534635472547345734");
        EXPECT_EQ(sizeof(num1), num1.size());

        big_int::BigInt num2 ("-9000000000000000000000000000042222");
        EXPECT_EQ(sizeof(num2), num2.size());
    }

    TEST(ArithmeticOperator, Summation) {
        big_int::BigInt num1 ("122135135123521512");
        big_int::BigInt num2 ("3463432495252135");
        EXPECT_EQ("125598567618773647", (num1+num2).GetRealNumber());

        big_int::BigInt num3 ("9991119911");
        big_int::BigInt num4 ("-123500000000");
        EXPECT_EQ("-113508880089", (num3+num4).GetRealNumber());

    }

    TEST(ArithmeticOperator, Difference) {
        big_int::BigInt num1 ("122343246123521512");
        big_int::BigInt num2 ("9999222575473");
        EXPECT_EQ("122333246900946039", (num1-num2).GetRealNumber());

        big_int::BigInt num3 ("-123521512351235");
        big_int::BigInt num4 ("9234000000");
        EXPECT_EQ("-123530746351235", (num3-num4).GetRealNumber());

        big_int::BigInt num5 ("-567823521512351235");
        big_int::BigInt num6 ("-444234000000");
        EXPECT_EQ("-567823077278351235", (num5-num6).GetRealNumber());
    }

    TEST(ArithmeticOperator, Multiplication) {
        big_int::BigInt num1 ("3225235253");
        big_int::BigInt num2 ("1111111111");
        EXPECT_EQ("3583594725197196083", (num1*num2).GetRealNumber());

        big_int::BigInt num3 ("-12523333333");
        big_int::BigInt num4 ("3352221");
        EXPECT_EQ("-41980980988882593", (num3*num4).GetRealNumber());

        big_int::BigInt num5 ("-566555521100");
        big_int::BigInt num6 ("-1222222233344");
        EXPECT_EQ("692456754312215715558400", (num5*num6).GetRealNumber());

        big_int::BigInt num ("34523462361");
        big_int::BigInt zero ("0");
        EXPECT_EQ("0", (num*zero).GetRealNumber());
    }

    TEST(ArithmeticOperator, Division) {
        big_int::BigInt num1 ("435345345342");
        big_int::BigInt num2 ("1233333");
        EXPECT_EQ("352982", (num1/num2).GetRealNumber());

        big_int::BigInt num3 ("-92222200000");
        big_int::BigInt num4 ("2335");
        EXPECT_EQ("-39495588", (num3/num4).GetRealNumber());

        big_int::BigInt num5 ("-523462346234623232346234");
        big_int::BigInt num6 ("-2346136232342346234634");
        EXPECT_EQ("223", (num5/num6).GetRealNumber());

        big_int::BigInt num7 ("234534523452345234");
        big_int::BigInt zero ("0");
        EXPECT_ANY_THROW(num7 /= zero);

        big_int::BigInt num8 ("12512351235235");
        EXPECT_EQ("0", (zero/num8).GetRealNumber());
    }

    TEST(ArithmeticOperator, Modulo) {
        big_int::BigInt num1 ("212351882323");
        big_int::BigInt num2 ("1888882");
        EXPECT_EQ("1879001", (num1%num2).GetRealNumber());

        big_int::BigInt num3 ("-46222200000");
        big_int::BigInt num4 ("2335342");
        EXPECT_EQ("-1111136", (num3%num4).GetRealNumber());

        big_int::BigInt num5 ("-923992395923959239592395");
        big_int::BigInt num6 ("-234293949293949239492394");
        EXPECT_EQ("-221110548042111521115213", (num5%num6).GetRealNumber());

        big_int::BigInt num7 ("345346346346");
        big_int::BigInt zero ("0");
        EXPECT_ANY_THROW(num7 %= zero;);


        big_int::BigInt num8 ("12512351235235");
        EXPECT_EQ("0", (zero%num8).GetRealNumber());
    }

    TEST(LogicOperator, XOR) {
        big_int::BigInt num1 ("912934912");
        big_int::BigInt num2 ("3434634634");
        EXPECT_EQ("4208072074", (num1^num2).GetRealNumber());

        big_int::BigInt num3 ("-78713717");
        big_int::BigInt num4 ("7123599000");
        EXPECT_EQ("-7183298029", (num3^num4).GetRealNumber());

        big_int::BigInt num5 ("-555150123322");
        big_int::BigInt num6 ("-6127342664611111");
        EXPECT_EQ("6126789696312351", (num5^num6).GetRealNumber());
    }

    TEST(LogicOperator, AND) {
        big_int::BigInt num1 ("1232134123");
        big_int::BigInt num2 ("9230002211");
        EXPECT_EQ("2132003", (num1&num2).GetRealNumber());

        big_int::BigInt num3 ("-23333");
        big_int::BigInt num4 ("100000000000002");
        EXPECT_EQ("99999999983618", (num3&num4).GetRealNumber());

        big_int::BigInt num5 ("-46454748777");
        big_int::BigInt num6 ("-459000111133");
        EXPECT_EQ("-459006539389", (num5&num6).GetRealNumber());
    }

    TEST(LogicOperator, OR) {
        big_int::BigInt num1 ("1232134123");
        big_int::BigInt num2 ("9230002211");
        EXPECT_EQ("10460004331", (num1|num2).GetRealNumber());

        big_int::BigInt num3 ("-23333");
        big_int::BigInt num4 ("100000000000002");
        EXPECT_EQ("-6949", (num3|num4).GetRealNumber());

        big_int::BigInt num5 ("-46454748777");
        big_int::BigInt num6 ("-459000111133");
        EXPECT_EQ("-46448320521", (num5|num6).GetRealNumber());
    }

    TEST(StreamOperator, ostream) {
        std::ostringstream out;

        big_int::BigInt num1 ("12312352135");
        out << num1;
        EXPECT_EQ("12312352135", out.str());
        out.str("");

        big_int::BigInt num2 ("-9990003245");
        out << num2;
        EXPECT_EQ("-9990003245", out.str());
    }
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
