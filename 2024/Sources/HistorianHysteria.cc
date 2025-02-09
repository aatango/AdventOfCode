#include "HistorianHysteria.hh"

#include <algorithm>
#include <numeric>
#include <sstream>

namespace {

auto accumulate(HistorianHysteria::List const& list) noexcept -> std::size_t
{
    return std::accumulate(list.begin(), list.end(), std::size_t { 0 });
}

} // namespace

namespace HistorianHysteria {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const [leftList, rightList] = parseInput(input);

    auto const distances = calculateDistances(leftList, rightList);
    auto const scores = scoreLists(leftList, rightList);

    return { ::accumulate(distances), ::accumulate(scores) };
}

auto parseInput(std::string const& input) noexcept -> PairedLists
{
    auto iss = std::istringstream { input };

    auto leftValue = std::size_t {};
    auto rightValue = std::size_t {};

    auto leftList = List {};
    auto rightList = List {};

    {
        auto const listLength = std::ranges::count(input, '\n');
        leftList.reserve(listLength);
        rightList.reserve(listLength);
    }

    while (iss >> leftValue >> rightValue) {
        leftList.push_back(leftValue);
        rightList.push_back(rightValue);
    }

    return { leftList, rightList };
}

auto calculateDistances(List lhs, List rhs) noexcept -> List
{
    std::ranges::sort(lhs);
    std::ranges::sort(rhs);

    auto differences = List {};

    std::ranges::transform(lhs, rhs, std::back_inserter(differences),
        [](std::size_t const x, std::size_t const y) -> std::size_t {
            return x >= y ? x - y : y - x;
        });

    return differences;
}

auto scoreLists(List lhs, List const rhs) noexcept -> List
{
    std::vector<std::size_t> scores;

    std::ranges::transform(lhs, std::back_inserter(scores),
        [&rhs](auto const x) { return x * std::ranges::count(rhs, x); });

    return scores;
}

} // namespace HistorianHysteria
