#include "line_ending.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int LineEnding::tryConsume(std::string_view stream)
    {
        LineComment potComment;
        int consumed;
        if ((consumed = potComment.tryConsume(stream)) != 0)
            comment = std::move(potComment);
        stream.remove_prefix(consumed);

        windowsNL = false;
        if (stream.empty())
            return 0;
        if (stream.front() == '\n')
            return consumed + 1;
        if (stream.size() >= 2 && stream.compare(0, 2, "\r\n", 2) == 0)
        {
            windowsNL = true;
            return consumed + 2;
        }
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    void LineEnding::serialize(std::ostream& out) const
    {
        if (comment)
            comment.value().serialize(out);
        if (windowsNL)
            out << "\r\n";
        else
            out << "\n";
    }
//#####################################################################################################################
}
