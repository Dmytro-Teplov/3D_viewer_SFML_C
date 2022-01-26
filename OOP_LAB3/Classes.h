#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
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
	sf::Color color;

	void middle(POINT a,POINT b);
	void create(float a, float b);
	void clear();
	void draw(sf::RenderWindow& window) const;
	bool operator>(POINT p);
	bool operator<(POINT p);
	void operator=(POINT p);
	bool operator==(POINT p);
	POINT operator*(float k);
	bool null();
	friend std::ostream& operator<<(std::ostream& os, POINT p);
	static bool compare_x(POINT p1,POINT p2);

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
	sf::Color color;
	sf::Color border_color;
	int border_width = 0;


	void create(POINT v1, POINT v2, POINT v3);
	void draw(sf::RenderWindow& window) const;
	void paint(std::string Col);
	void paint(HEX color);
};

class OBJECT
{
public:
	std::vector<TRIANGLE> mesh;
};

class V_POINT : public POINT
{
public:
	float bottom_x = 0;
	float bottom_y = 0;
	float radius = 0;

	bool circle_event = false;

	POINT p1, p2, p3, center_point;
	PARABOLA parabola;

	void set_2_circle_event(V_POINT p1, V_POINT p2, V_POINT p3, bool& change);
	//void update_parabola(PARABOLA p);
	bool point_check(POINT p);
	//void operator==(V_POINT e);
};
class KIRK_POINT : public POINT
{
public:
	bool right = true;
	bool left = true;
};
class VORONOI
{
public:
	static std::vector<V_POINT> find_diagram(std::vector<V_POINT> points);
	static void procced_point(std::vector<V_POINT>& points, std::vector<V_POINT>& BEACH_LINE,std::vector<V_POINT>& CIRCLE_EVENTS, LINE& line);
	static void procced_circle_event(std::vector<V_POINT>& points, std::vector<V_POINT>& BEACH_LINE,std::vector<V_POINT>& CIRCLE_EVENTS, std::vector<V_POINT>& VERTICES, LINE& line);
};
class KIRKPATRICK
{
public:
	static std::vector<EDGE> find_shell(std::vector<KIRK_POINT> points);
	static void sort_by_buckets(std::vector<std::vector<KIRK_POINT>>& bucket, std::vector<KIRK_POINT>& right,
		std::vector<KIRK_POINT>& left);
	static void proceed_l_1(std::deque<float>& slopes, float& relative_slope, EDGE& edge,
		std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i);
	static void proceed_l_2(std::deque<float>& slopes, float& relative_slope, EDGE& edge,
		std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i);
	static void proceed_r_1(std::deque<float>& slopes, float& relative_slope, EDGE& edge,
		std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i);
	static void proceed_r_2(std::deque<float>& slopes, float& relative_slope, EDGE& edge,
		std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i);
};