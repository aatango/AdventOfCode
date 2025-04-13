// Advent of Code, 2024, day 05

#pragma once

#include <cstddef>
#include <span>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace PrintQueue {

auto solve(std::string) noexcept -> std::pair<std::size_t, std::size_t>;

using Pages = std::vector<std::size_t>;
using PageUpdates = std::vector<Pages>;
using OrderingRules = std::unordered_map<std::size_t, Pages>;

auto parseInput(std::string_view) noexcept -> std::pair<OrderingRules, PageUpdates>;
auto isValidPageUpdate(std::span<std::size_t const>, OrderingRules const&) noexcept -> bool;
auto sortUpdate(Pages, OrderingRules const&) noexcept -> Pages;
auto findMiddlePage(std::span<std::size_t const>) noexcept -> std::size_t;

} // namespace PrintQueue
