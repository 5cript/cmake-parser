#include "file_element.hpp"

#include <type_traits>
#include <stdexcept>

namespace
{
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
}

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int FileElement::tryConsume(std::string_view stream)
    {
        int totalConsumed = 0;
        CommandInvocation command;
        if ((totalConsumed = command.tryConsume(stream)) != 0)
        {
            element = command;
            stream.remove_prefix(totalConsumed);
        }
        else
        {
            std::vector <std::variant <BracketComment, Space>> commentOrSpace;
            int singleConsumation = 0;
            do
            {
                BracketComment bcomment;
                if ((singleConsumation = bcomment.tryConsume(stream)) == 0)
                {
                    Space space;
                    singleConsumation = space.tryConsume(stream);
                    if (!space.empty())
                        commentOrSpace.emplace_back(space);
                }
                else
                    commentOrSpace.emplace_back(bcomment);

                totalConsumed += singleConsumation;
                if (singleConsumation != 0)
                    stream.remove_prefix(singleConsumation);
            } while (singleConsumation != 0);
            if (!commentOrSpace.empty())
                element = commentOrSpace;
        }
        int leConsumed = lineEnding.tryConsume(stream);

        return totalConsumed + leConsumed;
    }
//---------------------------------------------------------------------------------------------------------------------
    void FileElement::serialize(std::ostream& out) const
    {
        if (element.index() == std::variant_npos)
            return;
        std::visit(overloaded{
            [&out](CommandInvocation const& value)
            {
                value.serialize(out);
            },
            [&out](std::vector <std::variant <BracketComment, Space>> const& vec)
            {
                for (auto&& i : vec)
                    std::visit([&out](auto&& value){
                        value.serialize(out);
                    }, i);
            }
        }, element);
        lineEnding.serialize(out);
    }
//#####################################################################################################################
}
