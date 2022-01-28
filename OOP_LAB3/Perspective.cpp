#include <iostream>
#include "obj_reader.h"

int main()
{
    POINT origin;
    origin.create(0, 0, 0);

    HEX violet,violet2;
    violet.create(167, 128,255);
    violet2.create(167, 80,255);

    OBJECT cubee;

    cubee=reading("jester.obj");

    //std::cout << cubee;
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
        
        /*p.draw(window);
        p.rotate(10,true);*/
        cubee.draw(window);
        cubee.rotate(5);
        //sf::sleep(sf::milliseconds(20));
       
        
        //cube.draw(window);
        origin.draw(window);
        
        window.display();
    }
    
   
    return 0;
}
