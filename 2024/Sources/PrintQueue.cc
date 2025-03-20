#include "PrintQueue.hh"

#include <algorithm>
#include <iterator>
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
auto parseInput(std::string const input) noexcept -> std::pair<OrderingRule, PageUpdates>
{
    auto const splitPosition = static_cast<std::ptrdiff_t>(input.find("\n\n"));

    auto const pageUpdates = std::string_view { input.cbegin() + splitPosition + 2, input.cend() };

    return { {}, ::parsePageUpdates(pageUpdates) };
}

} // namespace PrintQueue
