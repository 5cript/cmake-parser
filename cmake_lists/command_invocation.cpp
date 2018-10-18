#include "command_invocation.hpp"

#include <cctype>

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int CommandInvocation::tryConsume(std::string_view stream)
    {
        int initialSize = stream.size();
        auto consumed = space1.tryConsume(stream);
        stream.remove_prefix(consumed);

        // identifier
        if (!std::isalpha(stream.front()))
            return 0;

        auto i = std::begin(stream) + 1;
        for (; i != std::end(stream) && (std::isalnum(*i) || *i == '_'); ++i)
        { }

        if (i == std::end(stream))
            return 0;

        identifier = std::string{std::begin(stream), i};
        stream.remove_prefix(identifier.size());

        // space 2
        consumed = space2.tryConsume(stream);
        stream.remove_prefix(consumed);

        if (stream.front() != '(')
            return 0;
        stream.remove_prefix(1);

        consumed = arguments.tryConsume(stream);
        stream.remove_prefix(consumed);

        if (stream.front() != ')')
            return 0;

        return initialSize - stream.size() + 1 /*)*/;
    }
//---------------------------------------------------------------------------------------------------------------------
    void CommandInvocation::serialize(std::ostream& out) const
    {
        space1.serialize(out);
        out << identifier;
        space2.serialize(out);
        out << '(';
        arguments.serialize(out);
        out << ')';
    }
//#####################################################################################################################
}
