#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

// Forward Declarations
struct ImGuiDemoWindowData;

static void ShowMyGuiWindow(/*bool *p_open*/);
static void MyGUIWindow();


// Data to be shared across different functions of the demo
struct ImGuiDemoWindowData
{
    bool ShowMainMenubar = false;
};


void ShowMyGuiWindow(/*bool *p_open*/)
{
    // Exceptionally add an extra assert here for people confused about initial Dear ImGui setup
    // Most functions would normally just assert/crash if the context is missing.
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

    // Verify ABI compatibility between caller code and compiled version of Dear ImGui. This helps detects some build issues.
    IMGUI_CHECKVERSION();

    //static ImGuiDemoWindowData demo_data;


    // We specify a default position/size in case there's no data in the .ini file.
    // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 300, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    // Main body of window starts here
    if(!ImGui::Begin("ListBox Demo"))
    {
        // Early out if the window is collapsed, as an optimization
        ImGui::End();
        return;
    }

    ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ImGui::Spacing();

    
    ImGui::End();

}

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
    bool listEnabled = false; 
    //bool p_open = true;

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

        ShowMyGuiWindow(/*&p_open*/);

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
