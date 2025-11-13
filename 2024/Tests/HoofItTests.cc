#include "HoofIt.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

auto constexpr exampleInput = "89010123\n"
                              "78121874\n"
                              "87430965\n"
                              "96549874\n"
                              "45678903\n"
                              "32019012\n"
                              "01329801\n"
                              "10456732\n";

using testing::Pair;
using testing::UnorderedElementsAre;

using namespace HoofIt;

TEST(HoofIt, parseMinimalExample)
{
    auto const map = Map("0123\n1234\n8765\n9876\n");
    EXPECT_THAT(map.trailheads(), UnorderedElementsAre(Position { .x = 0, .y = 0 }));
    EXPECT_THAT(map.peaks(), UnorderedElementsAre(Position { .x = 0, .y = 3 }));
    EXPECT_THAT(map.steps(),
        UnorderedElementsAre(
            Pair(Position { .x = 0, .y = 0 }, Positions { { .x = 1, .y = 0 }, { .x = 0, .y = 1 } }),
            Pair(Position { .x = 0, .y = 1 }, Positions { { .x = 1, .y = 1 } }),
            Pair(Position { .x = 0, .y = 2 }, Positions { { .x = 0, .y = 3 } }),
            Pair(Position { .x = 1, .y = 0 }, Positions { { .x = 2, .y = 0 }, { .x = 1, .y = 1 } }),
            Pair(Position { .x = 1, .y = 1 }, Positions { { .x = 2, .y = 1 } }),
            Pair(Position { .x = 1, .y = 2 }, Positions { { .x = 0, .y = 2 }, { .x = 1, .y = 3 } }),
            Pair(Position { .x = 1, .y = 3 }, Positions { { .x = 0, .y = 3 } }),
            Pair(Position { .x = 2, .y = 0 }, Positions { { .x = 3, .y = 0 }, { .x = 2, .y = 1 } }),
            Pair(Position { .x = 2, .y = 1 }, Positions { { .x = 3, .y = 1 } }),
            Pair(Position { .x = 2, .y = 2 }, Positions { { .x = 1, .y = 2 }, { .x = 2, .y = 3 } }),
            Pair(Position { .x = 2, .y = 3 }, Positions { { .x = 1, .y = 3 } }),
            Pair(Position { .x = 3, .y = 0 }, Positions { { .x = 3, .y = 1 } }),
            Pair(Position { .x = 3, .y = 1 }, Positions { { .x = 3, .y = 2 } }),
            Pair(Position { .x = 3, .y = 2 }, Positions { { .x = 2, .y = 2 }, { .x = 3, .y = 3 } }),
            Pair(Position { .x = 3, .y = 3 }, Positions { { .x = 2, .y = 3 } })));
}

