#include "PrintQueue.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <string_view>

std::string_view constexpr exampleInput = "47|53\n"
                                          "97|13\n"
                                          "97|61\n"
                                          "97|47\n"
                                          "75|29\n"
                                          "61|13\n"
                                          "75|53\n"
                                          "29|13\n"
                                          "97|29\n"
                                          "53|29\n"
                                          "61|53\n"
                                          "97|53\n"
                                          "61|29\n"
                                          "47|13\n"
                                          "75|47\n"
                                          "97|75\n"
                                          "47|61\n"
                                          "75|61\n"
                                          "47|29\n"
                                          "75|13\n"
                                          "53|13\n"
                                          "\n"
                                          "75,47,61,53,29\n"
                                          "97,61,53,29,13\n"
                                          "75,29,13\n"
                                          "75,97,47,61,53\n"
                                          "61,13,29\n"
                                          "97,13,75,29,47\n";

using testing::_;
using testing::Pair;

using namespace PrintQueue;

TEST(PrintQueueTests, ParsePageUpdates)
{
    EXPECT_THAT(parseInput("\n\n"), Pair(_, PageUpdates {}));
    EXPECT_THAT(parseInput("53|13\n\n"), Pair(_, PageUpdates {}));

    EXPECT_THAT(
        parseInput("\n\n75,47,61,53,29\n"), Pair(_, PageUpdates { { 75, 47, 61, 53, 29 } }));
    EXPECT_THAT(
        parseInput("53|13\n\n75,47,61,53,29\n"), Pair(_, PageUpdates { { 75, 47, 61, 53, 29 } }));

    EXPECT_THAT(parseInput("\n\n75,47,61,53,29\n75,29,13\n"),
        Pair(_, PageUpdates { { 75, 47, 61, 53, 29 }, { 75, 29, 13 } }));

    EXPECT_THAT(parseInput(std::string { exampleInput }),
        Pair(_,
            PageUpdates { { 75, 47, 61, 53, 29 }, { 97, 61, 53, 29, 13 }, { 75, 29, 13 },
                { 75, 97, 47, 61, 53 }, { 61, 13, 29 }, { 97, 13, 75, 29, 47 } }));
}

TEST(PrintQueueTests, FindMiddlePageNumber)
{
    EXPECT_EQ(findMiddlePage(std::array<std::size_t, 5> { 75, 47, 61, 53, 29 }), 61);
    EXPECT_EQ(findMiddlePage(std::array<std::size_t, 5> { 97, 61, 53, 29, 13 }), 53);
    EXPECT_EQ(findMiddlePage(std::array<std::size_t, 3> { 75, 29, 13 }), 29);
}
