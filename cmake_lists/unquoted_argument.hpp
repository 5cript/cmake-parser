#pragma once

#include <string>
#include <string_view>
#include <iostream>

namespace CMakeParser::DataStructures
{
    struct UnquotedArgument
    {
        std::string unquotedArgument;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
