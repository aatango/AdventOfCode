#pragma once // Advent of Code, 2024, day 07

#include <cstddef>
#include <string_view>
#include <utility>
#include <vector>

namespace BridgeRepair {

using Equation = std::pair<std::size_t, std::vector<std::size_t>>; // Result, and operands
using Equations = std::vector<Equation>;

auto parseInput(std::string_view) noexcept -> Equations;
auto isValidEquation(Equation const&) noexcept -> bool;

} // namespace BridgeRepair
