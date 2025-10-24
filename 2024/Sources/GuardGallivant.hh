#pragma once // Advent of Code, 2024, day 06

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string_view>
#include <unordered_set>

namespace GuardGallivant {

auto solve(std::string) noexcept -> std::pair<std::size_t, std::size_t>;

struct Position {
    std::size_t x;
    std::size_t y;

private:
    friend auto operator==(Position, Position) noexcept -> bool = default;
    friend void PrintTo(Position const&, std::ostream*);
};

using Positions = std::unordered_set<Position>;

} // namespace GuardGallivant

template <> struct std::hash<GuardGallivant::Position> {
    auto operator()(GuardGallivant::Position const& p) const -> std::size_t
    {
        return std::hash<std::size_t>()(p.x) ^ std::hash<std::size_t>()(p.y << 1U);
    }
};

namespace GuardGallivant {

enum class Orientation : std::uint8_t { Up, Right, Down, Left };

struct Guard {
    Position position;
    Orientation orientation;
    Positions visitedPositions;
};

class Map {
public:
    explicit Map(std::string_view input);

    Map(Map const&) = default;
    Map(Map&&) = delete;

    ~Map() = default;

    [[nodiscard]] auto guard() const noexcept -> Guard const&;
    [[nodiscard]] auto obstructions() const noexcept -> Positions const&;
    [[nodiscard]] auto positions() const noexcept -> Positions const&;

    void addObstruction(Position) noexcept;

    auto operator=(Map const&) -> Map& = default;
    auto operator=(Map&&) -> Map& = delete;
    auto completePatrol() noexcept -> bool;

private:
    std::size_t m_height;
    std::size_t m_width;

    Guard m_guard;

    Positions m_obstructions;
};

} // namespace GuardGallivant
