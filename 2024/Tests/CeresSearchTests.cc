#include "CeresSearch.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string_view>
#include <tuple>

std::string_view constexpr exampleInput = "MMMSXXMASM\n"
                                          "MSAMXMSMSA\n"
                                          "AMXSXMAAMM\n"
                                          "MSAMASMSMX\n"
                                          "XMASAMXAMM\n"
                                          "XXAMMXXAMA\n"
                                          "SMSMSASXSS\n"
                                          "SAXAMASAAA\n"
                                          "MAMMMXMMMM\n"
                                          "MXMXAXMASX\n";

namespace CeresSearch {

class GridDimensionTests
    : public testing::TestWithParam<std::tuple<std::string_view, std::size_t, std::size_t>> { };

TEST_P(GridDimensionTests, GridIsProperlySizedBasedOnNewLineCharacters)
{
    auto [characters, width, height] = GetParam();

    auto const grid = Grid { characters };

    EXPECT_EQ(grid.height(), height);
    EXPECT_EQ(grid.width(), width);
}

INSTANTIATE_TEST_CASE_P(SingleColumnGrid, GridDimensionTests,
    testing::Values(std::tuple { "X\n", 1, 1 }, std::tuple { "XMAS\n", 4, 1 }));

INSTANTIATE_TEST_CASE_P(
    SingleRowGrid, GridDimensionTests, testing::Values(std::tuple { "X\nM\nA\nS\n", 1, 4 }));

INSTANTIATE_TEST_CASE_P(SquareGrid, GridDimensionTests,
    testing::Values(std::tuple { "MMMM\nMMMM\nMMMM\nMMMM\n", 4, 4 }));

} // namespace CeresSearch
