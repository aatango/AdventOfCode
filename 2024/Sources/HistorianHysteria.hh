// Advent of Code, 2024, day 01

#ifndef HISTORIANHYSTERIA_HH
#define HISTORIANHYSTERIA_HH

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace HistorianHysteria {

auto solve(std::string) noexcept -> std::size_t;

using List = std::vector<std::size_t>;
using PairedLists = std::pair<List, List>;

auto parseInput(std::string const&) noexcept -> PairedLists;
auto calculateDistances(List, List) noexcept -> List;

} // namespace HistorianHysteria

#endif // HISTORIANHYSTERIA_HH
