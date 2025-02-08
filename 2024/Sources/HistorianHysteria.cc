#include "HistorianHysteria.hh"

#include <algorithm>
#include <sstream>

namespace HistorianHysteria {

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

} // namespace HistorianHysteria
