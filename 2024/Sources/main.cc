#include "HistorianHysteria.hh"

#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <print>

enum class Puzzles : std::uint8_t {
    HistorianHysteria = 01,
};

int main()
{
    auto const inputFolder = std::filesystem::path("Input");

    auto inputDay01 = std::ifstream { inputFolder
        / std::format("{:02}.txt", static_cast<int>(Puzzles::HistorianHysteria)) };

    auto const [firstResult, secondResult] = HistorianHysteria::solve(std::string {
        std::istreambuf_iterator<char> { inputDay01 }, std::istreambuf_iterator<char> {} });

    std::println("Day 01 - Historian Hysteria: {} {}", firstResult, secondResult);
}
