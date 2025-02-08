#include "HistorianHysteria.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string_view>
#include <utility>

std::string_view constexpr exampleInput = { "3   4\n"
                                            "4   3\n"
                                            "2   5\n"
                                            "1   3\n"
                                            "3   9\n"
                                            "3   3\n" };

namespace HistorianHysteria {

TEST(Day01Tests, CalculateTotalDistanceBetweenLists)
{
    EXPECT_EQ(solve(std::string { exampleInput }), 11);
}

class InputParsingTests : public ::testing::TestWithParam<std::pair<std::string, PairedLists>> { };

TEST_P(InputParsingTests, ParseInputIntoPairsOfLists)
{
    auto const [stringToTest, expectedResult] = GetParam();

    EXPECT_THAT(parseInput(stringToTest), expectedResult);
}

INSTANTIATE_TEST_CASE_P(ParseEmptyInput, InputParsingTests,
    ::testing::Values(std::pair { "", PairedLists { {}, {} } }));

INSTANTIATE_TEST_CASE_P(ParseSingleInput, InputParsingTests,
    ::testing::Values(std::pair { "3 4\n", PairedLists { { 3 }, { 4 } } },
        std::pair { "4   3\n", PairedLists { { 4 }, { 3 } } },
        std::pair { "2\t5\n", PairedLists { { 2 }, { 5 } } }));

INSTANTIATE_TEST_CASE_P(ParseMultipleInputs, InputParsingTests,
    ::testing::Values(std::pair { std::string { exampleInput },
        PairedLists { { 3, 4, 2, 1, 3, 3 }, { 4, 3, 5, 3, 9, 3 } } }));

class ListComparisonTests : public ::testing::TestWithParam<std::pair<PairedLists, List>> { };

TEST_P(ListComparisonTests, ReturnElementwiseDifferencesOfSortedLists)
{
    auto const [pairedLists, expectedResult] = GetParam();

    EXPECT_THAT(calculateDistances(pairedLists.first, pairedLists.second), expectedResult);
}

INSTANTIATE_TEST_CASE_P(CompareEmptyLists, ListComparisonTests,
    ::testing::Values(std::pair { PairedLists { {}, {} }, List {} }));

INSTANTIATE_TEST_CASE_P(CompareListsWithOneLocationEach, ListComparisonTests,
    ::testing::Values(std::pair { PairedLists { { 2 }, { 5 } }, List { 3 } },
        std::pair { PairedLists { { 4 }, { 3 } }, List { 1 } },
        std::pair { PairedLists { { 3 }, { 3 } }, List { 0 } }));

INSTANTIATE_TEST_CASE_P(CompareListsWitMultipleListsEach, ListComparisonTests,
    ::testing::Values(std::pair {
        PairedLists { { 3, 4, 2, 1, 3, 3 }, { 4, 3, 5, 3, 9, 3 } }, List { 2, 1, 0, 1, 2, 5 } }));

} // namespace HistorianHysteria
