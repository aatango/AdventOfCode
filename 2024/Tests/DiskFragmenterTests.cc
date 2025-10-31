#include "DiskFragmenter.hh"

#include <string_view>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

std::string_view constexpr exampleInput = "2333133121414131402\n";

using testing::_;
using testing::ElementsAre;
using testing::Pair;

using namespace DiskFragmenter;

TEST(DiskFragmenterTests, solveFirstPuzzle)
{
    EXPECT_THAT(solve(std::string { exampleInput }), Pair(1928, _));
}

TEST(DiskFragmenterTests, parseInput)
{
    EXPECT_THAT(parseInput("12345\n"), ElementsAre(1, 2, 3, 4, 5));
    EXPECT_THAT(parseInput(exampleInput),
        ElementsAre(2, 3, 3, 3, 1, 3, 3, 1, 2, 1, 4, 1, 4, 1, 3, 1, 4, 0, 2));
}

TEST(DiskFragmenterTests, defragmentByBlock)
{
    EXPECT_THAT(defragmentByBlock({ 1, 2, 3, 4, 5 }), ElementsAre(0, 2, 2, 1, 1, 1, 2, 2, 2));
    EXPECT_THAT(defragmentByBlock(parseInput(exampleInput)),
        ElementsAre(
            0, 0, 9, 9, 8, 1, 1, 1, 8, 8, 8, 2, 7, 7, 7, 3, 3, 3, 6, 4, 4, 6, 5, 5, 5, 5, 6, 6));
}
