#include "RedNosedReports.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <utility>

std::string_view constexpr exampleInput = { "7 6 4 2 1\n"
                                            "1 2 7 8 9\n"
                                            "9 7 6 2 1\n"
                                            "1 3 2 4 5\n"
                                            "8 6 4 4 1\n"
                                            "1 3 6 7 9\n" };

namespace RedNosedReports {

class RedNosedReportsInputParsingTests
    : public ::testing::TestWithParam<std::pair<std::string, Reports>> { };

TEST_P(RedNosedReportsInputParsingTests, ParseInputIntoReports)
{
    auto const [stringToTest, expectedResult] = GetParam();

    EXPECT_THAT(parseInput(stringToTest), expectedResult);
}

INSTANTIATE_TEST_CASE_P(ParseEmptyInput, RedNosedReportsInputParsingTests,
    ::testing::Values(std::pair { "", Reports {} }));

INSTANTIATE_TEST_CASE_P(ParseSingleInput, RedNosedReportsInputParsingTests,
    ::testing::Values(std::pair { "7 6 4 2 1\n", Reports { { 7, 6, 4, 2, 1 } } }));

INSTANTIATE_TEST_CASE_P(ParseMultipleInputs, RedNosedReportsInputParsingTests,
    ::testing::Values(std::pair { exampleInput,
        Reports { { 7, 6, 4, 2, 1 }, { 1, 2, 7, 8, 9 }, { 9, 7, 6, 2, 1 }, { 1, 3, 2, 4, 5 },
            { 8, 6, 4, 4, 1 }, { 1, 3, 6, 7, 9 } } }));

} // namespace RedNosedReports
