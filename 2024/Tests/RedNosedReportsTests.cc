#include "RedNosedReports.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

std::string_view constexpr exampleInput = { "7 6 4 2 1\n"
                                            "1 2 7 8 9\n"
                                            "9 7 6 2 1\n"
                                            "1 3 2 4 5\n"
                                            "8 6 4 4 1\n"
                                            "1 3 6 7 9\n" };

using ::testing::Pair;

namespace RedNosedReports {

TEST(RedNosedReportsTests, SolveBothPuzzles)
{
    EXPECT_THAT(solve(std::string { exampleInput }), Pair(2, 4));
}

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

class ValidateReportTests : public ::testing::TestWithParam<std::pair<Report, bool>> { };

TEST_P(ValidateReportTests, ValidateReports)
{
    auto const [report, isSafe] = GetParam();

    EXPECT_EQ(validateReport(report), isSafe);
}

INSTANTIATE_TEST_CASE_P(ReportsToValidate, ValidateReportTests,
    ::testing::Values(std::pair { Report { 7, 6, 4, 2, 1 }, true },
        std::pair { Report { 1, 2, 7, 8, 9 }, false },
        std::pair { Report { 9, 7, 6, 2, 1 }, false },
        std::pair { Report { 1, 3, 2, 4, 5 }, false },
        std::pair { Report { 8, 6, 4, 4, 1 }, false },
        std::pair { Report { 1, 3, 6, 7, 9 }, true }));

class ValidateDampenedReportsTests : public ::testing::TestWithParam<std::pair<Report, bool>> { };

TEST_P(ValidateDampenedReportsTests, ValidateReports)
{
    auto const [report, isSafe] = GetParam();

    EXPECT_THAT(validateReport(report, true), isSafe);
}

INSTANTIATE_TEST_CASE_P(ReportsToValidate, ValidateDampenedReportsTests,
    ::testing::Values(std::pair { Report { 7, 6, 4, 2, 1 }, true },
        std::pair { Report { 1, 2, 7, 8, 9 }, false },
        std::pair { Report { 9, 7, 6, 2, 1 }, false }, std::pair { Report { 1, 3, 2, 4, 5 }, true },
        std::pair { Report { 8, 6, 4, 4, 1 }, true },
        std::pair { Report { 1, 3, 6, 7, 9 }, true }));

} // namespace RedNosedReports
