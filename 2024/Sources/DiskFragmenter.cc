#include "DiskFragmenter.hh"

#include <numeric>
#include <ranges>

namespace DiskFragmenter {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const defragmentedDisk = defragmentByBlock(parseInput(input));

    auto checkSum = std::size_t { 0 };
    for (auto const [i, id] : defragmentedDisk | std::views::enumerate) {
        checkSum += i * id;
    }

    return { checkSum, 0 };
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

    return defragmentedDisk;
}

} // namespace DiskFragmenter
