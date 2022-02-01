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
	bool initialized = false;
	float r_angle=0;

	sf::Color color;
	float distance(POINT a, POINT b);
	float distance(float x1, float y1,float x2,float y2);
	void middle(POINT a,POINT b);
	void create(float a, float b, float c = 0);
	void clear();
	
	void draw(sf::RenderWindow& window) const;
	bool operator>(POINT p);
	bool operator<(POINT p);
	void operator=(POINT p);
	//void operator=(const POINT p);
	bool operator==(POINT p);
	POINT operator*(float k);
	POINT operator-(POINT b);
	bool null();
	friend std::ostream& operator<<(std::ostream& os, POINT p);
	static bool compare_x(POINT p1,POINT p2);
	POINT rotate(float angle,bool is3d=false);
	std::vector<float> vector(POINT A);
};
class EDGE
{
public:
	POINT p1, p2;
	POINT s1, s2;
	float thicc=4;

	void create(POINT a, POINT b);
	void create(POINT a, std::vector<float> normalv);
	void create(float x1, float x2, float y1, float y2);
	void clear();
	void draw(sf::RenderWindow& window) ;
	void draw_3d(sf::RenderWindow& window) const;
	void rotate(float angle);
	friend std::ostream& operator<<(std::ostream& os, EDGE& e);
	void operator=(EDGE e);
	
};

class TRIANGLE
{

	
public:
	POINT v1;
	POINT v2;
	POINT v3;
	POINT centroid;
	float r_angle=0;
	std::vector<float> normalv;
	sf::Color color = sf::Color(100, 100, 100);
	sf::Color border_color = sf::Color(50, 50, 50);
	int border_width = 0;

	float center();
	void scale_this(float lambda);
	void create(POINT v1, POINT v2, POINT v3);
	void draw(sf::RenderWindow& window) const;
	void draw_3d(sf::RenderWindow& window, POINT light, bool normal_visible = false, bool islit=false) ;
	void paint(std::string Col);
	void paint(HEX color);
	void lightness(float l);
	TRIANGLE rotate(float angle);
	void operator=(TRIANGLE tris);
	float angle(std::vector<float> vec2);
	POINT center_point();
	TRIANGLE scale(float lambda);
	TRIANGLE operator*(float k);
	friend std::ostream& operator<<(std::ostream& os, TRIANGLE t);
	std::vector<float> normal(bool update= true);
};

class OBJECT
{
public:
	
	
	std::vector<TRIANGLE> mesh;
	std::vector<TRIANGLE> border;
	float r_angle = 0;
	bool sorted = false;

	void scale(float percent);
	void draw(sf::RenderWindow& window, POINT light, float angle ,bool normal_visible = false, bool islit = false);
	void renderInHalfs(sf::RenderWindow& window, POINT light);
	void create_hard_mode(std::vector<TRIANGLE> mesh);
	void operator=(std::vector<TRIANGLE> mesh);
	void operator=(OBJECT obj);
	friend std::ostream& operator<<(std::ostream& os, OBJECT o);
	OBJECT rotate(float angle);
};

