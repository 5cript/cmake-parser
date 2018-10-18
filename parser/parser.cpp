#include "parser.hpp"

#include <stdexcept>

namespace CMakeParser
{
//#####################################################################################################################
    Parser::Parser(std::string fileName)
        : fileName_{std::move(fileName)}
        , ctx_{}
    {
        ctx_.load(fileName_);
    }
//---------------------------------------------------------------------------------------------------------------------
    DataStructures::CMakeLists Parser::parse()
    {
        using namespace std::string_literals;

        DataStructures::CMakeLists cmakeFile;
        auto const& data = ctx_.data();

        auto throwError = [&data](int consumed, std::string const& specificError = {})
        {
            int line = 1;
            for (int i = 0; i != consumed; ++i)
                if (data[i] == '\n')
                    ++line;
            if (specificError.empty())
                throw std::runtime_error((
                    "Unspecified error in line (unexpected input on stream) "s +
                    " in line " +
                    std::to_string(line)
                ).c_str());
            else
                throw std::runtime_error((
                    specificError +
                    " in line " +
                    std::to_string(line)
                ).c_str());
        };

        int consumed{0};
        try
        {
            consumed = cmakeFile.tryConsume(std::string_view{data.c_str(), data.size()});
            if (consumed != static_cast <int> (data.size()))
                throwError(consumed);
        }
        catch (CMakeListsParseException const& exc)
        {
            throwError(exc.consumationAmount, exc.what());
        }
        return cmakeFile;
    }
//#####################################################################################################################
}
