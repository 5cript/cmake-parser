#include "line_comment.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int LineComment::tryConsume(std::string_view stream)
    {
        if (stream.empty())
            return 0;

        if (stream.front() != '#')
            return 0;

        stream.remove_prefix(1);
        auto i = std::begin(stream);
        for (; i != std::end(stream) && *i != '\n'; ++i)
        { }

        if (i == std::end(stream))
            return stream.size() + 1;

        if (*(i-1) == '\r')
            lineComment = std::string{std::begin(stream), i - 1};
        else
            lineComment = std::string{std::begin(stream), i};
        return i - std::begin(stream) + 1;
    }
//---------------------------------------------------------------------------------------------------------------------
    void LineComment::serialize(std::ostream& out) const
    {
        out << '#';
        out << lineComment;
    }
//#####################################################################################################################
}
