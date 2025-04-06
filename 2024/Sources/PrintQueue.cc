#include "PrintQueue.hh"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <print>
#include <ranges>
#include <string>

namespace {

auto constexpr parseOrderingRules(std::string_view const input) noexcept
    -> PrintQueue::OrderingRules
{
    auto const lines = input | std::views::split('\n')
        | std::views::take_while([](auto&& line) { return !line.empty(); })
        | std::ranges::to<std::vector>();

    auto const keys = lines | std::views::transform([](auto&& line) {
        assert((line[2] == '|') && "Key must be two digits long!");

        return std::stoull(std::string { line.cbegin(), line.cbegin() + 2 });
    });

    auto const values = lines | std::views::transform([](auto&& line) {
        assert((line[5] == '\n') && "Value must be two digits long!");

        return std::stoull(std::string { line.cend() - 2, line.cend() });
    });

    PrintQueue::OrderingRules rule;

    std::ranges::for_each(std::views::zip(keys, values), [&rule](auto&& zipped) {
        auto const [key, value] = zipped;
        rule[key].push_back(value);
    });

    return rule;
}

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
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const [orderingRules, pageUpdates] = parseInput(input);

    auto middlePages = pageUpdates | std::views::filter([&orderingRules](auto&& x) {
        return isValidPageUpdate(x, orderingRules);
    }) | std::views::transform(findMiddlePage);

    return { std::accumulate(middlePages.cbegin(), middlePages.cend(), std::size_t { 0 }), 0 };
}

auto parseInput(std::string_view const input) noexcept -> std::pair<OrderingRules, PageUpdates>
{
    auto const splitPosition = static_cast<std::ptrdiff_t>(input.find("\n\n"));

    auto const orderingRules = std::string_view { input.cbegin(), input.cbegin() + splitPosition };
    auto const pageUpdates = std::string_view { input.cbegin() + splitPosition + 2, input.cend() };

    return { ::parseOrderingRules(orderingRules), ::parsePageUpdates(pageUpdates) };
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