TEST(HoofIt, parseExampleInput)
{
    auto const map = Map(exampleInput);
    EXPECT_THAT(map.trailheads(),
        UnorderedElementsAre(Position { .x = 2, .y = 0 }, Position { .x = 4, .y = 0 },
            Position { .x = 4, .y = 2 }, Position { .x = 6, .y = 4 }, Position { .x = 2, .y = 5 },
            Position { .x = 5, .y = 5 }, Position { .x = 0, .y = 6 }, Position { .x = 6, .y = 6 },
            Position { .x = 1, .y = 7 }));
    EXPECT_THAT(map.peaks(),
        UnorderedElementsAre(Position { .x = 1, .y = 0 }, Position { .x = 5, .y = 2 },
            Position { .x = 0, .y = 3 }, Position { .x = 4, .y = 3 }, Position { .x = 5, .y = 4 },
            Position { .x = 4, .y = 5 }, Position { .x = 4, .y = 6 }));
    EXPECT_THAT(map.steps(),
        UnorderedElementsAre(Pair(Position { .x = 0, .y = 0 }, Positions { { .x = 1, .y = 0 } }),
            Pair(Position { .x = 0, .y = 1 },
                Positions { { .x = 0, .y = 0 }, { .x = 0, .y = 2 }, { .x = 1, .y = 1 } }),
            Pair(Position { .x = 0, .y = 2 }, Positions { { .x = 0, .y = 3 } }),
            Pair(Position { .x = 0, .y = 4 }, Positions { { .x = 1, .y = 4 } }),
            Pair(Position { .x = 0, .y = 5 }, Positions { { .x = 0, .y = 4 } }),
            Pair(Position { .x = 0, .y = 6 }, Positions { { .x = 1, .y = 6 }, { .x = 0, .y = 7 } }),
            Pair(Position { .x = 0, .y = 7 }, Positions {}),
            Pair(Position { .x = 1, .y = 1 }, Positions { { .x = 1, .y = 0 } }),
            Pair(Position { .x = 1, .y = 2 }, Positions { { .x = 0, .y = 2 }, { .x = 1, .y = 1 } }),
            Pair(Position { .x = 1, .y = 3 }, Positions { { .x = 1, .y = 2 } }),
            Pair(Position { .x = 1, .y = 4 }, Positions { { .x = 1, .y = 3 }, { .x = 2, .y = 4 } }),
            Pair(Position { .x = 1, .y = 5 }, Positions { { .x = 0, .y = 5 } }),
            Pair(Position { .x = 1, .y = 6 }, Positions { { .x = 1, .y = 5 } }),
            Pair(Position { .x = 1, .y = 7 }, Positions { { .x = 1, .y = 6 }, { .x = 0, .y = 7 } }),
            Pair(Position { .x = 2, .y = 0 }, Positions { { .x = 3, .y = 0 }, { .x = 2, .y = 1 } }),
            Pair(Position { .x = 2, .y = 1 }, Positions { { .x = 3, .y = 1 } }),
            Pair(Position { .x = 2, .y = 2 }, Positions { { .x = 2, .y = 3 } }),
            Pair(Position { .x = 2, .y = 3 }, Positions { { .x = 1, .y = 3 }, { .x = 2, .y = 4 } }),
            Pair(Position { .x = 2, .y = 4 }, Positions { { .x = 3, .y = 4 } }),
            Pair(Position { .x = 2, .y = 5 }, Positions { { .x = 3, .y = 5 } }),
            Pair(Position { .x = 2, .y = 6 }, Positions { { .x = 2, .y = 7 } }),
            Pair(Position { .x = 2, .y = 7 }, Positions { { .x = 3, .y = 7 } }),
            Pair(Position { .x = 3, .y = 0 }, Positions { { .x = 3, .y = 1 } }),
            Pair(Position { .x = 3, .y = 1 }, Positions { { .x = 3, .y = 2 } }),
            Pair(Position { .x = 3, .y = 2 }, Positions { { .x = 2, .y = 2 }, { .x = 3, .y = 3 } }),
            Pair(Position { .x = 3, .y = 3 }, Positions { { .x = 2, .y = 3 } }),
            Pair(Position { .x = 3, .y = 4 }, Positions { { .x = 4, .y = 4 } }),
            Pair(Position { .x = 3, .y = 5 }, Positions { { .x = 3, .y = 6 } }),
            Pair(Position { .x = 3, .y = 6 }, Positions { { .x = 2, .y = 6 } }),
            Pair(Position { .x = 3, .y = 7 }, Positions { { .x = 4, .y = 7 } }),
            Pair(Position { .x = 4, .y = 0 },
                Positions { { .x = 3, .y = 0 }, { .x = 4, .y = 1 }, { .x = 5, .y = 0 } }),
            Pair(Position { .x = 4, .y = 1 }, Positions { { .x = 3, .y = 1 } }),
            Pair(Position { .x = 4, .y = 2 }, Positions { { .x = 4, .y = 1 } }),
            Pair(Position { .x = 4, .y = 4 },
                Positions { { .x = 4, .y = 3 }, { .x = 4, .y = 5 }, { .x = 5, .y = 4 } }),
            Pair(Position { .x = 4, .y = 7 }, Positions { { .x = 5, .y = 7 } }),
            Pair(Position { .x = 5, .y = 0 }, Positions { { .x = 6, .y = 0 } }),
            Pair(Position { .x = 5, .y = 1 }, Positions { { .x = 5, .y = 2 } }),
            Pair(Position { .x = 5, .y = 3 },
                Positions { { .x = 4, .y = 3 }, { .x = 5, .y = 2 }, { .x = 5, .y = 4 } }),
            Pair(Position { .x = 5, .y = 5 }, Positions { { .x = 6, .y = 5 } }),
            Pair(Position { .x = 5, .y = 6 }, Positions { { .x = 4, .y = 6 } }),
            Pair(Position { .x = 5, .y = 7 }, Positions { { .x = 5, .y = 6 } }),
            Pair(Position { .x = 6, .y = 0 }, Positions { { .x = 7, .y = 0 } }),
            Pair(Position { .x = 6, .y = 1 }, Positions { { .x = 5, .y = 1 } }),
            Pair(Position { .x = 6, .y = 2 }, Positions { { .x = 6, .y = 1 }, { .x = 6, .y = 3 } }),
            Pair(Position { .x = 6, .y = 3 }, Positions { { .x = 5, .y = 3 } }),
            Pair(Position { .x = 6, .y = 4 }, Positions { { .x = 6, .y = 5 } }),
            Pair(Position { .x = 6, .y = 5 }, Positions { { .x = 7, .y = 5 } }),
            Pair(Position { .x = 6, .y = 6 }, Positions { { .x = 7, .y = 6 }, { .x = 6, .y = 5 } }),
            Pair(Position { .x = 6, .y = 7 }, Positions {}),
            Pair(Position { .x = 7, .y = 0 }, Positions { { .x = 7, .y = 1 } }),
            Pair(Position { .x = 7, .y = 1 }, Positions { { .x = 7, .y = 2 } }),
            Pair(Position { .x = 7, .y = 2 }, Positions { { .x = 6, .y = 2 } }),
            Pair(Position { .x = 7, .y = 3 }, Positions { { .x = 7, .y = 2 } }),
            Pair(Position { .x = 7, .y = 4 }, Positions { { .x = 7, .y = 3 } }),
            Pair(Position { .x = 7, .y = 5 }, Positions { { .x = 7, .y = 4 } }),
            Pair(Position { .x = 7, .y = 6 }, Positions { { .x = 7, .y = 5 }, { .x = 7, .y = 7 } }),
            Pair(Position { .x = 7, .y = 7 }, Positions { { .x = 6, .y = 7 } })));
}

