#include "CeresSearch.hh"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ranges>

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

} // namespace CeresSearch
