#include "particle.hpp"

#include <SFML/Graphics.hpp>

#include <optional>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800



int main(void)
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Euler Integration");
    window.setFramerateLimit(30);

    #if 0
    Particle particle[2];
    particle[0] = Particle(350, 300, 0, 50, 1.0);
    particle[1] = Particle(450, 300, 0, 50, 1.0);
    #endif 

    ver::Particle p (ver::Vector2D<float>(450, 300), ver::Vector2D<float>(0, 50), 1.0);
    ver::Vector2D<float> forces(0.0f, 300.0f);

    while(window.isOpen()){
        // check all window events triggered since last loop iteration
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

            window.clear(sf::Color::Black);
            #if 0
            for(auto p : particle){
                p.update(0.1f, 0.0f, 300.0f);
                std::cerr << p;
                p.draw(window);
            }
            #endif 

            
            p.update(forces, 0.1);
            p.draw(window);
            window.display();
        
    }

    return 0;
}
