#include "bracket_comment.hpp"

#ifndef NDEBUG
#   include <iostream>
#endif

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int BracketComment::tryConsume(std::string_view stream)
    {
        if (stream.empty())
            return 0;

        if (stream.front() != '#')
            return 0;

        stream.remove_prefix(1);
        if (int consumed; (consumed = bracketComment.tryConsume(stream)))
        {
            return consumed + 1;
        }
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    void BracketComment::serialize(std::ostream& out) const
    {
        out << '#';
        bracketComment.serialize(out);
    }
//#####################################################################################################################
}
