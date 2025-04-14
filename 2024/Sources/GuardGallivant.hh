#pragma once // Advent of Code, 2024, day 06

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string_view>
#include <vector>

namespace GuardGallivant {

struct Position {
    std::size_t x;
    std::size_t y;

    friend auto operator==(Position, Position) noexcept -> bool = default;
    friend void PrintTo(Position const&, std::ostream*);
};

using Positions = std::vector<Position>;

enum class Orientation : std::uint8_t { Up, Right, Down, Left };

struct Guard {
    Position position;
    Orientation orientation;
    std::size_t walkedDistance;
};

class Map {
public:
    explicit Map(std::string_view input);

    [[nodiscard]] auto guard() const noexcept -> Guard const&;
    [[nodiscard]] auto obstructions() const noexcept -> std::vector<Position> const&;

private:
    std::size_t m_height;
    std::size_t m_width;

    Guard m_guard;

    Positions m_obstructions;
};

} // namespace GuardGallivant
