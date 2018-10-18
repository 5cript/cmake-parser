#pragma once

#include "argument.hpp"
#include "separation.hpp"
#include "argument.hpp"

#include "separation.hpp"
#include "argument.hpp"
#include "arguments.hpp"

#include <vector>
#include <optional>

#include <optional>
#include <vector>

namespace CMakeParser::DataStructures
{
    struct SeparatedArguments;

    struct Arguments
    {
        std::optional <Argument> argument;
        std::vector <SeparatedArguments> seperatedArguments;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };

    struct SeparatedArguments
    {
        std::vector <Separation> separation;
        std::variant <std::optional <Argument>, Arguments> separatedArguments;

        int tryConsume(std::string_view stream);
        void serialize(std::ostream& out) const;
    };
}
