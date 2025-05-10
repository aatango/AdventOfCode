#include "ResonantCollinearity.hh"

#include <ostream>

namespace ResonantCollinearity {

void PrintTo(Point pt, std::ostream* os) { *os << "{.x= " << pt.x << ", .y= " << pt.y << "}"; }

auto createAntinodes(Point const lhs, Point const rhs) noexcept -> std::pair<Point, Point>
{
    auto const magnitudeX = rhs.x - lhs.x;
    auto const magnitudeY = rhs.y - lhs.y;

    return { Point { .x = lhs.x - magnitudeX, .y = lhs.y - magnitudeY },
        Point { .x = rhs.x + magnitudeX, .y = rhs.y + magnitudeY } };
}

} // namespace ResonantCollinearity
