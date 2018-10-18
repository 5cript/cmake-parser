#include "parser_context.hpp"

#include <fstream>
#include <sstream>

namespace CMakeParser
{
//#####################################################################################################################
    void ParserContext::load(std::string const& fileName)
    {
        std::ifstream reader{fileName, std::ios_base::binary};
        std::stringstream buffer;
        buffer << reader.rdbuf();
        data_ = buffer.str();
        if (!data_.empty() && data_.back() != '\n')
            data_.push_back('\n');
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string const& ParserContext::data()
    {
        return data_;
    }
//#####################################################################################################################
}
