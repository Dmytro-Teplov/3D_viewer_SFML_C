#include <iostream>
#include "obj_reader.h"
#include <map>
#include <Windows.h>
#include <winuser.h>

int main()
{
    sf::Font font;
    font.loadFromFile("Soothing.ttf");
    sf::Text islit_text,islit,gour_text,gouraud;
    islit_text.setFont(font);
    islit_text.setString("Lit: ");
    islit_text.setCharacterSize(24);
    //islit_text.setFillColor(sf::Color::Red);
    islit_text.setStyle(sf::Text::Bold);
    islit_text.setPosition(-600, 300);

    islit.setFont(font);
    islit.setString("False");
    islit.setCharacterSize(24);
    //islit.setFillColor(sf::Color::Red);
    islit.setStyle(sf::Text::Bold);
    islit.setPosition(-570, 300);

    gour_text.setFont(font);
    gour_text.setString("Gouraud: ");
    gour_text.setCharacterSize(24);
    //gour_text.setFillColor(sf::Color::Red);
    gour_text.setStyle(sf::Text::Bold);
    gour_text.setPosition(-490, 300);

    gouraud.setFont(font);
    gouraud.setString("False");
    gouraud.setCharacterSize(24);
    //gouraud.setFillColor(sf::Color::Red);
    gouraud.setStyle(sf::Text::Bold);
    gouraud.setPosition(-395, 300);



    sf::Mouse mice;
    sf::Keyboard board;


    sf::Texture texture;
    if (!texture.loadFromFile("BackGround.png"))
    {

    }
    sf::Sprite background(texture);

    background.setPosition(-640, -360);

    Point origin;
    origin.create(0, 0, 0);
    Point l;
    l.create(300, 100, 400);

    HEX violet,violet2;
    violet.create(167, 128,200);
    violet2.create(167, 80,255);

    Point v1, v2, v3;
    v1.create(100,123,50);
    v2.create(50,-40,30);
    v3.create(-40,10,100);
    Face tris1,tris2;
    tris1.update(std::vector<Point>({ v1, v2, v3 }));
    tris2 = tris1;
    tris2.scale(0.5);
    Edge e;
    Object cubee = reading("CUBE.obj");
    //cubee.scale(1.5);
    
    cubee.paint(sf::Color(0,0,255));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "3D Viewer", sf::Style::Default, settings);
    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));
    float i = 1;
    window.setView(view);
    bool gour = false;
    bool lit = true;
    bool bord = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (mice.isButtonPressed(sf::Mouse::Left))
            {
                l.x = mice.getPosition(window).x - 640;
                l.y = -(mice.getPosition(window).y - 360);
            }
            
        }
        
        window.clear();
        window.draw(background);
       
        cubee.draw(window,l, sf::Color(120, 255, 20), lit,false,i,gour,bord);

        window.draw(islit);
        window.draw(islit_text);
        window.draw(gour_text);
        window.draw(gouraud);

        if (board.isKeyPressed(sf::Keyboard::A))
        {
            i -= 10;
        }
        if (board.isKeyPressed(sf::Keyboard::D))
        {
            i += 10;
        }
        if (board.isKeyPressed(sf::Keyboard::B))
        {
            bord = !bord;
            
            sf::sleep(sf::milliseconds(200));
        }
        if (board.isKeyPressed(sf::Keyboard::C))
        {
            cubee = cubee.Subdivide(1);
            sf::sleep(sf::milliseconds(200));
        }
        if (board.isKeyPressed(sf::Keyboard::L))
        {
            cubee = cubee.Subdivide(1,"Doo-Sabin");
            sf::sleep(sf::milliseconds(200));
        }
        if (board.isKeyPressed(sf::Keyboard::G))
        {
            gour = !gour;
            if (gour)
                gouraud.setString("True");
            else
                gouraud.setString("False");
            sf::sleep(sf::milliseconds(200));
        }
        /*if (board.isKeyPressed(sf::Keyboard::L))
        {
            lit = !lit;
            if(lit)
                islit.setString("True");
            else
                islit.setString("False");
            sf::sleep(sf::milliseconds(200));

        }*/
        
        
        window.display();
    }
    
    //Point p1(100, 150), p2(121, 110), p3(103, 134);
    //Edge e1(p1, p2), e2(p2, p1), e3(p3, p2);
    //std::vector<Edge> v = {e1,e3,e2,e3};
    //auto it = std::find(v.begin(),v.end(),e2);
    //std::cout << *it;
   
    return 0;
}
