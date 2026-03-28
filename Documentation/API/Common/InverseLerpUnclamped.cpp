#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

auto main() -> int
{
    auto value = InverseLerpUnclamped(0, 10, 11);

    std::cout << value << std::endl; // 1.1

    return 0;
}
