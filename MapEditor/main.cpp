#include <iostream>

#include "FileReader.hpp"
#include "KnightTiles.hpp"

int main()
{
    std::cout<<"Hi"<<std::endl;

    try
    {
        MapEditor::FileReader::process_map_layer_data<Engine::KnightTiles>("InputFiles/map_layer1_data.json");
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
}