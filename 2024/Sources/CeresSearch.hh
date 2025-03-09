// Advent of Code, 2024, day 04

#ifndef CERESSEARCH_HH
#define CERESSEARCH_HH

#include <cstddef>
#include <string_view>
#include <vector>

namespace CeresSearch {

struct Position {
    std::size_t u;
    std::size_t v;
};

class Grid {
public:
    explicit Grid(std::string_view input);

    [[nodiscard]] auto width() const noexcept -> std::size_t;
    [[nodiscard]] auto height() const noexcept -> std::size_t;

    [[nodiscard]] auto countXmas() const noexcept -> std::size_t;

private:
    [[nodiscard]] auto isXmasEast(Position) const noexcept -> bool;
    [[nodiscard]] auto isXmasSouthEast(Position) const noexcept -> bool;
    [[nodiscard]] auto isXmasSouth(Position) const noexcept -> bool;
    [[nodiscard]] auto isXmasSouthWest(Position) const noexcept -> bool;

    std::size_t m_height;
    std::size_t m_width;
    std::vector<char> m_data;
};

} // namespace CeresSearch

#endif // CERESSEARCH_HH
