#include "argument.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int Argument::tryConsume(std::string_view stream)
    {
        BracketArgument bracketArg;
        int consumed = bracketArg.tryConsume(stream);
        if (consumed != 0)
        {
            argument = bracketArg;
            return consumed;
        }

        QuotedArgument quotArg;
        consumed = quotArg.tryConsume(stream);
        if (consumed != 0)
        {
            argument = quotArg;
            return consumed;
        }

        UnquotedArgument unquotArg;
        consumed = unquotArg.tryConsume(stream);
        if (consumed != 0)
        {
            argument = unquotArg;
            return consumed;
        }
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    void Argument::serialize(std::ostream& out) const
    {
        std::visit([&out](auto const& arg) {
            arg.serialize(out);
        }, argument);
    }
//#####################################################################################################################
}
