#include <iostream>
#include "Classes.h"

int main()
{
    POINT origin;
    origin.create(0, 0, 0);
    HEX violet,violet2;
    violet.create(167, 128,255);
    violet2.create(167, 80,255);

    POINT p1, p2, p3, p4, p5, p6, p7, p8;
    p1.create(100,-100,-100);
    p2.create(-100,-100,-100);
    p3.create(-100,100,-100);
    p4.create(100,100,-100);
    p5.create(-100,-100,100);
    p6.create(100,100,100);
    p7.create(-100,100,100);
    p8.create(100,-100,100);

    
    TRIANGLE t1,t2,t3,t4,t5,t6;
    t1.create(p1,p2,p4);
    t2.create(p4,p2,p3);
    t3.create(p5,p2,p3);
    t4.create(p6,p1,p4);
    t5.create(p7,p5,p3);
    t6.create(p8,p6,p1);

    t1.paint(violet);
    t2.paint(violet2);
    t3.paint(violet);
    t4.paint(violet2);
    t5.paint(violet2);
    t6.paint(violet);

    OBJECT cube;
    std::vector<TRIANGLE> mesh = {t1,t2,t3,t4,t5,t6};
    cube = mesh;
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

       
        
        //cube.draw(window);

        origin.draw(window);
        
        window.display();
    }
    
   
    return 0;
}
