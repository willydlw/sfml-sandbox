#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

void MyGUIWindow(){
    // store currently selected item
    int currentItem = 0;

    // start drawing the window
    ImGui::Begin("ListBox Window");

    // list of items to display
    const char* items[] = {"Item 1", "Item 2", "Item 3"};
    
    // create list box
    ImGui::ListBox("Select an item\n", &currentItem, items, IM_ARRAYSIZE(items) );

    ImGui::End(); // finish drawing window
}

int main()
{
    bool listEnabled = true; 

    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        return -1;

    sf::Clock clock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        if(listEnabled){
            MyGUIWindow();
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
