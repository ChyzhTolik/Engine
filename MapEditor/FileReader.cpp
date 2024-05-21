#include "FileReader.hpp"

#include <iostream>
#include <regex>

namespace MapEditor
{
    std::vector<std::pair<uint16_t,uint16_t>> FileReader::m_coords{};

    void FileReader::read_file(const std::string& file_name)
    {
        m_coords.clear();
        std::ifstream file(file_name);

        if (file.fail())
        {
            throw std::runtime_error("Error opening the file");
        }
        else
        {
            // \(\d+,\d+\)
            std::regex reg { "\\d+,\\d+" };

            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string contents = buffer.str();

            auto words_begin = std::sregex_iterator( contents.cbegin(), contents.cend(), reg);
            auto words_end = std::sregex_iterator();

            m_coords.reserve(std::distance(words_begin, words_end));

            for(std::sregex_iterator i = words_begin;
                            i != words_end;
                            ++i )
            {
                const std::string delimiter = ",";
                size_t found = i->str().rfind(delimiter);
                std::cout<<i->str().substr(0,found)<<","<<i->str().substr(found+1,i->str().size())<<std::endl;

                m_coords.push_back({std::stoi(i->str().substr(0,found)),std::stoi(i->str().substr(found+1,i->str().size()))});
            }
	    }

        for (auto &&pair : m_coords)
        {
            std::cout<<pair.first<<";"<<pair.second<<std::endl;
        }        
    }
} // namespace MapEditor
