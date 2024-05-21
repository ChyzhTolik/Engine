#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using nlohmann::json;


namespace MapEditor
{
    template<typename T>
    struct FilesInfo
    {
        std::string file_name;
        T type;
    }; 

    template<typename T>
    struct MapLayerInfo
    {
        std::string layer_file_name;
        std::vector<FilesInfo<T>> files;
    };

    template<typename T>
    struct CoordsInfo
    {
        std::vector<uint16_t> coords;
        T type;
    };

    class FileReader
    {
    public:
        template<typename T>
        static void process_map_layer_data(const std::string& input_file);

    private:
        static void read_file(const std::string& file_name);
        static std::vector<std::pair<uint16_t,uint16_t>> m_coords;
    };

    template<typename T>
    void to_json(json& j, const FilesInfo<T>& p) 
    {
        j = json
        {
            {"file_name", p.file_name},
            {"type", p.type}
        };
    }

    template<typename T>
    void from_json(const json& j, FilesInfo<T>& p) 
    {
        j.at("file_name").get_to(p.file_name);
        j.at("type").get_to(p.type );
    }

    template<typename T>
    void to_json(json& j, const CoordsInfo<T>& p) 
    {
        j = json
        {
            {"coords", p.coords},
            {"type", p.type}
        };
    }

    template<typename T>
    void from_json(const json& j, CoordsInfo<T>& p) 
    {
        j.at("coords").get_to(p.coords);
        j.at("type").get_to(p.type );
    }

    template<typename T>
    void to_json(json& j, const MapLayerInfo<T>& p) 
    {
        j = json
        {
            {"layer", p.layer_file_name},
            {"files", p.files}
        };
    }

    template<typename T>
    void from_json(const json& j, MapLayerInfo<T>& p) 
    {
        j.at("layer").get_to(p.layer_file_name);
        j.at("files").get_to(p.files );
    }

    template<typename T>
    void FileReader::process_map_layer_data(const std::string& input_file)
    {
        std::fstream map_layer_data_file{input_file};

        if (!map_layer_data_file.good())
        { 
            std::cout << "! Failed loading " << input_file << "." << std::endl; 
            return; 
        }

	    json map_layer_data_json = json::parse(map_layer_data_file);
        MapLayerInfo<T> map_layer_info = map_layer_data_json;

        std::vector<CoordsInfo<T>> coords_infos;
        for (auto &&layer_data : map_layer_info.files)
        {
            read_file(layer_data.file_name);


            for (auto &&coord : m_coords)
            {
                CoordsInfo<T> coords_info;
                coords_info.coords.push_back(coord.first);
                coords_info.coords.push_back(coord.second);
                coords_info.type = layer_data.type;

                coords_infos.push_back(coords_info);
            }
        }

        json jf;

        jf = coords_infos;

        std::string path = "/home/achyzh/Projects/Engine/MapEditor/OutputFiles/" + map_layer_info.layer_file_name;
        std::ofstream file(path);
        file << std::setw(4) << jf << std::endl;;        
    }
} // namespace MapEditor
