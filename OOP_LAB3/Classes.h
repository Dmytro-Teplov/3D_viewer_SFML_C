#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <math.h> 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//float window_size_x = 1000;
//float window_size_y = 600;


class HEX
{
public:
	int red = 0;
	int green = 0;
	int blue = 0;
	void create(int red_num, int green_num, int blue_num);
};
class POINT
{
public:
	float x = 0;
	float y = 0;
	float z = 0;


	sf::Color color;
	float distance(POINT a, POINT b);
	float distance(float x1, float y1,float x2,float y2);
	void middle(POINT a,POINT b);
	void create(float a, float b,float c);
	void clear();
	void draw(sf::RenderWindow& window) const;
	bool operator>(POINT p);
	bool operator<(POINT p);
	void operator=(POINT p);
	//void operator=(const POINT p);
	bool operator==(POINT p);
	POINT operator*(float k);
	bool null();
	friend std::ostream& operator<<(std::ostream& os, POINT p);
	static bool compare_x(POINT p1,POINT p2);
	void rotate(float angle,bool is3d=false);

};
class LINE 
{
public:
	float k;
	float b;

	void create(int k,int b);
	void update(POINT p);
	friend std::ostream& operator<<(std::ostream& os, LINE l);
	bool operator==(LINE l);
};
class PARABOLA 
{
public:
	POINT focus;
	LINE directrix;
	float a = 0, b = 0, c = 0;
	float MAX_X = 1000, MIN_X = 0;

	void create_parabola(LINE directrix, POINT focus);
	void update(LINE directrix);
	friend std::ostream& operator<<(std::ostream& os, PARABOLA& pa);
	float find_y(float x);
	bool operator==(PARABOLA pa);
protected:
	void calculate();
};
class EDGE
{
public:
	POINT p1, p2;
	POINT s1, s2;

	void create(POINT a, POINT b);
	void clear();
	void draw(sf::RenderWindow& window) const;
	friend std::ostream& operator<<(std::ostream& os, EDGE& e);
	void operator=(EDGE e);
};

class TRIANGLE
{

public:
	POINT v1;
	POINT v2;
	POINT v3;
	sf::Color color = sf::Color(100, 100, 100);
	sf::Color border_color = sf::Color(50, 50, 50);
	int border_width = 0;


	void create(POINT v1, POINT v2, POINT v3);
	float center() const;
	void draw(sf::RenderWindow& window) const;
	void draw_3d(sf::RenderWindow& window) const;
	void paint(std::string Col);
	void paint(HEX color);
	void rotate(float angle);
	void operator=(TRIANGLE tris);
	TRIANGLE operator*(float k);
	friend std::ostream& operator<<(std::ostream& os, TRIANGLE t);
	//void operator=(const TRIANGLE tris) const;
};

class OBJECT
{
public:
	
	
	std::vector<TRIANGLE> mesh;
	
	void scale(int percent);
	void draw(sf::RenderWindow& window);
	void renderInHalfs(sf::RenderWindow& window);
	void create(std::vector<TRIANGLE> mesh);
	void operator=(std::vector<TRIANGLE> mesh);
	void operator=(OBJECT obj);
	friend std::ostream& operator<<(std::ostream& os, OBJECT o);
	void rotate(float angle);
};

