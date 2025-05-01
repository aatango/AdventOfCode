#include "BridgeRepair.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string_view>

std::string_view constexpr exampleInput = "190: 10 19\n"
                                          "3267: 81 40 27\n"
                                          "83: 17 5\n"
                                          "156: 15 6\n"
                                          "7290: 6 8 6 15\n"
                                          "161011: 16 10 13\n"
                                          "192: 17 8 14\n"
                                          "21037: 9 7 18 13\n"
                                          "292: 11 6 16 20\n";

using testing::Pair;

using namespace BridgeRepair;

TEST(BridgeRepairTests, solveFirstPuzzle)
{
    EXPECT_THAT(solve(std::string { exampleInput }), Pair(3749, 11387));
}

TEST(BridgeRepairTests, ParseInput)
{
    Equations const exampleEquations
        = { { 190, { 10, 19 } }, { 3267, { 81, 40, 27 } }, { 83, { 17, 5 } }, { 156, { 15, 6 } },
              { 7290, { 6, 8, 6, 15 } }, { 161011, { 16, 10, 13 } }, { 192, { 17, 8, 14 } },
              { 21037, { 9, 7, 18, 13 } }, { 292, { 11, 6, 16, 20 } } };

    EXPECT_EQ(parseInput(exampleInput), exampleEquations);
}

TEST(BridgeRepairTests, ValidateEquations)
{
    EXPECT_TRUE(isValidEquation(Equation { 190, { 10, 19 } }));
    EXPECT_TRUE(isValidEquation(Equation { 3267, { 81, 40, 27 } }));
    EXPECT_TRUE(isValidEquation(Equation { 292, { 11, 6, 16, 20 } }));

    EXPECT_FALSE(isValidEquation(Equation { 83, { 17, 5 } }));
    EXPECT_FALSE(isValidEquation(Equation { 156, { 15, 6 } }));
    EXPECT_FALSE(isValidEquation(Equation { 7290, { 6, 8, 6, 15 } }));
    EXPECT_FALSE(isValidEquation(Equation { 161011, { 16, 10, 13 } }));
    EXPECT_FALSE(isValidEquation(Equation { 192, { 17, 8, 14 } }));
    EXPECT_FALSE(isValidEquation(Equation { 21037, { 9, 7, 18, 13 } }));
}

TEST(BridgeRepairTests, ValidateEquationsWithConcatenation)
{
    EXPECT_TRUE(isValidEquation(Equation { 156, { 15, 6 } }, true));
    EXPECT_TRUE(isValidEquation(Equation { 7290, { 6, 8, 6, 15 } }, true));
    EXPECT_TRUE(isValidEquation(Equation { 192, { 17, 8, 14 } }, true));
}
