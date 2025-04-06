#include "PrintQueue.hh"

#include <algorithm>
#include <cassert>
#include <print>
#include <ranges>
#include <string>

namespace {

auto constexpr parsePageUpdates(std::string_view const input) noexcept -> PrintQueue::PageUpdates
{
    auto constexpr parsePageUpdate = [](auto&& update) {
        return update | std::views::split(',') | std::views::transform([](auto&& x) -> std::size_t {
            return std::stoull(std::string { x.cbegin(), x.cend() });
        });
    };

    return input | std::views::split('\n')
        | std::views::take_while([](auto&& line) { return !line.empty(); })
        | std::views::transform(parsePageUpdate) | std::ranges::to<PrintQueue::PageUpdates>();
}

} // namespace

namespace PrintQueue {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto parseInput(std::string input) noexcept -> std::pair<OrderingRules, PageUpdates>
{
    auto const splitPosition = static_cast<std::ptrdiff_t>(input.find("\n\n"));

    auto const pageUpdates = std::string_view { input.cbegin() + splitPosition + 2, input.cend() };

    return { {}, ::parsePageUpdates(pageUpdates) };
}

auto isValidPageUpdate(
    std::span<std::size_t const> const pages, OrderingRules const& rules) noexcept -> bool
{
    auto const isValidPage = [&rules](auto const& pair) {
        auto const [first, second] = pair;
        return rules.contains(first) && std::ranges::contains(rules.at(first), second);
    };

    return std::ranges::all_of(pages | std::views::adjacent<2>, isValidPage);
}

auto findMiddlePage(std::span<std::size_t const> const pages) noexcept -> std::size_t
{
    assert((pages.size() % 2 == 1) && "Can only find middle page of an odd numbered update!");

    auto const iteratorToMiddlePage
        = pages.cbegin() + static_cast<std::ptrdiff_t>(pages.size() / 2);

    return *iteratorToMiddlePage;
}

} // namespace PrintQueue
