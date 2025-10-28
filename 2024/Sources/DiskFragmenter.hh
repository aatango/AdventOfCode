#pragma once // Advent of Code 2024, day 09

#include <string_view>
#include <vector>

namespace DiskFragmenter {

auto parseInput(std::string_view) noexcept -> std::vector<unsigned>;
auto defragmentByBlock(std::vector<unsigned> diskMap) noexcept -> std::vector<unsigned>;

} // namespace DiskFragmenter
