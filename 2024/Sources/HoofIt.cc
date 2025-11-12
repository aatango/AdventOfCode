#include "HoofIt.hh"

#include <algorithm>
#include <cctype>
#include <ostream>
#include <ranges>

namespace {

auto constexpr format(std::string_view const input) noexcept -> std::vector<std::size_t>
{
    return input | std::views::filter([](auto const c) { return !std::isspace(c); })
        | std::views::transform([](auto const c) { return c - '0'; })
        | std::ranges::to<std::vector<std::size_t>>();
}

} // namespace

namespace HoofIt {

Map::Map(std::string_view const input)
    : m_height { static_cast<std::size_t>(std::ranges::count(input, '\n')) }
    , m_width { static_cast<std::size_t>(std::ranges::find(input, '\n') - input.begin()) }
{
    auto const data = format(input);
    for (auto const [i, height] : data | std::views::enumerate) {
        auto const position = toPosition(i);
        if (height == 9) {
            m_peaks.insert(position);
            continue;
        }
        if (height == 0) {
            m_trailheads.insert(position);
        }
        m_steps[position].insert_range(neighboursOf(position)
            | std::views::filter([&](auto const p) { return data[from(p)] == height + 1; }));
    }
}

void PrintTo(Position const& pos, std::ostream* os) { std::print(*os, "({}, {})", pos.x, pos.y); }

auto Map::trailheads() const noexcept -> Positions const& { return m_trailheads; }
auto Map::peaks() const noexcept -> Positions const& { return m_peaks; }
auto Map::steps() const noexcept -> Steps const& { return m_steps; }

auto Map::neighboursOf(Position const position) const noexcept -> Positions
{
    auto result = Positions {};
    result.reserve(4);
    if (position.x > 0) {
        result.emplace(position.x - 1, position.y);
    }
    if (position.x < m_width - 1) {
        result.emplace(position.x + 1, position.y);
    }
    if (position.y > 0) {
        result.emplace(position.x, position.y - 1);
    }
    if (position.y < m_height - 1) {
        result.emplace(position.x, position.y + 1);
    }
    return result;
}

auto Map::from(Position const position) const noexcept -> std::size_t
{
    return position.x + (position.y * m_width);
}

auto Map::toPosition(std::size_t const index) const noexcept -> Position
{
    return { .x = index % m_width, .y = index / m_width };
}

} // namespace HoofIt
