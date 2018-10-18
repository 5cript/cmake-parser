#pragma once

#include "space.hpp"
#include "line_ending.hpp"

#include <variant>

namespace CMakeParser::DataStructures
{
    struct Separation
    {
        // even though both are "optional", one of them has to be set, but bot can be set at the same time.
        std::optional <Space> space;
        std::optional <LineEnding> ending;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
