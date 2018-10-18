#include "separation.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int Separation::tryConsume(std::string_view stream)
    {
        int consumed = 0;

        // if space
        Space s;
        consumed = s.tryConsume(stream);
        if (consumed)
        {
            space = s;
            return consumed;
        }

        // elif line ending
        LineEnding le;
        consumed = le.tryConsume(stream);
        if (consumed)
        {
            ending = le;
            return consumed;
        }

        // else
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    void Separation::serialize(std::ostream& out) const
    {
        if (space)
            space.value().serialize(out);
        else if (ending)
            ending.value().serialize(out);
    }
//#####################################################################################################################
}
