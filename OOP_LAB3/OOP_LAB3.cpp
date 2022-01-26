#include <iostream>
#include "Classes.h"

int main2()
{
    KIRK_POINT v1, v2, v3, v4, v5, v6, v7;
    std::vector <KIRK_POINT> v;
    std::vector <EDGE> e;
    v1.create(130, 50);
    v2.create(50, 200);
    v3.create(120, 250);
    v4.create(100, 150);
    v5.create(100, 300);
    v6.create(80, 350);
    v7.create(140, 400);
   /* v1.create_point(740, 72);
    v2.create_point(947, 200);
    v3.create_point(874, 302);
    v4.create_point(147, 227);
    v5.create_point(848, 507);
    v6.create_point(15, 271);
    v7.create_point(449, 298);*/
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    e = KIRKPATRICK::find_shell(v);


   

    
    
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
    /*sf::CircleShape shape(5.f);
    sf::RectangleShape rectangle(sf::Vector2f(0, 0));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::Blue);
    int posx = 0, posy = 0;
    std::vector<sf::CircleShape> rects;
    posx = 753;
    posy = 110;
    shape.setPosition(posx, posy);
    rects.push_back(shape);
    posx = 270;
    posy = 340;
    shape.setPosition(posx, posy);
    rects.push_back(shape);
    posx = 689;
    posy = 410;
    shape.setPosition(posx, posy);
    rects.push_back(shape);*/


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (const auto& el : v)
            el.draw(window);
        for (const auto& el : e)
            el.draw(window);
        window.display();
    }
   // V_POINT s,s2,s3,m,center;
   // EDGE e;
   // LINE l;
   // PARABOLA pa;
   // std::vector<EDGE> r;
   // std::vector<POINT> p;
   // //l.create_line(0,5);

   // s.create_point(5,7);
   // s2.create_point(3,23);
   // s3.create_point(8,3);

   // //e.create_edge(s,s2);

   // m.middle(s, s2);
   // //p.push_back(s2);
   //// p.push_back(s);
   //// pa.create_parabola(l,s);

   //// r = VORONOI::find_diagram(p);
   // center.set_2_circle_event(s, s2, s3);
   // std::cout << center<<"\n";
   // std::cout << center.circle_event << "\n";
   // std::cout << center.radius << "\n";
    /*V_POINT p1,p2,p3,p4;
    LINE l;
    l.create_line(0,8);
    std::vector<V_POINT> vec;
    std::vector<V_POINT> res;
    p1.create_point(3.72, 21.9);
    p2.create_point(11.3, 16.76);
    p3.create_point(14.08, 18.2);
    p4.create_point(13.34, 21.7);
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);
    vec.push_back(p4);
   res = VORONOI::find_diagram(vec);
    std::cout << l;
    PARABOLA p;
    l.update(p1);
    p1.parabola.create_parabola(l,p1);
    std::cout << p1.parabola << "\n";*/
    

    return 0;
}

