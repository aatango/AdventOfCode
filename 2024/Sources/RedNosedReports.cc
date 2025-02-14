#include "RedNosedReports.hh"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <ranges>
#include <span>

namespace {

auto formatReport(auto&& unformattedRange) noexcept -> RedNosedReports::Report
{
    return unformattedRange | std::views::split(' ')
        | std::views::transform(
            [](auto&& s) -> std::size_t { return std::stoull(std::string { s.begin(), s.end() }); })
        | std::ranges::to<RedNosedReports::Report>();
}

auto adjacentDifferences(std::span<std::size_t const> input) noexcept -> std::vector<int>
{
    std::vector<int> adjacentDifferences;
    std::adjacent_difference(input.begin(), input.end(), std::back_inserter(adjacentDifferences));

    adjacentDifferences.erase(adjacentDifferences.begin());

    return adjacentDifferences;
}

auto isReportSorted(RedNosedReports::Report const& report) noexcept -> bool
{
    auto const levelDifferences = ::adjacentDifferences(report);

    return std::ranges::all_of(levelDifferences, [](auto const x) { return x > 0; })
        || std::ranges::all_of(levelDifferences, [](auto const x) { return x < 0; });
}

auto isReportStable(RedNosedReports::Report const& report) noexcept -> bool
{
    return std::ranges::all_of(::adjacentDifferences(report),
        [](auto const x) { return std::abs(x) > 0 && std::abs(x) < 4; });
}

} // namespace

namespace RedNosedReports {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string const input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto const parsedInput = parseInput(input);
    return { std::ranges::count_if(parsedInput, [](auto&& r) { return validateReport(r, false); }),
        std::ranges::count_if(parsedInput, [](auto&& r) { return validateReport(r, true); }) };
}

auto parseInput(std::string_view const input) noexcept -> Reports
{
    return input | std::views::split('\n')
        | std::views::take_while([](auto&& line) { return !line.empty(); })
        | std::views::transform([](auto&& line) -> Report { return ::formatReport(line); })
        | std::ranges::to<Reports>();
}

auto validateReport(Report const& report, bool isDampened) noexcept -> bool
{
    if (!isDampened)
        return ::isReportSorted(report) && ::isReportStable(report);

    for (auto i = std::size_t { 0 }; i < report.size(); ++i) {
        auto subReport = report;
        subReport.erase(subReport.begin() + i);

        if (::isReportSorted(subReport) && ::isReportStable(subReport))
            return true;
    }

    return false;
}

} // namespace RedNosedReports
