#include <testing.hpp>

#include "MainWindow.hpp"
#include "Configuration.hpp"

int main()
{
    Engine::Configuration::Initialize();

    Engine::MainWindow window;
    window.run(60);
}