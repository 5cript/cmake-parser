#include "cmake_lists.hpp"

namespace CMakeParser
{
//#####################################################################################################################
    CMakeListsParseException::CMakeListsParseException(std::string message, int consumationAmount)
        : message{std::move(message)}
        , consumationAmount{consumationAmount}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    char const* CMakeListsParseException::what() const noexcept
    {
        return message.c_str();
    }
//#####################################################################################################################
namespace DataStructures
{
    int CMakeLists::tryConsume(std::string_view stream)
    {
        int totalConsumed = 0;
        try
        {
            for(int consumeAmount{1}; consumeAmount != 0;)
            {
                FileElement single;
                if ((consumeAmount = single.tryConsume(stream)) != 0)
                {
                    fileElements.push_back(single);
                    stream.remove_prefix(consumeAmount);
                }
                totalConsumed += consumeAmount;
            }
        }
        catch (std::exception const& exc)
        {
            throw CMakeListsParseException{{exc.what()}, totalConsumed};
        }

        return totalConsumed;
    }
//---------------------------------------------------------------------------------------------------------------------
    void CMakeLists::serialize(std::ostream& out) const
    {
        for (auto const& element : fileElements)
            element.serialize(out);
    }
//#####################################################################################################################
}
}
