#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto value = LerpUnclamped(0, 10, 1.1f);

    std::cout << value << std::endl; // 11

    return 0;
}
