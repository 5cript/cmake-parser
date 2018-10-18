#include "arguments.hpp"

namespace CMakeParser::DataStructures
{
//#####################################################################################################################
    int Arguments::tryConsume(std::string_view stream)
    {
        int totalConsumed = 0;
        Argument arg;
        int consumed = arg.tryConsume(stream);
        if (consumed != 0)
        {
            argument = arg;
            stream.remove_prefix(consumed);
            totalConsumed += consumed;
        }
        do
        {
            SeparatedArguments sepArgs;
            consumed = sepArgs.tryConsume(stream);
            if (consumed != 0)
            {
                stream.remove_prefix(consumed);
                seperatedArguments.push_back(sepArgs);
            }
            totalConsumed += consumed;
        } while (consumed != 0);

        return totalConsumed;
    }
//---------------------------------------------------------------------------------------------------------------------
    void Arguments::serialize(std::ostream& out) const
    {
        if (argument)
            argument.value().serialize(out);
        for (auto const& sepArg : seperatedArguments)
        {
            sepArg.serialize(out);
        }
    }
//#####################################################################################################################
    int SeparatedArguments::tryConsume(std::string_view stream)
    {
        if (stream.empty())
            return 0;

        int consumed = 0;
        int totalSepaConsumed = 0;
        do {
            Separation sepa;
            consumed = sepa.tryConsume(stream);
            totalSepaConsumed += consumed;
            separation.push_back(sepa);
            stream.remove_prefix(consumed);
        } while (consumed != 0);

        auto opt1Consumer = [this, &totalSepaConsumed](std::string_view stream) -> int
        {
            if (totalSepaConsumed == 0)
                return 0;

            Argument arg;
            int consumed = arg.tryConsume(stream);
            if (consumed == 0)
                return 0;
            else
            {
                separatedArguments = std::move(arg);
                return consumed;
            }
        };

        auto opt2Consumer = [this, &totalSepaConsumed](std::string_view stream) -> int
        {
            if (stream.size() < 2)
                return 0;

            if (stream.front() != '(')
                return 0;

            stream.remove_prefix(1);

            Arguments args;
            int consumed = args.tryConsume(stream);
            if (consumed == 0)
                return 0;
            stream.remove_prefix(consumed);

            if (stream.empty())
                return 0;
            if (stream.front() != ')')
                return 0;

            separatedArguments = std::move(args);
            return consumed + 2;
        };

        int opt2Consumed = opt2Consumer(stream);
        if (opt2Consumed == 0)
        {
            int opt1Consumed = opt1Consumer(stream);
            if (opt1Consumed == 0)
                return 0;
            else
                return opt1Consumed + totalSepaConsumed;
        }
        else
            return opt2Consumed + totalSepaConsumed;

        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    void SeparatedArguments::serialize(std::ostream& out) const
    {
        for (auto const& sep : separation)
            sep.serialize(out);

        switch (separatedArguments.index())
        {
            case 0:
            {
                auto const& arg = std::get_if<0>(&separatedArguments);
                if (*arg)
                    arg->value().serialize(out);
                break;
            }
            case 1:
            {
                out.put('(');
                std::get_if<1>(&separatedArguments)->serialize(out);
                out.put(')');
                break;
            }
        }
    }
//#####################################################################################################################
}
