#include "MullItOver.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

std::string_view constexpr exampleInput
    = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

namespace MullItOver {

class MullItOverInputParsingTests
    : public ::testing::TestWithParam<std::pair<std::string, Multiplications>> { };

TEST_P(MullItOverInputParsingTests, ParseInputIntoReports)
{
    auto const [stringToTest, expectedResult] = GetParam();

    EXPECT_THAT(parseInput(stringToTest), expectedResult);
}

INSTANTIATE_TEST_CASE_P(ParseEmptyInput, MullItOverInputParsingTests,
    ::testing::Values(std::pair { "", Multiplications {} }));

INSTANTIATE_TEST_CASE_P(ParseSingleInput, MullItOverInputParsingTests,
    ::testing::Values(std::pair { "mul(44,46)", Multiplications { { 44, 46 } } },
        std::pair { "mul(4*", Multiplications {} }, std::pair { "mul(6,9!", Multiplications {} },
        std::pair { "?(12,34)", Multiplications {} },
        std::pair { "mul ( 2 , 4 )", Multiplications {} },
        std::pair { "mul(123,4)", Multiplications { { 123, 4 } } }));

INSTANTIATE_TEST_CASE_P(ParseMultipleInputs, MullItOverInputParsingTests,
    ::testing::Values(
        std::pair { exampleInput, Multiplications { { 2, 4 }, { 5, 5 }, { 11, 8 }, { 8, 5 } } }));

} // namespace MullItOver
