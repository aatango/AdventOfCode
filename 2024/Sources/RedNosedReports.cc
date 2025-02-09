#include "RedNosedReports.hh"

#include <ranges>
#include <string>

namespace {

auto formatReport(auto&& unformattedRange) noexcept -> RedNosedReports::Report
{
    return unformattedRange | std::views::split(' ')
        | std::views::transform(
            [](auto&& s) -> std::size_t { return std::stoull(std::string { s.begin(), s.end() }); })
        | std::ranges::to<RedNosedReports::Report>();
}

} // namespace

namespace RedNosedReports {

auto parseInput(std::string_view const input) noexcept -> Reports
{
    return input | std::views::split('\n')
        | std::views::take_while([](auto&& line) { return !line.empty(); })
        | std::views::transform([](auto&& line) -> Report { return ::formatReport(line); })
        | std::ranges::to<Reports>();
}

} // namespace RedNosedReports
