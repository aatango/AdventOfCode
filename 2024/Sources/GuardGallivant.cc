#include "GuardGallivant.hh"

#include <algorithm>
#include <ostream>

namespace {

auto constexpr parseGuardOrientation(std::string_view const input) noexcept
    -> GuardGallivant::Orientation
{
    switch (input[input.find_first_of("^>v<")]) {
    case '^':
        return GuardGallivant::Orientation::Up;
    case '>':
        return GuardGallivant::Orientation::Right;
    case '<':
        return GuardGallivant::Orientation::Left;
    case 'v':
        return GuardGallivant::Orientation::Down;
    default:
        std::terminate();
    }
}

auto toPosition(std::size_t const index, std::size_t mapWidth) noexcept -> GuardGallivant::Position
{
    mapWidth++; // Account for '\n' that separate each "row".

    auto const posY = std::size_t { index / mapWidth };
    auto const posX = std::size_t { index - (mapWidth * posY) };

    return { .x = posX, .y = posY };
}

auto parseGuardPosition(std::string_view const input, std::size_t const mapWidth) noexcept
    -> GuardGallivant::Position
{
    auto const index = input.find_first_of("^>v<"); // Input always has one guard.

    return toPosition(index, mapWidth);
}

} // namespace

namespace GuardGallivant {

void PrintTo(Position const& pos, std::ostream* os) { *os << '(' << pos.x << ',' << pos.y << ')'; }

Map::Map(std::string_view const input)
    : m_height { static_cast<std::size_t>(std::ranges::count(input, '\n')) }
    , m_width { static_cast<std::size_t>(std::ranges::find(input, '\n') - input.begin()) }
    , m_guard { .position = ::parseGuardPosition(input, m_width),
        .orientation = ::parseGuardOrientation(input),
        .visitedPositions = {} }
{
    m_guard.visitedPositions.insert(m_guard.position);
}

auto Map::guard() const noexcept -> Guard const& { return m_guard; }

} // namespace GuardGallivant
