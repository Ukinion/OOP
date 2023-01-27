project(lab1_big_int)

add_library(
        bigInt BigInt.cpp Binary.cpp Summator.cpp Subtractor.cpp
        Divider.cpp Multiplier.cpp LogicalAnalyzer.cpp StringManager.cpp
        big_int.h constants.h math_machine.h
)
