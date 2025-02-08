// Advent of Code, 2024, day 01

#ifndef HISTORIANHYSTERIA_HH
#define HISTORIANHYSTERIA_HH

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace HistorianHysteria {

using List = std::vector<std::size_t>;
using PairedLists = std::pair<List, List>;

auto parseInput(std::string const&) noexcept -> PairedLists;

} // namespace HistorianHysteria

#endif // HISTORIANHYSTERIA_HH
