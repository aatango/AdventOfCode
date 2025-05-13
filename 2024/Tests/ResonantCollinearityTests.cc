#include "ResonantCollinearity.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string_view>

std::string_view constexpr exampleInput = "............\n"
                                          "........0...\n"
                                          ".....0......\n"
                                          ".......0....\n"
                                          "....0.......\n"
                                          "......A.....\n"
                                          "............\n"
                                          "............\n"
                                          "........A...\n"
                                          ".........A..\n"
                                          "............\n"
                                          "............\n";

using testing::_;
using testing::Pair;
using testing::UnorderedElementsAre;

using namespace ResonantCollinearity;

TEST(ResonantCollinearlityTests, solvePuzzle)
{
    EXPECT_THAT(solve(std::string { exampleInput }), Pair(14, _));
}

TEST(ResonantCollinearityTests, parseInput)
{
    auto constexpr expectedGrid = Grid { .width = 12, .height = 12 };
    auto const expectedAntennas = Antennas {
        { '0', { { .x = 8, .y = 1 }, { .x = 5, .y = 2 }, { .x = 7, .y = 3 }, { .x = 4, .y = 4 } } },
        { 'A', { { .x = 6, .y = 5 }, { .x = 8, .y = 8 }, { .x = 9, .y = 9 } } }
    };

    EXPECT_THAT(parseInput(exampleInput), Pair(expectedGrid, expectedAntennas));
}

TEST(ResonantCollinearityTests, createAntinodesGivenTwoPoints)
{
    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 0, .y = 0 }),
        Pair(Point { .x = 0, .y = 0 }, Point { .x = 0, .y = 0 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 1, .y = 0 }),
        Pair(Point { .x = -1, .y = 0 }, Point { .x = 2, .y = 0 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 1, .y = 1 }),
        Pair(Point { .x = -1, .y = -1 }, Point { .x = 2, .y = 2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 2, .y = 1 }),
        Pair(Point { .x = -2, .y = -1 }, Point { .x = 4, .y = 2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 0, .y = 1 }),
        Pair(Point { .x = 0, .y = -1 }, Point { .x = 0, .y = 2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = -1, .y = 1 }),
        Pair(Point { .x = 1, .y = -1 }, Point { .x = -2, .y = 2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = -1, .y = 2 }),
        Pair(Point { .x = 1, .y = -2 }, Point { .x = -2, .y = 4 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = -1, .y = 0 }),
        Pair(Point { .x = 1, .y = 0 }, Point { .x = -2, .y = 0 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = -1, .y = -1 }),
        Pair(Point { .x = 1, .y = 1 }, Point { .x = -2, .y = -2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = -2, .y = -1 }),
        Pair(Point { .x = 2, .y = 1 }, Point { .x = -4, .y = -2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 0, .y = -1 }),
        Pair(Point { .x = 0, .y = 1 }, Point { .x = 0, .y = -2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 1, .y = -1 }),
        Pair(Point { .x = -1, .y = 1 }, Point { .x = 2, .y = -2 }));

    EXPECT_THAT(createAntinodes({ .x = 0, .y = 0 }, { .x = 1, .y = -2 }),
        Pair(Point { .x = -1, .y = 2 }, Point { .x = 2, .y = -4 }));

    EXPECT_THAT(createAntinodes({ .x = 1, .y = 3 }, { .x = 4, .y = 7 }),
        Pair(Point { .x = -2, .y = -1 }, Point { .x = 7, .y = 11 }));
}

TEST(ResonantCollinearityTests, createAntinodesGivenMultiplePoints)
{
    auto const points
        = std::vector<Point> { { .x = 4, .y = 3 }, { .x = 8, .y = 4 }, { .x = 5, .y = 5 } };

    EXPECT_THAT(createAntinodes(points),
        UnorderedElementsAre(Point { .x = 3, .y = 1 }, Point { .x = 0, .y = 2 },
            Point { .x = 11, .y = 3 }, Point { .x = 12, .y = 5 }, Point { .x = 2, .y = 6 },
            Point { .x = 6, .y = 7 }));
}

TEST(ResonantCollinearityTests, arePointsInsideGrid)
{

    auto constexpr grid = Grid { .width = 4, .height = 2 };

    EXPECT_TRUE(isPointInsideGrid({ .x = 0, .y = 0 }, grid));
    EXPECT_TRUE(isPointInsideGrid({ .x = 1, .y = 0 }, grid));
    EXPECT_TRUE(isPointInsideGrid({ .x = 0, .y = 1 }, grid));
    EXPECT_TRUE(isPointInsideGrid({ .x = 1, .y = 1 }, grid));
    EXPECT_TRUE(isPointInsideGrid({ .x = 3, .y = 1 }, grid));

    EXPECT_FALSE(isPointInsideGrid({ .x = -1, .y = 0 }, grid));
    EXPECT_FALSE(isPointInsideGrid({ .x = 0, .y = -1 }, grid));
    EXPECT_FALSE(isPointInsideGrid({ .x = -1, .y = -1 }, grid));

    EXPECT_FALSE(isPointInsideGrid({ .x = 4, .y = 0 }, grid));
    EXPECT_FALSE(isPointInsideGrid({ .x = 0, .y = 2 }, grid));
    EXPECT_FALSE(isPointInsideGrid({ .x = 4, .y = 2 }, grid));
}

TEST(ResonantCollinearityTests, findPointsInGridAlongLines)
{
    auto const antennas
        = std::vector<Point> { { .x = 0, .y = 0 }, { .x = 3, .y = 1 }, { .x = 1, .y = 2 } };

    auto const grid = Grid { .width = 10, .height = 10 };

    EXPECT_THAT(findPointsInGridAlongLines(grid, antennas),
        UnorderedElementsAre(Point { .x = 4, .y = 8 }, Point { .x = 2, .y = 4 },
            Point { .x = 5, .y = 0 }, Point { .x = 1, .y = 2 }, Point { .x = 3, .y = 6 },
            Point { .x = 9, .y = 3 }, Point { .x = 6, .y = 2 }, Point { .x = 3, .y = 1 },
            Point { .x = 0, .y = 0 }));
}
