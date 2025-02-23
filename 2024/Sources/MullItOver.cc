#include "MullItOver.hh"

#include <regex>
#include <string_view>

namespace {

void disableInstructions(std::string& input) noexcept
{
    std::string_view constexpr disablingInstruction = "don't()";
    std::string_view constexpr enablingInstruction = "do()";

    auto startIndex = input.find(disablingInstruction);

    while (startIndex != std::string::npos) {
        if (auto endIndex
            = input.find(enablingInstruction, startIndex + disablingInstruction.size());
            endIndex != std::string::npos) {
            input.erase(startIndex, endIndex - (startIndex + enablingInstruction.size()));
        } else {
            input.erase(startIndex);
        }

        startIndex = input.find(disablingInstruction);
    }
}

} // namespace

namespace MullItOver {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto solve(std::string input) noexcept -> std::pair<std::size_t, std::size_t>
{
    auto parsedInput = parseInput(input);

    auto sumOfInstructions = std::size_t { 0 };

    for (Multiplication mult : parsedInput) {
        sumOfInstructions += (mult.multiplicand * mult.multiplier);
    }

    return { sumOfInstructions, 0 };
}

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto parseInput(std::string input, bool handleConditionals) noexcept -> Multiplications
{

    if (handleConditionals) {
        ::disableInstructions(input);
    }

    auto const pattern = std::regex { R"(mul\((\d{1,3}),(\d{1,3})\))" };

    auto const inputBegin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto const inputEnd = std::sregex_iterator();

    auto multiplications = Multiplications {};
    multiplications.reserve(2 * std::distance(inputBegin, inputEnd));

    for (std::regex_iterator i = inputBegin; i != inputEnd; ++i) {
        auto const multiplicand = std::stoull((*i)[1].str());
        auto const multiplier = std::stoull((*i)[2].str());

        multiplications.emplace_back(multiplicand, multiplier);
    }

    return multiplications;
}

} // namespace MullItOver
