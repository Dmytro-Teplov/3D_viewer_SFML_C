#include <iostream>
#include "obj_reader.h"

int main()
{
    POINT origin;
    origin.create(0, 0, 0);

    HEX violet,violet2;
    violet.create(167, 128,255);
    violet2.create(167, 80,255);
    POINT v1, v2, v3;
    v1.create(100,123,50);

    v2.create(50,-40,30);
    v3.create(-40,10,100);
    TRIANGLE tris1,tris2;
    tris1.create(v1,v2,v3);
    tris2 = tris1;
    tris1.paint(violet);
    tris2.scale(0.5);
    OBJECT cubee;
    cubee.create_hard_mode(reading("jester.obj"));
    cubee.scale(1.5);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

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
        //sf::sleep(sf::milliseconds(10));
        
        
        //cube.draw(window);
        origin.draw(window);
        
        window.display();
    }
    
   
    return 0;
}
