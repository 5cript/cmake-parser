#pragma once

#include "line_comment.hpp"

#include <optional>
#include <string_view>

namespace CMakeParser::DataStructures
{
    struct LineEnding
    {
        std::optional <LineComment> comment;
        bool windowsNL;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
