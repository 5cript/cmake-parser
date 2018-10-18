#pragma once

#include "bracket_argument.hpp"
#include "quoted_argument.hpp"
#include "unquoted_argument.hpp"

#include <variant>

namespace CMakeParser::DataStructures
{
    struct Argument
    {
        std::variant <
            BracketArgument,
            QuotedArgument,
            UnquotedArgument
        > argument;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
