#include "DiskFragmenter.hh"

#include <string_view>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

std::string_view constexpr exampleInput = "2333133121414131402\n";

using testing::ElementsAre;

using namespace DiskFragmenter;

TEST(DiskFragmenterTests, parseInput)
{
    EXPECT_THAT(parseInput("12345\n"), ElementsAre(1, 2, 3, 4, 5));
    EXPECT_THAT(parseInput(exampleInput),
        ElementsAre(2, 3, 3, 3, 1, 3, 3, 1, 2, 1, 4, 1, 4, 1, 3, 1, 4, 0, 2));
}
