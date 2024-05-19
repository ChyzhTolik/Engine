#include <iostream>

#include "FileReader.hpp"

int main()
{
    std::cout<<"Hi"<<std::endl;

    MapEditor::FileReader reader;

    try
    {
        // reader.read_file("InputFiles/test_data.txt");
        reader.process_map_layer_data("InputFiles/map_layer1_data.json");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    
}