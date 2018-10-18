#pragma once

// https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#grammar-token-line_comment

#include "file_element.hpp"

#include <vector>
#include <string_view>
#include <iostream>
#include <exception>

namespace CMakeParser
{
    struct CMakeListsParseException : public std::exception
    {
        CMakeListsParseException(std::string message, int consumationAmount);
        char const* what() const noexcept override;

        std::string message;
        int consumationAmount;
    };

    namespace DataStructures
    {
        struct CMakeLists
        {
            std::vector <FileElement> fileElements;

            int tryConsume(std::string_view stream);
            void serialize(std::ostream& out) const;
        };
    }
}
