#pragma once // Advent of Code 2024, day 08

#include <iosfwd>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ResonantCollinearity {

struct Point {
    int x;
    int y;

    friend auto operator==(Point, Point) noexcept -> bool = default;
    friend void PrintTo(Point, std::ostream*);
};

using Antennas = std::unordered_map<char, std::vector<Point>>;

struct Grid {
    std::size_t width;
    std::size_t height;

    friend auto operator==(Grid, Grid) noexcept -> bool = default;
    friend void PrintTo(Grid, std::ostream*);
};

auto parseInput(std::string_view) noexcept -> std::pair<Grid, Antennas>;

auto createAntinodes(Point, Point) noexcept -> std::pair<Point, Point>;

auto isPointInsideGrid(Point, Grid) noexcept -> bool;

} // namespace ResonantCollinearity
