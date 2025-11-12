#pragma once // Advent of Code, day 10

#include <cstddef>
#include <functional>
#include <iosfwd>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace HoofIt {

struct Position {
    std::size_t x;
    std::size_t y;

private:
    friend auto operator==(Position, Position) noexcept -> bool = default;
    friend void PrintTo(Position const&, std::ostream*);
};

} // namespace HoofIt

template <> struct std::hash<HoofIt::Position> {
    auto operator()(HoofIt::Position const& p) const -> std::size_t
    {
        return std::hash<std::size_t>()(p.x) ^ std::hash<std::size_t>()(p.y << 1U);
    }
};

namespace HoofIt {

using Positions = std::unordered_set<Position>;
using Steps = std::unordered_map<Position, Positions>;

class Map {
public:
    explicit Map(std::string_view input);

    [[nodiscard]] auto trailheads() const noexcept -> Positions const&;
    [[nodiscard]] auto peaks() const noexcept -> Positions const&;
    [[nodiscard]] auto steps() const noexcept -> Steps const&;

private:
    [[nodiscard]] auto from(Position) const noexcept -> std::size_t;
    [[nodiscard]] auto toPosition(std::size_t) const noexcept -> Position;
    [[nodiscard]] auto neighboursOf(Position) const noexcept -> Positions;

    std::size_t m_height;
    std::size_t m_width;

    Positions m_trailheads {};
    Positions m_peaks {};
    Steps m_steps {};
};

} // namespace HoofIt
