#include <iostream>
#include "obj_reader.h"

int main()
{
    POINT origin;
    origin.create(0, 0, 0);
    POINT l;
    l.create(300, 300, 0);

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
    e.create(tris1.center_point(),tris1.normal());
    OBJECT cubee;
    cubee = reading("jester.obj");
    //cubee.create_hard_mode(reading("xanadu.obj"));
    cubee.scale(2);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));
    float i = 1;
    cubee.rotate(100);
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
        cubee.draw(window,l);
        cubee.rotate(5);
        
       // tris1.draw_3d(window,true);
        //sf::sleep(sf::milliseconds(20));
        
        //tris1.draw_3d(window,true);
        //tris1.lightness(1);
        //tris1.rotate(5);
        
        //tris1.center_point().draw(window);
        //e.draw_3d(window);
        //e.rotate(1);
        //cube.draw(window);
        origin.draw(window);
        
        window.display();
    }
    
   
    return 0;
}
