#include "ResonantCollinearity.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Pair;

using namespace ResonantCollinearity;

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
