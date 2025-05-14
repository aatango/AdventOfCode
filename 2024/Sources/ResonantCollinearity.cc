#include "ResonantCollinearity.hh"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ostream>
#include <ranges>
#include <utility>

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

auto createAntinodes(std::span<Point const> const points) noexcept -> PointSet
{
    auto pointPairs = std::views::cartesian_product(points, points)
        | std::views::filter(
            [](std::pair<Point, Point> const& points) { return points.first != points.second; });

    PointSet antinodes;

    for (auto const [firstPoint, secondPoint] : pointPairs) {
        auto const [firstNode, secondNode] = createAntinodes(firstPoint, secondPoint);
        antinodes.insert(firstNode);
        antinodes.insert(secondNode);
    }

    return antinodes;
}

auto PointHash::operator()(Point const p) const noexcept -> std::size_t
{
    return std::hash<std::size_t> {}(p.x) ^ (std::hash<std::size_t> {}(p.y) * 2);
};

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

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const [grid, antennas] = parseInput(input);

    auto firstAntinodes = antennas | std::views::values
        | std::views::transform([](auto&& antennas) { return createAntinodes(antennas); })
        | std::views::join
        | std::views::filter([&grid](Point const node) { return isPointInsideGrid(node, grid); });

    PointSet firstAntinodeSet;
    for (auto pt : firstAntinodes) {
        firstAntinodeSet.insert(pt);
    }

    auto secondAntinodes = antennas | std::views::values
        | std::views::transform(
            [&grid](auto&& antennas) { return findPointsInGridAlongLines(grid, antennas); })
        | std::views::join;

    PointSet secondAntinodeSet;
    for (auto pt : secondAntinodes) {
        secondAntinodeSet.insert(pt);
    }

    return { firstAntinodeSet.size(), secondAntinodeSet.size() };
}

auto findPointsInGridAlongLine(Grid const grid, Point const pointA, Point const pointB) noexcept
    -> std::vector<Point>
{
    std::vector<Point> points;
    points.push_back(pointA);
    points.push_back(pointB);

    auto usedPointA = pointA;
    auto usedPointB = pointB;
    while (isPointInsideGrid(usedPointA, grid)) {
        auto const [newPointA, _] = createAntinodes(usedPointA, usedPointB);

        points.push_back(newPointA);

        usedPointB = usedPointA;
        usedPointA = newPointA;
    }

    usedPointA = pointA;
    usedPointB = pointB;
    while (isPointInsideGrid(usedPointB, grid)) {
        auto const [_, newPointB] = createAntinodes(usedPointA, usedPointB);

        points.push_back(newPointB);

        usedPointA = usedPointB;
        usedPointB = newPointB;
    }

    return points;
}

auto findPointsInGridAlongLines(Grid const grid, std::span<Point const> const points) noexcept
    -> PointSet
{
    auto pointPairs = std::views::cartesian_product(points, points)
        | std::views::filter(
            [](std::pair<Point, Point> const& points) { return points.first != points.second; });

    PointSet antinodes;

    for (auto const [firstPoint, secondPoint] : pointPairs) {
        for (auto const& node : findPointsInGridAlongLine(grid, firstPoint, secondPoint)
                | std::views::filter(
                    [&grid](Point const node) { return isPointInsideGrid(node, grid); })) {
            antinodes.insert(node);
        }
    }

    return antinodes;
}

} // namespace ResonantCollinearity
