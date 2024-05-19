#pragma once

#include <string>
#include <vector>

namespace MapEditor
{
    struct FilesInfo
    {
        std::string file_name;
        uint16_t type;
    }; 

    struct MapLayerInfo
    {
        std::string layer;
        std::vector<FilesInfo> files;
    };

    struct CoordsInfo
    {
        std::vector<uint16_t> coords;
        uint16_t type;
    };

    class FileReader
    {
    public:
        FileReader(/* args */);
        ~FileReader();

        void process_map_layer_data(const std::string& input_file);
        void read_file(const std::string& file_name);

    private:

        std::vector<std::pair<uint16_t,uint16_t>> m_coords;
    };    
} // namespace MapEditor
