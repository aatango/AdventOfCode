// Advent of Code, 2024, day 02

#ifndef REDNOSEDREPORTS_HH
#define REDNOSEDREPORTS_HH

#include <cstddef>
#include <string_view>
#include <vector>

namespace RedNosedReports {

using Report = std::vector<std::size_t>;
using Reports = std::vector<Report>;

auto parseInput(std::string_view) noexcept -> Reports;
auto validateReport(Report const&) noexcept -> bool;

} // namespace RedNosedReports

#endif // REDNOSEDREPORTS_HH
