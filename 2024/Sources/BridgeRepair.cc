#include "BridgeRepair.hh"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <ranges>
#include <string>

namespace {

auto solve(BridgeRepair::Equations const& equations, bool const concat = false) -> std::size_t
{
    auto validResults = equations | std::views::filter([concat](BridgeRepair::Equation const& e) {
        return BridgeRepair::isValidEquation(e, concat);
    }) | std::views::keys;

    return std::accumulate(validResults.cbegin(), validResults.cend(), 0ULL);
}

} // namespace

namespace BridgeRepair {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const equations = parseInput(input);

    return { ::solve(equations), ::solve(equations, true) };
}

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

auto isValidEquation(Equation const& equation, bool const canConcatenate) noexcept -> bool
{
    auto const& [result, operands] = equation;

    // NOLINTNEXTLINE(misc-no-recursion)
    return [](this auto const& itself, auto const& operands, std::size_t remainder,
               bool const concat) -> bool {
        if (operands.size() == 1)
            return operands.front() == remainder;

        if (remainder < operands.front())
            // Cannot divide or subtract the operand from the remainder, and get a natural number;
            return false;

        auto const operand = operands.front();
        auto const remainingOperands
            = operands | std::views::drop(1) | std::ranges::to<std::vector<std::size_t>>();

        if (concat) {
            auto const numberOfDigits = static_cast<std::size_t>(std::log10(operand) + 1);
            auto const divider = static_cast<std::size_t>(std::pow(10, numberOfDigits));

            if ((remainder % divider == operand)
                && itself(remainingOperands, remainder / divider, concat))
                return true;
        }

        return remainder % operand == 0 && itself(remainingOperands, remainder / operand, concat)
            ? true
            : itself(remainingOperands, remainder - operand, concat);
    }(operands | std::views::reverse, result, canConcatenate);
}

} // namespace BridgeRepair
