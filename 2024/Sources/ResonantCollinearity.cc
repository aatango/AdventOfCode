#include "ResonantCollinearity.hh"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ostream>
#include <ranges>

namespace ResonantCollinearity {

void PrintTo(Point const pt, std::ostream* os)
{
    *os << "{.x= " << pt.x << ", .y= " << pt.y << "}";
}

void PrintTo(Grid const grid, std::ostream* os)
{
    *os << "{.width = " << grid.width << ", .height = " << grid.height << "}";
}

auto createAntinodes(Point const lhs, Point const rhs) noexcept -> std::pair<Point, Point>
{
    auto const magnitudeX = rhs.x - lhs.x;
    auto const magnitudeY = rhs.y - lhs.y;

    return { Point { .x = lhs.x - magnitudeX, .y = lhs.y - magnitudeY },
        Point { .x = rhs.x + magnitudeX, .y = rhs.y + magnitudeY } };
}

auto isPointInsideGrid(Point const point, Grid const grid) noexcept -> bool
{
    if (point.x < 0 || point.y < 0)
        return false;

    return static_cast<std::size_t>(point.x) < grid.width
        && static_cast<std::size_t>(point.y) < grid.height;
}

auto parseInput(std::string_view const input) noexcept -> std::pair<Grid, Antennas>
{
    auto const width = static_cast<std::size_t>(std::ranges::count(input, '\n'));
    auto const height = static_cast<std::size_t>(std::ranges::find(input, '\n') - input.cbegin());

    auto antennas = input | std::views::filter([](char c) { return c != '\n'; })
        | std::views::enumerate
        | std::views::filter([](std::pair<int, char> const& c) { return std::isalnum(c.second); })
        | std::views::transform([&width](std::pair<int, char> const& a) {
              return std::pair { Point { .x = static_cast<int>(a.first % width),
                                     .y = static_cast<int>(a.first / width) },
                  a.second };
          });

    std::unordered_map<char, std::vector<ResonantCollinearity::Point>> mappedAntennas;

    for (auto const& [position, id] : antennas) {
        mappedAntennas[id].push_back(position);
    }

    return { Grid { .width = width, .height = height }, mappedAntennas };
}

} // namespace ResonantCollinearity
