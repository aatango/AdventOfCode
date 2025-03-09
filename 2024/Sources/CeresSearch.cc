#include "CeresSearch.hh"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <ranges>

namespace {

auto isXmas(std::string_view const sv) noexcept -> bool { return sv == "xmas" || sv == "samx"; }

} // namespace

namespace CeresSearch {

Grid::Grid(std::string_view const input)
    : m_height { static_cast<std::size_t>(std::ranges::count(input, '\n')) }
    , m_width { static_cast<std::size_t>(std::ranges::find(input, '\n') - input.begin()) }
{
    m_data.reserve(m_width * m_height);
    m_data = input | std::views::filter([](char c) { return c != '\n'; })
        | std::views::transform([](char c) { return std::tolower(c); })
        | std::ranges::to<std::vector<char>>();
}

auto Grid::height() const noexcept -> std::size_t { return m_height; }
auto Grid::width() const noexcept -> std::size_t { return m_width; }

auto Grid::countXmas() const noexcept -> std::size_t
{
    auto countedXmas = std::size_t { 0 };

    for (auto const x : std::views::iota(std::size_t { 0 }, m_width)) {
        for (auto const y : std::views::iota(std::size_t { 0 }, m_height)) {

            if (auto const letter = m_data.at(x + (y * m_width)); letter == 'x' || letter == 's') {
                auto const startPosition = Position { .u = x, .v = y };

                countedXmas += static_cast<std::size_t>(isXmasEast(startPosition))
                    + static_cast<std::size_t>(isXmasSouthEast(startPosition))
                    + static_cast<std::size_t>(isXmasSouth(startPosition))
                    + static_cast<std::size_t>(isXmasSouthWest(startPosition));
            }
        }
    }

    return countedXmas;
}

auto Grid::isXmasEast(Position startPosition) const noexcept -> bool
{
    if (m_width - startPosition.u < 4)
        return false;

    auto const beginIterator = m_data.begin()
        + static_cast<std::ptrdiff_t>(startPosition.u + (startPosition.v * m_width));

    return ::isXmas(std::string_view { beginIterator, beginIterator + 4 });
}

auto Grid::isXmasSouthEast(Position startPosition) const noexcept -> bool
{
    if (m_width - startPosition.u < 4 || m_height - startPosition.v < 4)
        return false;

    auto sampleArray = std::array<char, 4> {};

    for (auto i : std::views::iota(0, 4)) {
        auto const x = startPosition.u + i;
        auto const y = startPosition.v + i;
        sampleArray.at(i) = m_data.at(x + (y * m_width));
    }

    return ::isXmas(std::string_view { sampleArray });
}

auto Grid::isXmasSouth(Position startPosition) const noexcept -> bool
{
    if (m_height - startPosition.v < 4)
        return false;

    auto sampleArray = std::array<char, 4> {};

    for (auto i : std::views::iota(0, 4)) {
        auto const y = startPosition.v + i;
        sampleArray.at(i) = m_data.at(startPosition.u + (y * m_width));
    }

    return ::isXmas(std::string_view { sampleArray });
}

auto Grid::isXmasSouthWest(Position startPosition) const noexcept -> bool
{
    if (startPosition.u < 3 || m_height - startPosition.v < 4)
        return false;

    auto sampleArray = std::array<char, 4> {};

    for (auto i : std::views::iota(0, 4)) {
        auto const x = startPosition.u - i;
        auto const y = startPosition.v + i;
        sampleArray.at(i) = m_data.at(x + (y * m_width));
    }

    return ::isXmas(std::string_view { sampleArray });
}

} // namespace CeresSearch
