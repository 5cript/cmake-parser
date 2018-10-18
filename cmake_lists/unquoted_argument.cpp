#include "unquoted_argument.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int UnquotedArgument::tryConsume(std::string_view stream)
    {
        std::string none{"()#\"'\r\n\t "};
        auto i = std::begin(stream);
        for (; i != std::end(stream); ++i)
        {
            bool inv = false;
            for (auto const j : none)
                if (*i == j)
                {
                    inv = true;
                    break;
                }

            if (inv)
                break;
        }
        if (i == std::begin(stream))
            return 0;
        if (i == std::end(stream))
            return 0;
        unquotedArgument = std::string{std::begin(stream), i};
        return unquotedArgument.size();
    }
//---------------------------------------------------------------------------------------------------------------------
    void UnquotedArgument::serialize(std::ostream& out) const
    {
        out << unquotedArgument;
    }
//#####################################################################################################################
}
