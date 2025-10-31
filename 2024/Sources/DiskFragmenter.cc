#include "DiskFragmenter.hh"

#include <numeric>
#include <ranges>

namespace DiskFragmenter {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const parsedInput = parseInput(input);

    auto partOne = std::size_t {};
    auto partTwo = std::size_t {};

    for (auto const [i, id] : defragmentByBlock(parsedInput) | std::views::enumerate) {
        partOne += i * id;
    }
    for (auto const [i, id] : defragmentByFile(parsedInput) | std::views::enumerate) {
        if (id.has_value()) {
            partTwo += i * (*id);
        }
    }

    return { partOne, partTwo };
}

auto parseInput(std::string_view const input) noexcept -> std::vector<unsigned>
{
    return input | std::views::take_while([](char c) { return c != '\n'; })
        | std::views::transform([](char const c) { return c - '0'; })
        | std::ranges::to<std::vector<unsigned>>();
}

auto defragmentByBlock(std::vector<unsigned int> diskMap) noexcept -> std::vector<unsigned>
{
    auto defragmentedDisk = std::vector<unsigned> {};

    defragmentedDisk.reserve(std::accumulate(diskMap.cbegin(), diskMap.cend(), 0U));

    auto startPos = std::size_t { 0 };
    auto endPos = diskMap.size() - 1;

    while (startPos < diskMap.size()) {
        if (startPos % 2 == 0) {
            defragmentedDisk.insert(defragmentedDisk.cend(), diskMap[startPos], startPos / 2);
            ++startPos;
        } else {
            while (diskMap[startPos] > 0) {
                if (diskMap[endPos] > 0) {
                    defragmentedDisk.push_back(endPos / 2);
                    --diskMap[endPos];
                    --diskMap[startPos];
                } else {
                    --endPos;
                    diskMap[endPos] = 0;
                    --endPos;
                }
            }
            ++startPos;
        }
    }

    defragmentedDisk.shrink_to_fit();

    return defragmentedDisk;
}

auto defragmentByFile(std::vector<unsigned int> diskMap) noexcept
    -> std::vector<std::optional<unsigned>>
{
    auto const originalMap = diskMap;

    auto defragmentedDisk = std::vector<std::optional<unsigned>> {};

    defragmentedDisk.reserve(std::accumulate(diskMap.cbegin(), diskMap.cend(), 0U));

    auto startPos = std::size_t { 0 };
    auto endPos = diskMap.size() - 1;

    while (startPos < diskMap.size()) {
        if (startPos % 2 == 0) {
            defragmentedDisk.insert(defragmentedDisk.cend(), originalMap[startPos],
                diskMap[startPos] == 0 ? std::nullopt : std::make_optional(startPos / 2));
            ++startPos;
        } else {
            auto rightPivot = endPos;
            while (diskMap[startPos] > 0) {
                if (startPos > rightPivot) {
                    defragmentedDisk.insert(
                        defragmentedDisk.cend(), diskMap[startPos], std::nullopt);
                    diskMap[startPos] = 0;
                    continue;
                }

                if (diskMap[startPos] < diskMap[rightPivot] || diskMap[rightPivot] == 0) {
                    rightPivot -= 2;
                } else if (diskMap[startPos] >= diskMap[rightPivot]) {
                    defragmentedDisk.insert(
                        defragmentedDisk.cend(), diskMap[rightPivot], rightPivot / 2);
                    diskMap[startPos] -= diskMap[rightPivot];
                    diskMap[rightPivot] = 0;
                }
            }
            ++startPos;
        }
    }

    return defragmentedDisk;
}

} // namespace DiskFragmenter
