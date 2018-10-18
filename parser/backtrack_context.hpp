#pragma once

#include <string_view>

namespace CMakeParser
{
    struct BacktrackContext
    {
        int totalBacktrackCount = 0;
        int backtrackCount = 0;

        void enterScope()
        {
            backtrackCount = 0;
        }
        void forward(int count)
        {
            totalBacktrackCount += count;
            backtrackCount = count;
        }
        int rewind()
        {
            int total = totalBacktrackCount;
            totalBacktrackCount = 0;
            backtrackCount = 0;
            return total;
        }
    };
}
