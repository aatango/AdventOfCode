#pragma once // Advent of Code 2024, day 08

#include <iosfwd>
#include <span>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
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

struct PointHash {
    auto operator()(Point) const noexcept -> std::size_t;
};

using PointSet = std::unordered_set<Point, PointHash>;

struct Grid {
    std::size_t width;
    std::size_t height;

    friend auto operator==(Grid, Grid) noexcept -> bool = default;
    friend void PrintTo(Grid, std::ostream*);
};

auto parseInput(std::string_view) noexcept -> std::pair<Grid, Antennas>;

auto createAntinodes(Point, Point) noexcept -> std::pair<Point, Point>;
auto createAntinodes(std::span<Point const>) noexcept -> PointSet;

auto isPointInsideGrid(Point, Grid) noexcept -> bool;

} // namespace ResonantCollinearity
