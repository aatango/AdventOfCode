#include "GuardGallivant.hh"

#include <algorithm>
#include <ostream>
#include <ranges>
#include <string>
#include <unordered_set>
#include <utility>

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

struct Step {
    GuardGallivant::Position position;
    GuardGallivant::Orientation orientation;

private:
    friend auto operator==(Step, Step) noexcept -> bool = default;
};

using Steps = std::unordered_set<Step>;

} // namespace

template <> struct std::hash<Step> {
    auto operator()(Step const& s) const -> std::size_t
    {
        return std::hash<GuardGallivant::Position>()(s.position)
            ^ std::hash<std::size_t>()(static_cast<std::size_t>(s.orientation) << 1U);
    }
};

namespace GuardGallivant {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const initialMap = Map { input };
    auto map = initialMap;
    map.completePatrol();

    auto const partOne = map.guard().visitedPositions.size();

    auto partTwo = std::size_t {};
    for (auto const p : map.positions()) {
        if (p == initialMap.guard().position)
            continue;

        auto mapToObstruct = initialMap;
        mapToObstruct.addObstruction(p);

        if (!mapToObstruct.completePatrol()) {
            partTwo++;
        }
    }

    return { partOne, partTwo };
}

void PrintTo(Position const& pos, std::ostream* os) { *os << '(' << pos.x << ',' << pos.y << ')'; }

Map::Map(std::string_view const input)
    : m_height { static_cast<std::size_t>(std::ranges::count(input, '\n')) }
    , m_width { static_cast<std::size_t>(std::ranges::find(input, '\n') - input.begin()) }
    , m_guard { .position = ::parseGuardPosition(input, m_width),
        .orientation = ::parseGuardOrientation(input),
        .visitedPositions = {} }
    , m_obstructions { ::parseObstructions(input, m_width) }
{
    m_guard.visitedPositions.insert(m_guard.position);
}

auto Map::guard() const noexcept -> Guard const& { return m_guard; }
auto Map::obstructions() const noexcept -> Positions const& { return m_obstructions; }
auto Map::positions() const noexcept -> Positions const& { return m_guard.visitedPositions; }

void Map::addObstruction(Position p) noexcept { m_obstructions.insert(p); }

auto Map::completePatrol() noexcept -> bool
{
    auto const isEndOfPatrol = [this]() -> bool {
        switch (m_guard.orientation) {
        case Orientation::Up:
            return m_guard.position.y == 0;
        case Orientation::Right:
            return m_guard.position.x == (m_width - 1);
        case Orientation::Down:
            return m_guard.position.y == (m_height - 1);
        case Orientation::Left:
        default:
            return m_guard.position.x == 0;
        }
    };

    auto const isObstructionAhead = [this]() -> bool {
        auto const positionAhead = [this]() -> Position {
            switch (m_guard.orientation) {
            case Orientation::Up:
                return { .x = m_guard.position.x, .y = m_guard.position.y - 1 };
            case Orientation::Right:
                return { .x = m_guard.position.x + 1, .y = m_guard.position.y };
            case Orientation::Down:
                return { .x = m_guard.position.x, .y = m_guard.position.y + 1 };
            case Orientation::Left:
            default:
                return { .x = m_guard.position.x - 1, .y = m_guard.position.y };
            }
        }();

        return m_obstructions.contains(positionAhead);
    };

    auto steps = Steps {};
    while (!isEndOfPatrol()) {
        if (isObstructionAhead()) {
            m_guard.orientation = [this]() -> Orientation {
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
            continue;
        }

        switch (m_guard.orientation) {
        case Orientation::Up:
            --m_guard.position.y;
            break;
        case Orientation::Right:
            ++m_guard.position.x;
            break;
        case Orientation::Down:
            ++m_guard.position.y;
            break;
        case Orientation::Left:
        default:
            --m_guard.position.x;
        }

        auto const nextStep
            = Step { .position = m_guard.position, .orientation = m_guard.orientation };

        if (steps.contains(nextStep))
            return false;

        m_guard.visitedPositions.insert(m_guard.position);
        steps.insert(nextStep);
    }

    return true;
}

} // namespace GuardGallivant
