#include "FileReader.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace MapEditor
{
    FileReader::FileReader(/* args */)
    {
    }
    
    FileReader::~FileReader()
    {
    }

    void to_json(json& j, const FilesInfo& p) 
    {
        j = json
        {
            {"file_name", p.file_name},
            {"type", p.type}
        };
    }

    void from_json(const json& j, FilesInfo& p) 
    {
        j.at("file_name").get_to(p.file_name);
        j.at("type").get_to(p.type );
    }

    void to_json(json& j, const CoordsInfo& p) 
    {
        j = json
        {
            {"coords", p.coords},
            {"type", p.type}
        };
    }

    void from_json(const json& j, CoordsInfo& p) 
    {
        j.at("coords").get_to(p.coords);
        j.at("type").get_to(p.type );
    }

    void to_json(json& j, const MapLayerInfo& p) 
    {
        j = json
        {
            {"layer", p.layer},
            {"files", p.files}
        };
    }

    void from_json(const json& j, MapLayerInfo& p) 
    {
        j.at("layer").get_to(p.layer);
        j.at("files").get_to(p.files );
    }

    void FileReader::process_map_layer_data(const std::string& input_file)
    {
        std::fstream map_layer_data_file{input_file};

        if (!map_layer_data_file.good())
        { 
            std::cout << "! Failed loading " << input_file << "." << std::endl; 
            return; 
        }

	    json map_layer_data_json = json::parse(map_layer_data_file);
        MapLayerInfo map_layer_info = map_layer_data_json;

        std::vector<CoordsInfo> coords_infos;
        for (auto &&layer_data : map_layer_info.files)
        {
            read_file(layer_data.file_name);


            for (auto &&coord : m_coords)
            {
                CoordsInfo coords_info;
                coords_info.coords.push_back(coord.first);
                coords_info.coords.push_back(coord.second);
                coords_info.type = layer_data.type;

                coords_infos.push_back(coords_info);
            }
        }

        json jf;

        jf = coords_infos;

        std::string path = "/home/achyzh/Projects/Engine/MapEditor/OutputFiles/" + map_layer_info.layer;
        std::ofstream file(path);
        file << std::setw(4) << jf << std::endl;;        
    }

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
