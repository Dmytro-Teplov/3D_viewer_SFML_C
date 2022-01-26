#include <iostream>
#include "Classes.h"

int main()
{

    HEX violet;
    violet.create(167, 128,255);
    POINT pointy;
    pointy.create(200, 120);
    POINT pointy2 = pointy * 0.5;
    pointy2.x += 100;
    POINT pointy3 = pointy * 0.2;
    TRIANGLE tris;
    tris.create(pointy,pointy2,pointy3);
    tris.paint(violet);
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");

    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));
    window.setView(view);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        /*pointy.draw(window);
        pointy2.draw(window);
        pointy3.draw(window);*/
        tris.draw(window);
        /*for (const auto& el : v)
            el.draw(window);
        for (const auto& el : e)
            el.draw(window);*/
        window.display();
    }
    
   
    return 0;
}
