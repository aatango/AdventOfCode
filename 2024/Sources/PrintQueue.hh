// Advent of Code, 2024, day 05

#pragma once

#include <cstddef>
#include <string>
#include <span>
#include <utility>
#include <vector>

namespace PrintQueue {

using OrderingRule = std::vector<std::size_t>;

using PageUpdate = std::vector<std::size_t>;
using PageUpdates = std::vector<PageUpdate>;

auto parseInput(std::string) noexcept -> std::pair<OrderingRule, PageUpdates>;

auto findMiddlePage(std::span<std::size_t const>) noexcept -> std::size_t;

} // namespace PrintQueue
