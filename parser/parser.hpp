#pragma once

#include "../cmake_lists/cmake_lists.hpp"
#include "parser_context.hpp"

#include <string>

namespace CMakeParser
{
    class Parser
    {
    public:
        Parser(std::string fileName);

        DataStructures::CMakeLists parse();

    private:
        std::string fileName_;
        ParserContext ctx_;
    };
}
