#include "BridgeRepair.hh"

#include <algorithm>
#include <ranges>

namespace BridgeRepair {

auto parseInput(std::string_view const input) noexcept -> Equations
{
    auto lines = input | std::views::split('\n')
        | std::views::take_while([](auto const& line) { return !line.empty(); });

    auto results = lines | std::views::transform([](auto const& line) {
        return std::stoull(line | std::views::take_while([](auto const c) { return c != ':'; })
            | std::ranges::to<std::string>());
    });

    auto operands = lines | std::views::transform([](auto const& line) {
        return line | std::views::drop_while([](auto const c) { return c != ' '; })
            | std::views::drop(1) | std::views::split(' ')
            | std::views::transform(
                [](auto const& s) { return std::stoull(s | std::ranges::to<std::string>()); });
    });

    Equations equations;
    std::ranges::transform(
        results, operands, std::back_inserter(equations), [](std::size_t const r, auto&& ops) {
            return Equation { r, ops | std::ranges::to<std::vector<std::size_t>>() };
        });

    return equations;
}

} // namespace BridgeRepair
