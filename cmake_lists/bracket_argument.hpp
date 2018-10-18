#pragma once

#include "../parser/backtrack_context.hpp"

#include <string>
#include <iostream>

namespace CMakeParser::DataStructures
{
    struct BracketArgument
    {
        int equalCount;
        std::string content;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
