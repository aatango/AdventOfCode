#pragma once // Advent of Code 2024, day 08

#include <cstddef>
#include <iosfwd>
#include <utility>

namespace ResonantCollinearity {

struct Point {
    int x;
    int y;

    friend auto operator==(Point, Point) noexcept -> bool = default;
    friend void PrintTo(Point, std::ostream*);
};

struct Grid {
    std::size_t width;
    std::size_t height;
};

auto createAntinodes(Point, Point) noexcept -> std::pair<Point, Point>;

auto isPointInsideGrid(Point, Grid) noexcept -> bool;

} // namespace ResonantCollinearity
