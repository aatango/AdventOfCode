#include "GuardGallivant.hh"

#include <algorithm>
#include <ostream>

namespace {

auto constexpr parseGuardOrientation(std::string_view const input) noexcept
    -> GuardGallivant::Orientation
{
    [[likely]] if (input.contains('^'))
        return GuardGallivant::Orientation::Up;

    if (input.contains('>'))
        return GuardGallivant::Orientation::Right;

    if (input.contains('<'))
        return GuardGallivant::Orientation::Left;

    return GuardGallivant::Orientation::Down;
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
        .walkedDistance = 0 }
{
}

auto Map::guard() const noexcept -> Guard const& { return m_guard; }

} // namespace GuardGallivant
