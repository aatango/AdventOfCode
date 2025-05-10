#pragma once // Advent of Code 2024, day 08

#include <iosfwd>
#include <utility>

namespace ResonantCollinearity {

struct Point {
    int x;
    int y;

    friend auto operator==(Point, Point) noexcept -> bool = default;
    friend void PrintTo(Point, std::ostream*);
};

auto createAntinodes(Point, Point) noexcept -> std::pair<Point, Point>;

} // namespace ResonantCollinearity
