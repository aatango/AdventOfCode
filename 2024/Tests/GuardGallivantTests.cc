#include "GuardGallivant.hh"

#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>

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

TEST(GuardGallivantTests, TaxicabDistanceBetweenTwoPositions)
{
    // Same position
    EXPECT_EQ(taxicabDistance({ .x = 0, .y = 0 }, { .x = 0, .y = 0 }), 0);
    EXPECT_EQ(taxicabDistance({ .x = 1, .y = 2 }, { .x = 1, .y = 2 }), 0);

    // Horizontal distance
    EXPECT_EQ(taxicabDistance({ .x = 1, .y = 2 }, { .x = 4, .y = 2 }), 3);
    EXPECT_EQ(taxicabDistance({ .x = 6, .y = 2 }, { .x = 1, .y = 2 }), 5);

    // Vertical distance
    EXPECT_EQ(taxicabDistance({ .x = 1, .y = 2 }, { .x = 1, .y = 6 }), 4);
    EXPECT_EQ(taxicabDistance({ .x = 1, .y = 4 }, { .x = 1, .y = 2 }), 2);

    // Diagonal distance
    EXPECT_EQ(taxicabDistance({ .x = 1, .y = 2 }, { .x = 4, .y = 5 }), 6);
    EXPECT_EQ(taxicabDistance({ .x = 1, .y = 6 }, { .x = 4, .y = 2 }), 7);
    EXPECT_EQ(taxicabDistance({ .x = 4, .y = 2 }, { .x = 1, .y = 7 }), 8);
    EXPECT_EQ(taxicabDistance({ .x = 4, .y = 6 }, { .x = 1, .y = 0 }), 9);
}

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

TEST(GuardGallivantTests, PositionsOfObstructions)
{
    EXPECT_EQ(Map("^.\n").obstructions(), Positions {});

    EXPECT_EQ(Map(".#^\n").obstructions(), (Positions { { .x = 1, .y = 0 } }));

    EXPECT_EQ(Map(".#\n^.\n").obstructions(), (Positions { { .x = 1, .y = 0 } }));
    EXPECT_EQ(Map("..\n#^\n").obstructions(), (Positions { { .x = 0, .y = 1 } }));

    EXPECT_EQ(Map(".^.\n.#.\n##.\n").obstructions(),
        (Positions { { .x = 1, .y = 1 }, { .x = 0, .y = 2 }, { .x = 1, .y = 2 } }));

    EXPECT_EQ(Map(exampleInput).obstructions(),
        (Positions { { .x = 4, .y = 0 }, { .x = 9, .y = 1 }, { .x = 2, .y = 3 }, { .x = 7, .y = 4 },
            { .x = 1, .y = 6 }, { .x = 8, .y = 7 }, { .x = 0, .y = 8 }, { .x = 6, .y = 9 } }));
}

TEST(GuardGallivantTests, IsPositionAheadOfGuard)
{
    EXPECT_TRUE(Map(".\n^\n").isPositionAheadOfGuard({ .x = 0, .y = 0 }));

    EXPECT_FALSE(Map(".\nv\n").isPositionAheadOfGuard({ .x = 0, .y = 0 }));

    EXPECT_FALSE(Map("#.\n.^\n").isPositionAheadOfGuard({ .x = 0, .y = 0 }));
    EXPECT_FALSE(Map(">.\n.#\n").isPositionAheadOfGuard({ .x = 1, .y = 1 }));
    EXPECT_FALSE(Map(".v...\n...#.\n").isPositionAheadOfGuard({ .x = 3, .y = 1 }));
    EXPECT_FALSE(Map("...\n.#.\n..<\n...\n").isPositionAheadOfGuard({ .x = 1, .y = 1 }));

    EXPECT_TRUE(Map("#\n^\n").isPositionAheadOfGuard({ .x = 0, .y = 0 }));
    EXPECT_TRUE(Map(">.#\n").isPositionAheadOfGuard({ .x = 2, .y = 0 }));
    EXPECT_TRUE(Map("v\n.\n#\n.\n").isPositionAheadOfGuard({ .x = 0, .y = 2 }));
    EXPECT_TRUE(Map(".#..<\n").isPositionAheadOfGuard({ .x = 1, .y = 0 }));

    EXPECT_TRUE(Map(exampleInput).isPositionAheadOfGuard({ .x = 4, .y = 0 }));
}

class GuardGallivantPatrollingTests
    : public testing::TestWithParam<std::pair<std::string, std::size_t>> { };

TEST_P(GuardGallivantPatrollingTests, PatrolledDistanceOnceGuardHasLeftTheMap)
{
    auto const [inputMap, expectedWalkedDistance] = GetParam();

    auto map = Map(inputMap);

    map.patrol();

    EXPECT_EQ(map.guard().visitedPositions.size(), expectedWalkedDistance);
}

INSTANTIATE_TEST_CASE_P(TestMaps, GuardGallivantPatrollingTests,
    testing::Values(std::pair { "^\n", 1 }, std::pair { ">.\n", 2 },
        std::pair { ".v\n..\n.#\n..\n", 3 }, std::pair { "...\n.#.\n...\n#.<\n", 4 },
        std::pair { ".#..\n...#\n....\n.^#.\n", 6 }));

INSTANTIATE_TEST_CASE_P(
    ExampleMap, GuardGallivantPatrollingTests, testing::Values(std::pair { exampleInput, 41 }));
