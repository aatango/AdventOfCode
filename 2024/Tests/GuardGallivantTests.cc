#include "GuardGallivant.hh"

#include <gtest/gtest.h>

std::string_view constexpr exampleInput = "....#.....\n"
                                          ".........#\n"
                                          "..........\n"
                                          "..#.......\n"
                                          ".......#..\n"
                                          "..........\n"
                                          ".#..^.....\n"
                                          "........#.\n"
                                          "#.........\n"
                                          "......#...\n";

using namespace GuardGallivant;

TEST(GuardGallivantTests, GuardInitialOrientation)
{
    EXPECT_EQ(Map("^\n").guard().orientation, Orientation::Up);
    EXPECT_EQ(Map(">\n").guard().orientation, Orientation::Right);
    EXPECT_EQ(Map("v\n").guard().orientation, Orientation::Down);
    EXPECT_EQ(Map("<\n").guard().orientation, Orientation::Left);

    EXPECT_EQ(Map(exampleInput).guard().orientation, Orientation::Up);
}

TEST(GuardGallivantTests, GuardInitialPosition)
{
    EXPECT_EQ(Map("^\n").guard().position, (Position { .x = 0, .y = 0 }));
    EXPECT_EQ(Map("^.\n..\n").guard().position, (Position { .x = 0, .y = 0 }));

    EXPECT_EQ(Map(".>\n").guard().position, (Position { .x = 1, .y = 0 }));
    EXPECT_EQ(Map("..>.\n....\n").guard().position, (Position { .x = 2, .y = 0 }));

    EXPECT_EQ(Map(".\nv\n").guard().position, (Position { .x = 0, .y = 1 }));
    EXPECT_EQ(Map("...\n...\n...\nv..\n").guard().position, (Position { .x = 0, .y = 3 }));

    EXPECT_EQ(Map("....\n..<.\n....\n....\n").guard().position, (Position { .x = 2, .y = 1 }));
    EXPECT_EQ(Map("....\n....\n..<.\n....\n").guard().position, (Position { .x = 2, .y = 2 }));
    EXPECT_EQ(Map("....\n....\n....\n.<..\n").guard().position, (Position { .x = 1, .y = 3 }));

    EXPECT_EQ(Map(exampleInput).guard().position, (Position { .x = 4, .y = 6 }));
}
