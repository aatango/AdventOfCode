// Advent of Code, 2024, day 02

#ifndef REDNOSEDREPORTS_HH
#define REDNOSEDREPORTS_HH

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace RedNosedReports {

auto solve(std::string) noexcept -> std::pair<std::size_t, std::size_t>;

using Report = std::vector<std::size_t>;
using Reports = std::vector<Report>;

auto parseInput(std::string_view) noexcept -> Reports;
auto validateReport(Report const&, bool isDampened = false) noexcept -> bool;

} // namespace RedNosedReports

#endif // REDNOSEDREPORTS_HH
