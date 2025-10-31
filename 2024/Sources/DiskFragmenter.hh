#pragma once // Advent of Code 2024, day 09

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace DiskFragmenter {

auto solve(std::string) noexcept -> std::pair<std::size_t, std::size_t>;

auto parseInput(std::string_view) noexcept -> std::vector<unsigned>;
auto defragmentByBlock(std::vector<unsigned> diskMap) noexcept -> std::vector<unsigned>;
auto defragmentByFile(std::vector<unsigned> condensedDiskMap) noexcept
    -> std::vector<std::optional<unsigned>>;

} // namespace DiskFragmenter
