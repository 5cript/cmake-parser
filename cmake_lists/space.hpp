#pragma once

#include <string>
#include <string_view>

namespace CMakeParser::DataStructures
{
    struct Space
    {
        std::string space;

        int tryConsume(std::string_view stream);
        bool empty() const noexcept;
        void serialize(std::ostream& out) const;
    };
}
