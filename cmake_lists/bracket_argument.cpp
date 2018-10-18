#include "bracket_argument.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int BracketArgument::tryConsume(std::string_view stream)
    {
        if (stream.size() < 4)
            return 0;

        if (stream.front() != '[')
            return 0;
        stream.remove_prefix(1);

        auto iter = std::begin(stream);
        for (; iter != std::end(stream) && *iter == '='; ++iter)
        { }

        if (iter == std::end(stream))
            return 0;

        equalCount = iter - std::begin(stream);
        if (*iter != '[')
            return 0;

        stream.remove_prefix(equalCount + 1);
        iter = std::begin(stream);

        for (; iter != std::end(stream); ++iter)
        {
            if (*iter == ']')
            {
                if (std::end(stream) - iter < (equalCount + 1))
                    return 0;

                // range check ok, no test for =* and ]
                bool ok = true;
                for (int i = 0; i != equalCount; ++i)
                {
                    if (*(iter + i + 1) != '=')
                    {
                        ok = false;
                        break;
                    }
                }
                // =* not found, continue loop.
                if (!ok)
                    continue;

                // test ']'
                if (*(iter + equalCount + 1) == ']')
                    break; // -> success
                // else continue
            }
        }
        // TODO?: fast parser exit possible, this multibracket argument obviously emcompasses the entire document.
        if (iter == std::end(stream))
            return 0;

        content = std::string{std::begin(stream), iter};
        return content.length() + 4 + equalCount * 2;
    }
//---------------------------------------------------------------------------------------------------------------------
    void BracketArgument::serialize(std::ostream& out) const
    {
        out << "[";
        for (int i = 0; i != equalCount; ++i)
            out << '=';
        out << '[';
        out << content;
        out << ']';
        for (int i = 0; i != equalCount; ++i)
            out << '=';
        out << ']';
    }
//#####################################################################################################################
}
