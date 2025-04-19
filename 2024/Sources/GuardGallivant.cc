#include "GuardGallivant.hh"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <ranges>
#include <utility>

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

auto parseObstructions(std::string_view const input, std::size_t const mapWidth) noexcept
    -> GuardGallivant::Positions
{
    return input | std::views::enumerate
        | std::views::filter(
            [](std::pair<std::size_t, char> const& pair) { return pair.second == '#'; })
        | std::views::transform([&mapWidth](std::pair<std::size_t, char> const& pair) {
              return ::toPosition(pair.first, mapWidth);
          })
        | std::ranges::to<GuardGallivant::Positions>();
}

} // namespace

namespace GuardGallivant {

void PrintTo(Position const& pos, std::ostream* os) { *os << '(' << pos.x << ',' << pos.y << ')'; }

auto taxicabDistance(Position const& lhs, Position const& rhs) noexcept -> std::size_t
{
    return std::abs(static_cast<std::ptrdiff_t>(lhs.x) - static_cast<std::ptrdiff_t>(rhs.x))
        + std::abs(static_cast<std::ptrdiff_t>(lhs.y) - static_cast<std::ptrdiff_t>(rhs.y));
}

Map::Map(std::string_view const input)
    : m_height { static_cast<std::size_t>(std::ranges::count(input, '\n')) }
    , m_width { static_cast<std::size_t>(std::ranges::find(input, '\n') - input.begin()) }
    , m_guard { .position = ::parseGuardPosition(input, m_width),
        .orientation = ::parseGuardOrientation(input),
        .visitedPositions = { ::parseGuardPosition(input, m_width) } }
    , m_obstructions { ::parseObstructions(input, m_width) }
{
}

auto Map::guard() const noexcept -> Guard const& { return m_guard; }
auto Map::obstructions() const noexcept -> Positions const& { return m_obstructions; }

auto Map::isPositionAheadOfGuard(Position const& pos) const noexcept -> bool
{
    switch (m_guard.orientation) {
    case Orientation::Up:
        return pos.x == m_guard.position.x && pos.y < m_guard.position.y;
    case Orientation::Right:
        return pos.y == m_guard.position.y && pos.x > m_guard.position.x;
    case Orientation::Down:
        return pos.x == m_guard.position.x && pos.y > m_guard.position.y;
    case Orientation::Left:
        return pos.y == m_guard.position.y && pos.x < m_guard.position.x;
    default:
        return false;
    }
}

void Map::patrol() noexcept
{
    while (true) {
        auto guardAboutToExitMap = [this] {
            switch (m_guard.orientation) {
            case Orientation::Up:
                return m_guard.position.y == 0;
            case Orientation::Right:
                return m_guard.position.x == (m_width - 1);
            case Orientation::Down:
                return m_guard.position.y == (m_height - 1);
            case Orientation::Left:
                return m_guard.position.x == 0;
            default:
                return false;
            }
        }();

        if (guardAboutToExitMap)
            break;

        [this] {
            switch (m_guard.orientation) {
            case Orientation::Up:
                --m_guard.position.y;
                return;
            case Orientation::Right:
                ++m_guard.position.x;
                return;
            case Orientation::Down:
                ++m_guard.position.y;
                return;
            case Orientation::Left:
            default:
                --m_guard.position.x;
            }
        }();

        m_guard.visitedPositions.insert(m_guard.position);

        auto obstructionsAhead = m_obstructions
            | std::views::filter([this](Position const& p) { return isPositionAheadOfGuard(p); });

        if (obstructionsAhead.empty())
            continue;

        auto const closestObstruction = std::ranges::min(obstructionsAhead, {},
            [this](Position const& p) { return taxicabDistance(p, m_guard.position); });

        if (taxicabDistance(m_guard.position, closestObstruction) == 1) {
            m_guard.orientation = [this] {
                switch (m_guard.orientation) {
                case Orientation::Up:
                    return Orientation::Right;
                case Orientation::Right:
                    return Orientation::Down;
                case Orientation::Down:
                    return Orientation::Left;
                case Orientation::Left:
                default:
                    return Orientation::Up;
                }
            }();
        }
    }
}

} // namespace GuardGallivant
