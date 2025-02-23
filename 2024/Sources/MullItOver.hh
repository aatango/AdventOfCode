// Advent of Code, 2024, day 01

#ifndef MULLITOVER_HH
#define MULLITOVER_HH

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace MullItOver {

auto solve(std::string) noexcept -> std::pair<std::size_t, std::size_t>;

struct Multiplication {
    std::size_t multiplicand;
    std::size_t multiplier;

private:
    friend auto operator==(Multiplication, Multiplication) noexcept -> bool = default;
};

using Multiplications = std::vector<Multiplication>;

auto parseInput(std::string, bool handleConditionals = false) noexcept -> Multiplications;

} // namespace MullItOver

#endif // MULLITOVER_HH
