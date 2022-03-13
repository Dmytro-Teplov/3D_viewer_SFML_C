#include <iostream>
#include "obj_reader.h"
#include <map>

int main()
{
    POINT origin;
    origin.create(0, 0, 0);
    POINT l;
    l.create(300, 100, 400);

    HEX violet,violet2;
    violet.create(167, 128,200);
    violet2.create(167, 80,255);

    POINT v1, v2, v3;
    v1.create(100,123,50);
    v2.create(50,-40,30);
    v3.create(-40,10,100);
    TRIANGLE tris1,tris2;
    tris1.create(v1,v2,v3);
    tris2 = tris1;
   // tris1.paint(violet);
    tris2.scale(0.5);
    EDGE e;
    //e.create(tris1.center_point(),tris1.normal());
    OBJECT cubee;
    cubee = reading("jester.obj");
    cubee.scale(1.5);
    cubee.paint(violet);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "3D Viewer", sf::Style::Default, settings);
    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));
    float i = 1;
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
        
        cubee.draw(window,l,true,false,i,false);
        
        i-=1;
                
        window.display();
    }
    
   
    return 0;
}