TEST(HoofIt, findPeaksFromMinimalExample)
{
    auto const map = Map("0123\n1234\n8765\n9876\n");
    EXPECT_THAT(
        map.peaksFrom({ .x = 0, .y = 0 }), UnorderedElementsAre(Position { .x = 0, .y = 3 }));
}

TEST(HoofIt, findPeaksFromExampleInput)
{
    auto const map = Map(exampleInput);

    EXPECT_THAT(map.peaksFrom({ .x = 2, .y = 0 }),
        UnorderedElementsAre(Position { .x = 0, .y = 3 }, Position { .x = 1, .y = 0 },
            Position { .x = 4, .y = 3 }, Position { .x = 4, .y = 5 }, Position { .x = 5, .y = 4 }));
    EXPECT_THAT(map.peaksFrom({ .x = 4, .y = 0 }),
        UnorderedElementsAre(Position { .x = 0, .y = 3 }, Position { .x = 1, .y = 0 },
            Position { .x = 4, .y = 3 }, Position { .x = 4, .y = 5 }, Position { .x = 5, .y = 2 },
            Position { .x = 5, .y = 4 }));
    EXPECT_THAT(map.peaksFrom({ .x = 4, .y = 2 }),
        UnorderedElementsAre(Position { .x = 0, .y = 3 }, Position { .x = 1, .y = 0 },
            Position { .x = 4, .y = 3 }, Position { .x = 4, .y = 5 }, Position { .x = 5, .y = 4 }));
    EXPECT_THAT(map.peaksFrom({ .x = 6, .y = 4 }),
        UnorderedElementsAre(
            Position { .x = 4, .y = 3 }, Position { .x = 5, .y = 2 }, Position { .x = 5, .y = 4 }));
    EXPECT_THAT(
        map.peaksFrom({ .x = 2, .y = 5 }), UnorderedElementsAre(Position { .x = 4, .y = 6 }));
    EXPECT_THAT(map.peaksFrom({ .x = 5, .y = 5 }),
        UnorderedElementsAre(
            Position { .x = 4, .y = 3 }, Position { .x = 5, .y = 2 }, Position { .x = 5, .y = 4 }));
    EXPECT_THAT(map.peaksFrom({ .x = 0, .y = 6 }),
        UnorderedElementsAre(Position { .x = 0, .y = 3 }, Position { .x = 1, .y = 0 },
            Position { .x = 4, .y = 3 }, Position { .x = 4, .y = 5 }, Position { .x = 5, .y = 4 }));
    EXPECT_THAT(map.peaksFrom({ .x = 6, .y = 6 }),
        UnorderedElementsAre(
            Position { .x = 4, .y = 3 }, Position { .x = 5, .y = 2 }, Position { .x = 5, .y = 4 }));
    EXPECT_THAT(map.peaksFrom({ .x = 1, .y = 7 }),
        UnorderedElementsAre(Position { .x = 0, .y = 3 }, Position { .x = 1, .y = 0 },
            Position { .x = 4, .y = 3 }, Position { .x = 4, .y = 5 }, Position { .x = 5, .y = 4 }));
}
