#include "quoted_argument.hpp"

#include <cctype>

namespace CMakeParser::DataStructures
{
    using namespace std::string_literals;
//#####################################################################################################################
    int QuotedArgument::tryConsume(std::string_view stream)
    {
        if (stream.empty())
            return 0;

        if (stream.front() != '"')
            return 0;
        stream.remove_prefix(1);

        bool slashPreceeded = false;
        auto i = std::begin(stream);

        // An iterator that indicates what characters on the stream yet have to be added to the string.
        auto encompassed = std::begin(stream);
        int escapedCount = 0;
        for (; i != std::end(stream); ++i)
        {
            auto& ref = *i;
            if (ref == '\\')
            {
                if (!slashPreceeded)
                {
                    slashPreceeded = true;
                    ++escapedCount;
                    continue;
                }
                else
                {
                    quotedArgument += std::string{encompassed, i-1}; // take one of the slashes
                    encompassed = i + 1;
                }
            }
            else
            {
                if (slashPreceeded)
                {
                    // store all previous characters away.
                    if (std::distance(encompassed, i-1) > 0)
                        quotedArgument += std::string{encompassed, i-1};

                    if (*i == 't')
                        quotedArgument.push_back('\t');
                    else if (*i == 'r')
                        quotedArgument.push_back('\r');
                    else if (*i == 'n')
                        quotedArgument.push_back('\n');
                    else if (std::isalnum(*i))
                        throw std::runtime_error(("Invalid character escape \\"s + *i).c_str());
                    else
                        quotedArgument.push_back(*i);

                    encompassed = i+1;
                }
                else if (*i == '"')
                {
                    if (encompassed != i)
                        quotedArgument += std::string{encompassed, i};
                    break;
                }
            }
            slashPreceeded = false;
        }

        if (i == std::end(stream))
            return 0;
        else
            return quotedArgument.size() + 2 + escapedCount;
    }
//---------------------------------------------------------------------------------------------------------------------
    void QuotedArgument::serialize(std::ostream& out) const
    {
        out.put('"');
        for(auto const& i : quotedArgument)
        {
            if (i == '\n')
                out << "\\n";
            else if (i == '\r')
                out << "\\r";
            else if (i == '\t')
                out << "\\t";
            else if (i == ';')
                out << "\\;";
            else
            {
                out.put(i);
            }
        }
        out.put('"');
    }
//#####################################################################################################################
}
