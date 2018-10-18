#pragma once

#include "command_invocation.hpp"
#include "bracket_comment.hpp"
#include "line_ending.hpp"
#include "space.hpp"

#include <string_view>
#include <variant>
#include <vector>

namespace CMakeParser::DataStructures
{
    struct FileElement
    {
        std::variant <
            CommandInvocation,
            std::vector <
                std::variant <
                    BracketComment,
                    Space
                >
            >
        > element;
        LineEnding lineEnding;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
