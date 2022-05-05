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

class HEX
{
public:
	int red = 0;
	int green = 0;
	int blue = 0;
	void create(int red_num, int green_num, int blue_num);
};
class Point
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
	
	Point()
	{}
	Point(float x,float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
		this->initialized = true;
	}

	static float distance(Point a, Point b);
	float distance(float x1, float y1,float x2,float y2);
	void middle(Point a,Point b);
	void create(float a, float b, float c = 0);
	void clear();

	void lightness(float l);
	float angle(std::vector<float> vec2);
	
	void draw(sf::RenderWindow& window) const;
	bool operator>(Point p);
	bool operator<(Point p);
	void operator=(Point p);
	bool operator==(Point const& p) const;
	Point operator*(float k);
	Point operator-(Point b);
	Point operator+(Point b);
	Point operator/(float b);
	bool null();
	friend std::ostream& operator<<(std::ostream& os, Point p);
	static bool compare_x(Point p1,Point p2);
	Point rotate(float angle,bool is3d=false);
	std::vector<float> vector(Point A);
	void Gouraud(Point& v1, std::vector<float>normalv , Point light);
};
class Edge
{
public:
	Point p1, p2;
	
	std::vector<int> adjacentFaces;

	float thicc=4;
	sf::Color color = sf::Color(50, 50, 50);

	Edge(){}

	Edge(Point a,Point b)
	{
		this->p1 = a;
		this->p2 = b;
	}

	void create(Point a, Point b);
	void create(Point* a, Point* b);
	void create(Point a, std::vector<float> normalv);
	void create(float x1, float x2, float y1, float y2);
	void clear();
	void draw(sf::RenderWindow& window) ;
	void draw_3d(sf::RenderWindow& window) const;
	void rotate(float angle);
	friend std::ostream& operator<<(std::ostream& os, Edge& e);
	void operator=(Edge e);
	bool operator==(Edge const& e) const;
	Edge operator*(float k);
	
};

class Face
{
public:
	std::vector<Point> v = { Point(),Point(),Point() };
	int n = 1;
	Point centroid;
	bool border = false;
	float r_angle=0;
	std::vector<float> normalv;

	std::vector<Edge> borders;

	sf::Color color = sf::Color(100, 100, 100);
	sf::Color border_color = sf::Color(50, 50, 50);
	int border_width = 0;

	float center();
	void scale_this(float lambda);
	//void create(Point v1, Point v2, Point v3);
	//void create(Point v1, Point v2, Point v3, Point v4);
	void update(Point v1, Point v2, Point v3);
	void update(Point v1, Point v2, Point v3, Point v4);
	void create(Point& v1, Point& v2, Point& v3, int tris_index);
	void create(Point& v1, Point& v2, Point& v3, Point& v4, int tris_index);
	void draw(sf::RenderWindow& window) const;
	void draw_3d(sf::RenderWindow& window, Point light, bool islit=false, bool gouraud = true, bool border = false);
	void paint(std::string Col);
	void paint(HEX color);
	void change_position(float x, float y);

	Face rotate(float angle);
	void operator=(Face tris);
	bool operator==(Face tris);
	bool operator!=(Face tris);
	void lightness(float l);
	float angle(std::vector<float> vec2);
	Point center_point();
	Face scale(float lambda);
	Face operator*(float k);
	
	
	friend std::ostream& operator<<(std::ostream& os, Face t);
	std::vector<float> normal(bool update= true);
};

class Object
{
public:
	
	Point center;

	std::vector<Face> mesh;
	
	std::vector<Edge> border;

	std::vector<Point> points;

	std::vector<std::vector<float>> vertex_normals;
	std::vector<Edge> vertex_normals_vis;
	sf::Color color = sf::Color(100, 100, 100);
	float r_angle = 0;
	bool sorted = false;

	
	

	void scale(float percent);
	void draw(sf::RenderWindow& window, Point light, sf::Color = sf::Color(100, 100, 100), bool islit = false, bool normal_visible = false, float angle = 0,  bool gouraud = true,bool border =false);
	

	
	void create(std::vector<Face> mesh, std::vector<Point> points);
	void operator=(std::vector<Face> mesh);

	void paint(std::string Col);
	void paint(HEX color);
	void operator=(Object obj);
	friend std::ostream& operator<<(std::ostream& os, Object o);
	Object rotate(float angle);

	Object Subdivide(int i,std::string subd_type="Catmull-Clark");
private:
	void calculate_center();
	Point calculateEdgePoint(Edge e);
	Point calculateFacePoint(Edge e,Face f);
	Point updateVertex(Point vertex);
};

