#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <map>
#include <string_view>
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
class point
{
public:
	float x = 0;
	float y = 0;
	float z = 0;
	bool initialized = false;
	float r_angle=0;
	std::vector<int> adjacent_tris;
	sf::Color color= sf::Color(127, 127, 127);
	std::vector<float> normalv;
	std::map<int,std::string> tripoints;



	float distance(point a, point b);
	float distance(float x1, float y1,float x2,float y2);
	void middle(point a,point b);
	void create(float a, float b, float c = 0);
	void clear();

	void lightness(float l);
	float angle(std::vector<float> vec2);
	
	void draw(sf::RenderWindow& window) const;
	bool operator>(point p);
	bool operator<(point p);
	void operator=(point p);
	//void operator=(const point p);
	bool operator==(point p);
	point operator*(float k);
	point operator-(point b);
	bool null();
	friend std::ostream& operator<<(std::ostream& os, point p);
	static bool compare_x(point p1,point p2);
	point rotate(float angle,bool is3d=false);
	std::vector<float> vector(point A);
	void Gouraud(point& v1, std::vector<float>normalv , point light);
};
class EDGE
{
public:
	point p1, p2;
	point s1, s2;
	float thicc=4;

	void create(point a, point b);
	void create(point a, std::vector<float> normalv);
	void create(float x1, float x2, float y1, float y2);
	void clear();
	void draw(sf::RenderWindow& window) ;
	void draw_3d(sf::RenderWindow& window) const;
	void rotate(float angle);
	friend std::ostream& operator<<(std::ostream& os, EDGE& e);
	void operator=(EDGE e);
	EDGE operator*(float k);
	
};

class TRIANGLE
{

	
public:
	point v1;
	point v2;
	point v3;
	point centroid;
	float r_angle=0;
	std::vector<float> normalv;
	sf::Color color = sf::Color(100, 100, 100);
	sf::Color border_color = sf::Color(50, 50, 50);
	int border_width = 0;

	float center();
	void scale_this(float lambda);
	void create(point v1, point v2, point v3);
	void create(point& v1, point& v2, point& v3, int tris_index);
	void draw(sf::RenderWindow& window) const;
	void draw_3d(sf::RenderWindow& window, point light, bool islit=false, bool gouraud = true);
	void paint(std::string Col);
	void paint(HEX color);
	
	TRIANGLE rotate(float angle);
	void operator=(TRIANGLE tris);
	void lightness(float l);
	float angle(std::vector<float> vec2);
	point center_point();
	TRIANGLE scale(float lambda);
	TRIANGLE operator*(float k);
	friend std::ostream& operator<<(std::ostream& os, TRIANGLE t);
	std::vector<float> normal(bool update= true);
};

class OBJECT
{
public:
	std::vector<TRIANGLE> mesh;
	std::vector<point> points;
	std::vector<std::vector<float>> vertex_normals;
	std::vector<EDGE> vertex_normals_vis;
	std::vector<TRIANGLE> border;
	sf::Color color = sf::Color(100, 100, 100);
	float r_angle = 0;
	bool sorted = false;


	void scale(float percent);
	void draw(sf::RenderWindow& window, point light, bool islit = false, bool normal_visible = false, float angle = 0,  bool gouraud = true);
	void renderInHalfs(sf::RenderWindow& window, point light);
	void create_hard_mode(std::vector<TRIANGLE> mesh);
	void create(std::vector<TRIANGLE> mesh, std::vector<point> points);
	void paint(HEX color);
	void operator=(std::vector<TRIANGLE> mesh);
	void operator=(OBJECT obj);
	friend std::ostream& operator<<(std::ostream& os, OBJECT o);
	OBJECT rotate(float angle);
};

