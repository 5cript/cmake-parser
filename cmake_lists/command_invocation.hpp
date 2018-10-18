#pragma once

#include "space.hpp"
#include "arguments.hpp"

#include <string>
#include <string_view>

namespace CMakeParser::DataStructures
{
    struct CommandInvocation
    {
        Space space1;
        std::string identifier;
        Space space2;
        Arguments arguments;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
