# Let's Animate Santa Claus 

Objective: Learn to work with SFML textures and sprites to animate a game character.


### Santa Claus Images

Thank you to GameArt2D for providing a free download of Santa Claus Sprites under a Creative Common Zero (CC0) a.k.a Public Domain license.

https://www.gameart2d.com/santa-claus-free-sprites.html 




<img src="images/Walk1.png" alt="Santa Walks" style="width:40%; height:auto;">




### Incremental Program Development

When trying something new, my program approach is to add new features, one at a time, and experiment with them to gain a better understanding. The steps below illustrate how I arrived at the final solution.

### Step 1 - SFML Drawing Window

SFML tutorials are very helpful and a great way to get started. We'll start with the [Drawing 2D stuff] (https://www.sfml-dev.org/tutorials/3.0/graphics/draw/ ) tutorial code to render a blank window. This lets us know that we've correctly linked to SFML libraries.


```c++
#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }
}
```


Build and run the program to generate the following output.


<img src="BlankWindow.png" alt="Blank Window" style="width:50%; height:auto;">


### Step 2 - Using Sprites and Textures to Display a Santa Image 

The next tutorial, [Sprites and Textures](https://www.sfml-dev.org/tutorials/3.0/graphics/sprite/) teaches us how to load an image into a texture and then use a sprite to make the texture a drawable element.

In SFML, a texture is an image mapped to a 2D entity. A sprite is a lightweight object that displays a portion of a texture, allowing you to move, rotate, scale, and colorize images on the screen.


**Process** 
- Load an image into an sf::Texture 
- Create an sf::Sprite and associate it with that texture 
- Set the sprite's properties (position, color, etc.)
- Draw the sprite to a render window


```c++
```