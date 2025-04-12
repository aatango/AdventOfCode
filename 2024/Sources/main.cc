#include "CeresSearch.hh"
#include "HistorianHysteria.hh"
#include "MullItOver.hh"
#include "RedNosedReports.hh"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <print>
#include <string_view>

namespace {

void solve(std::size_t const day, std::string_view const name, auto solverFunction) noexcept
{
    auto const inputFile = std::filesystem::path { "Input" } / name;

    auto inputStream = std::ifstream { inputFile };

    auto inputData = std::string { std::istreambuf_iterator<char> { inputStream },
        std::istreambuf_iterator<char> {} };

    auto const startTime = std::chrono::steady_clock::now();

    auto const [firstResult, secondResult] = solverFunction(std::move(inputData));

    auto const endTime = std::chrono::steady_clock::now();
    auto const duration
        = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::println("Day {:02}, {}: {} | {} ({})", day, name, firstResult, secondResult, duration);
}

} // namespace

int main()
{
    ::solve(01, "HistorianHysteria", HistorianHysteria::solve);
    ::solve(02, "RedNosedReports", RedNosedReports::solve);
    ::solve(03, "MullItOver", MullItOver::solve);
    ::solve(04, "CeresSearch", CeresSearch::solve);
}
