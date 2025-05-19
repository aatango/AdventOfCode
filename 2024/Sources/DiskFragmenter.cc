#include "DiskFragmenter.hh"

#include <ranges>

namespace DiskFragmenter {

auto parseInput(std::string_view const input) noexcept -> std::vector<unsigned>
{
    return input | std::views::take_while([](char c) { return c != '\n'; })
        | std::views::transform([](char const c) { return c - '0'; })
        | std::ranges::to<std::vector<unsigned>>();
}

} // namespace DiskFragmenter
