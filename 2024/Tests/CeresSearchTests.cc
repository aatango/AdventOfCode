#include "CeresSearch.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string_view>
#include <tuple>
#include <utility>

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

using testing::Pair;

namespace CeresSearch {

TEST(CeresSearchTests, SolveFirstPuzzle)
{
    EXPECT_THAT(solve(std::string { exampleInput }), Pair(18, 9));
}

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

class XmasCountingTests : public testing::TestWithParam<std::pair<std::string_view, std::size_t>> {
};

TEST_P(XmasCountingTests, CountXmas)
{
    auto const [content, expectedCount] = GetParam();

    auto const grid = Grid { content };

    EXPECT_EQ(grid.countXmas(), expectedCount);
}

INSTANTIATE_TEST_CASE_P(XmasStrings, XmasCountingTests,
    testing::Values(std::pair { "X\n", 0 }, std::pair { "X.A.\n", 0 }, std::pair { "XMAS\n", 1 },
        std::pair { "X\n.\nA\n.\n", 0 }, std::pair { "X\nM\nA\nS\n", 1 },
        std::pair { "....\n....\n....\n....\n", 0 }, std::pair { "XMAS\n....\n....\n....\n", 1 },
        std::pair { "X...\n.M..\n..A.\n...S\n", 1 }, std::pair { "X...\nM...\nA...\nS...\n", 1 },
        std::pair { "...X\n..M.\n.A..\nS...\n", 1 }, std::pair { "SAMX\n....\n....\n....\n", 1 },
        std::pair { "S...\n.A..\n..M.\n...X\n", 1 }, std::pair { "S...\nA...\nM...\nX...\n", 1 },
        std::pair { "Xmas\nMm..\nA.A.\nS..s\n", 3 }, std::pair { "xmaS\n..aA\n.M.M\nx..X\n", 3 }));

class CrossedMasTests : public testing::TestWithParam<std::pair<std::string_view, std::size_t>> { };

TEST_P(CrossedMasTests, CountCrossedMas)
{
    auto const [content, expectedCount] = GetParam();

    auto const grid = Grid { content };

    EXPECT_EQ(grid.countCrossedMas(), expectedCount);
}

INSTANTIATE_TEST_CASE_P(SingleMas, CrossedMasTests,
    testing::Values(std::pair { "MAS\n", 0 }, std::pair { "M..\nA..\nS..\n", 0 },
        std::pair { "M.M\n.A.\nS.S\n", 1 }, std::pair { "M.S\n.A.\nM.S\n", 1 },
        std::pair { "S.M\n.A.\nS.M\n", 1 }, std::pair { "S.S\n.A.\nM.M\n", 1 }));

} // namespace CeresSearch
