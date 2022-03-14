#include <iostream>
#include "obj_reader.h"
#include <map>
#include <Windows.h>

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






    sf::Texture texture;
    if (!texture.loadFromFile("BackGround.png"))
    {

    }
    sf::Sprite background(texture);

    background.setPosition(-640, -360);

    point origin;
    origin.create(0, 0, 0);
    point l;
    l.create(300, 100, 400);

    HEX violet,violet2;
    violet.create(167, 128,200);
    violet2.create(167, 80,255);

    point v1, v2, v3;
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
    cubee = reading("CUBE2.obj");
    cubee.scale(1.5);
    cubee.paint(violet);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    //void sf::RenderTarget::clear(const Color & color = Color(0, 0, 0, 255));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "3D Viewer", sf::Style::Default, settings);
    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));
    float i = 1;
    window.setView(view);
    bool gour = false;
    bool lit = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        window.draw(background);

        cubee.draw(window,l,lit,false,i,gour);


        window.draw(islit);
        window.draw(islit_text);
        window.draw(gour_text);
        window.draw(gouraud);
        if (GetKeyState('A') & 0x8000)
        {
            i -= 10;
        }
        if (GetKeyState('D') & 0x8000)
        {
            i += 10;
        }
        if (GetKeyState('G') & 0x8000)
        {
            gour = !gour;
            if (gour)
                gouraud.setString("True");
            else
                gouraud.setString("False");
            sf::sleep(sf::milliseconds(100));
        }
        if (GetKeyState('L') & 0x8000)
        {
            lit = !lit;
            if(lit)
                islit.setString("True");
            else
                islit.setString("False");
            sf::sleep(sf::milliseconds(100));

        }

                
        window.display();
    }
    
   
    return 0;
}
