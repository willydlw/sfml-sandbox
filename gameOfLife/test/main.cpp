#include "neighborTest.hpp"

#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <filesystem>

int main(void)
{
    std::string fontFile{"arial.ttf"};

    sf::Font font;
    if(!font.openFromFile(fontFile))
    {
        std::cerr << "[FATAL] failure to open font file: " << fontFile << "\n";
        std::cerr << "Current working directory: " << std::filesystem::current_path() << "\n";
        return 1;
    }
    neighborTest::runTests();
    return 0;
}