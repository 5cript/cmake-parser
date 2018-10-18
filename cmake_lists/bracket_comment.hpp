#pragma once

#include "bracket_argument.hpp"

#include <string>
#include <string_view>

namespace CMakeParser::DataStructures
{
    struct BracketComment
    {
        BracketArgument bracketComment;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
