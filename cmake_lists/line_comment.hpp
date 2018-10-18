#pragma once

#include <string>
#include <string_view>
#include <iostream>

namespace CMakeParser::DataStructures
{
    struct LineComment
    {
        std::string lineComment;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
