#pragma once

#include <string>

namespace CMakeParser
{
    class ParserContext
    {
    public:
        void load(std::string const& fileName);

        std::string const& data();

    private:
        std::string data_;
    };
}
