#include "HistorianHysteria.hh"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <utility>

namespace HistorianHysteria {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::size_t
{

    auto [leftList, rightList] = parseInput(input);
    auto const calculatedDistances = calculateDistances(std::move(leftList), std::move(rightList));

    return std::accumulate(
        calculatedDistances.begin(), calculatedDistances.end(), std::size_t { 0 });
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

} // namespace HistorianHysteria
