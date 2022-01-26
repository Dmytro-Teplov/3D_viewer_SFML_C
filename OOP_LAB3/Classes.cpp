#include "Classes.h"

void HEX::create(int red_num, int green_num, int blue_num)
{
	this->red = red_num;
	this->green = green_num;
	this->blue = blue_num;
}


void POINT::middle(POINT a, POINT b)
{
	this->x = (a.x + b.x) / 2;
	this->y = (a.y + b.y) / 2;
}
void POINT::create(float a, float b)
{
	this->x = a;
	this->y = b;
}
void POINT::clear()
{
	this->x = 0;
	this->y = 0;
}
void POINT::draw(sf::RenderWindow& window) const
{
	std::string s;//=  + std::to_string((int)this->y);
	s.push_back('[');
	s += std::to_string((int)this->x);
	s.push_back(',');
	s += std::to_string((int)this->y);
	s.push_back(']');
	sf::CircleShape shape(2.f);
	sf::Text text;
	sf::Font font;
	sf::String s1;
	font.loadFromFile("3974.ttf");
	text.setFont(font);
	text.setCharacterSize(10);
	text.setString(s);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setFillColor(sf::Color::Red);
	text.setPosition(this->x-2 , this->y);
	shape.setPosition(this->x-2,this->y-2);
	shape.setFillColor(sf::Color::White);
	window.draw(text);
	window.draw(shape);
	
}
bool POINT::operator>(POINT d)
{
	return this->y > d.y;
}
bool POINT::operator<(POINT d)
{
	return this->y < d.y;
}
void POINT::operator=(POINT d)
{
	this->x = d.x;
	this->y = d.y;

}
bool POINT::operator==(POINT p)
{
	return this->x==p.x&& this->y == p.y;
}
POINT POINT::operator*(float k)
{
	POINT newP;
	newP.create(this->x * k, this->y * k);
	return newP;
}
bool POINT::null()
{
	return this->x == 0&& this->y == 0;
}
bool POINT::compare_x(POINT p1,POINT p2)
{
	return p1.x<p2.x;
}

void EDGE::create(POINT a, POINT b)
{
	this->p1=a;
	this->p2=b;
}
void EDGE::clear()
{
	this->p1.clear();
	this->p2.clear();
}
void EDGE::draw(sf::RenderWindow& window) const
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(this->p1.x, this->p1.y)),
		sf::Vertex(sf::Vector2f(this->p2.x, this->p2.y))
	};
	window.draw(line, 2, sf::Lines);
}
void EDGE::operator=(EDGE e)
{
	this->p1 = e.p1;
	this->p2 = e.p2; 
	this->s1 = e.s1;
	this->s2 = e.s2;
}

void TRIANGLE::draw(sf::RenderWindow& window) const
{
	sf::ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(this->v1.x, this->v1.y));
	convex.setPoint(1, sf::Vector2f(this->v2.x, this->v2.y));
	convex.setPoint(2, sf::Vector2f(this->v3.x, this->v3.y));

	convex.setOutlineThickness(this->border_width);
	convex.setOutlineColor(this->border_color);
	convex.setFillColor(this->color);
	window.draw(convex);
	
}
void TRIANGLE::create(POINT v1, POINT v2, POINT v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
}
void TRIANGLE::paint(std::string Col)
{
	if (Col == "Red") 
	{
		this->color = sf::Color::Red;
		std::cout << "Red";
	}
	if (Col == "Green")
	{
		this->color = sf::Color::Green;
	}
	if (Col == "Blue")
	{
		this->color = sf::Color::Blue;
	}
	if (Col == "Black")
	{
		this->color = sf::Color::Black;
	}
	if (Col == "White")
	{
		this->color = sf::Color::White;
	}

}

void TRIANGLE::paint(HEX color)
{
	this->color = sf::Color(color.red, color.green, color.blue);
}

std::ostream& operator<<(std::ostream& os, POINT p)
{
	os << "(" << p.x << "," << p.y<<")";
	return os;
}
std::ostream& operator<<(std::ostream& os, EDGE& e)
{
	os << "[" << e.p1 << "," << e.p2 << "]\n";
	return os;
}
std::ostream& operator<<(std::ostream& os, LINE l)
{
	if(l.k)
		os << "y=" << l.k << "x+" << l.b;
	else
		os << "y=" << l.b;
	return os;
}
std::ostream& operator<<(std::ostream& os, PARABOLA& pa)
{
	if (pa.a == 0 && pa.b == 0 && pa.c == 0)
	{
		pa.calculate();
	}
	os << "y=" << pa.a << "(x-(" << pa.b << "))^2 + ("<< pa.c <<")";
	return os;
}

void PARABOLA::create_parabola(LINE directrix, POINT focus)
{
	this->directrix = directrix;
	this->focus = focus;
}
void PARABOLA::update(LINE directrix)
{
	this->directrix = directrix;
}
bool PARABOLA::operator==(PARABOLA pa)
{
	bool b1 = pa.focus == this->focus;
	bool b2 = pa.directrix == this->directrix;
	bool b3 = pa.MAX_X == this->MAX_X;
	bool b4 = pa.MIN_X == this->MIN_X;
	return b1 && b2 && b3 && b4;
}
void PARABOLA::calculate()
{
	this->a = (float)1 / (2 * (this->focus.y - this->directrix.b));
	this->b = (float)this->focus.x;
	this->c = 0.5 * (this->focus.y + this->directrix.b);
}
float PARABOLA::find_y(float x)
{
	if (this->a == 0 && this->b == 0 && this->c == 0)
	{
		this->a = (float)1 / (2 * (this->focus.y - this->directrix.b));
		this->b = (float)this->focus.x;
		this->c = 0.5 * (this->focus.y + this->directrix.b);
	}
	return this->a * (x - this->b) * (x - this->b) + this->c;
}

void LINE::create(int k, int b)
{
	this->k = k;
	this->b = b;
}
void LINE::update(POINT p)
{
	if(this->b==0)
		this->k = p.y;
}
bool LINE::operator==(LINE l)
{
	return l.b==this->b&&l.k==this->k;
}

std::vector<V_POINT> VORONOI::find_diagram(std::vector<V_POINT> points)
{
	std::vector<V_POINT> BEACH_POINTS;
	//std::vector<PARABOLA> BEACH_LINE;
	std::vector<V_POINT> CIRCLE_EVENTS;
	std::vector<V_POINT> VERTICES;
	LINE SWEEP_LINE;
	V_POINT curr;
	V_POINT mid;
	V_POINT curr_vertex;
	bool change;
	SWEEP_LINE.create(0,0);
	std::sort(points.begin(), points.end());
	while (!points.empty() || !CIRCLE_EVENTS.empty())
	{
		if (!CIRCLE_EVENTS.empty()) 
		{
			if (points.empty()) 
			{

				procced_circle_event(points, BEACH_POINTS, CIRCLE_EVENTS, VERTICES, SWEEP_LINE);
			}
			else 
			{
				if (points.front().y < CIRCLE_EVENTS.front().bottom_y)
				{
					procced_point(points, BEACH_POINTS, CIRCLE_EVENTS, SWEEP_LINE);
				}
				else
				{
					procced_circle_event(points, BEACH_POINTS, CIRCLE_EVENTS, VERTICES, SWEEP_LINE);
				}
			}
			
		}
		else
		{
			procced_point(points, BEACH_POINTS, CIRCLE_EVENTS, SWEEP_LINE);
		}
		/*while (CIRCLE_EVENTS.empty()) {
			curr = points.front();
			points.erase(points.begin());
			if (BEACH_POINTS.size() >= 2)
			{
				for (int i = 0; i < BEACH_POINTS.size(); i++)
				{
					for (int j = 0; j < BEACH_POINTS.size(); j++)
					{
						curr_vertex.set_2_circle_event(curr, BEACH_POINTS[i], BEACH_POINTS[j], change);
						if (change)
						{
							CIRCLE_EVENTS.push_back(curr_vertex);
						}
					}
				}

			}
			BEACH_POINTS.push_back(curr);
			std::sort(CIRCLE_EVENTS.begin(), CIRCLE_EVENTS.end());
		}
		if (!points.empty())
		{
			if (points.front().y < CIRCLE_EVENTS.front().bottom_y)
			{
				curr = points.front();
				points.erase(points.begin());
				for (int i = 0; i < BEACH_POINTS.size(); i++)
				{

				}
				if (BEACH_POINTS.size() > 2)
				{
					for (int i = 0; i < BEACH_POINTS.size(); i++)
					{
						for (int j = 0; j < BEACH_POINTS.size(); j++)
						{
							curr_vertex.set_2_circle_event(curr, BEACH_POINTS[i], BEACH_POINTS[j], change);
							if (change)
							{
								CIRCLE_EVENTS.push_back(curr_vertex);
							}
						}
					}
					BEACH_POINTS.push_back(curr);
					std::sort(CIRCLE_EVENTS.begin(), CIRCLE_EVENTS.end());
				}
			}
		}

		curr = CIRCLE_EVENTS.front();
		CIRCLE_EVENTS.erase(CIRCLE_EVENTS.begin());
		mid.middle(curr.p1, curr.p3);
		VERTICES.push_back(curr);
	}*/

	}
	return VERTICES;
}

void VORONOI::procced_point(std::vector<V_POINT>& points, std::vector<V_POINT>& BEACH_POINTS, std::vector<V_POINT>& CIRCLE_EVENTS, LINE& line)
{
	V_POINT curr;
	V_POINT curr_vertex;
	bool change;
	curr = points.front();
	points.erase(points.begin());
	line.update(curr);
	if (BEACH_POINTS.size() >= 2)
	{
		//CIRCLE_EVENTS.clear();
		for (int i = 0; i < BEACH_POINTS.size(); i++)
		{
			for (int j = 0; j < BEACH_POINTS.size(); j++)
			{
				curr_vertex.set_2_circle_event(curr, BEACH_POINTS[i], BEACH_POINTS[j], change);
				if (change)
				{
					CIRCLE_EVENTS.push_back(curr_vertex);
					std::sort(CIRCLE_EVENTS.begin(), CIRCLE_EVENTS.end());
				}
			}
		}
	}
	curr.parabola.create_parabola(line,curr);
	BEACH_POINTS.push_back(curr);
}
void VORONOI::procced_circle_event(std::vector<V_POINT>& points, std::vector<V_POINT>& BEACH_POINTS, std::vector<V_POINT>& CIRCLE_EVENTS, std::vector<V_POINT>& VERTICES, LINE& line)
{
	V_POINT curr;
	V_POINT curr_vertex;
	bool change;
	curr = CIRCLE_EVENTS.front();
	CIRCLE_EVENTS.erase(CIRCLE_EVENTS.begin());
	//mid.middle(curr.p1, curr.p3);
	if ((curr.p2.y < curr.p1.y && curr.p2.y < curr.p3.y))
	{
		BEACH_POINTS.erase(std::remove(BEACH_POINTS.begin(), BEACH_POINTS.end(), curr.p2), BEACH_POINTS.end());
	}
	VERTICES.push_back(curr);
}

void V_POINT::set_2_circle_event(V_POINT p1, V_POINT p2, V_POINT p3, bool& change)
{
	if( !((this->p1 == p1 || this->p2 == p1 || this->p3 == p1)
		&& (this->p1 == p2 || this->p2 == p2 || this->p3 == p2)
		&& (this->p1 == p3 || this->p2 == p3 || this->p3 == p3))
		&&!((p1==p2) || (p2 == p3) || (p1 == p3)))
	{
		std::vector<V_POINT> p;
		p.push_back(p1);
		p.push_back(p2);
		p.push_back(p3);
		if (p[1].x < p[0].x)
			std::swap(p[0], p[1]);
		if (p[2] < p[1])
		{
			std::swap(p[1], p[2]);
			if (p[1].x < p[0].x)
				std::swap(p[1], p[0]);
		}

		this->p1 = p[0];
		this->p2 = p[1];
		this->p3 = p[2];

		this->circle_event = true;
		float bx = p1.x; float by = p1.y;
		float cx = p2.x; float cy = p2.y;
		float dx = p3.x; float dy = p3.y;
		float temp = cx * cx + cy * cy;
		float bc = (bx * bx + by * by - temp) / 2.0;
		float cd = (temp - dx * dx - dy * dy) / 2.0;
		float det = (bx - cx) * (cy - dy) - (cx - dx) * (by - cy);
		det = 1 / det;
		this->x = (bc * (cy - dy) - cd * (by - cy)) * det;
		this->y = ((bx - cx) * cd - (cx - dx) * bc) * det;
		cx = this->x;
		cy = this->y;
		this->radius = std::sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by));
		this->bottom_x = this->x;
		this->bottom_y = this->y - this->radius;
		this->center_point.create(cx, cy);
		change = true;
	}
	else
	{
		change = false;
	}
}
bool V_POINT::point_check(POINT p)
{
	if (this->p1 == p)
		return true;
	else if (this->p2 == p)
		return true;
	else if (this->p3 == p)
		return true;
	else
		return false;
}

std::vector<EDGE> KIRKPATRICK::find_shell(std::vector<KIRK_POINT> points)
{
	std::sort(points.begin(), points.end());
	std::vector<std::vector<KIRK_POINT>> bucket((int)points.back().y+1);
	std::vector<EDGE> shell_left;
	std::vector<EDGE> shell_right;
	std::sort(points.begin(), points.end(), POINT::compare_x);
	points.back().right = false;
	points.back().left = true;
	points.front().left = false;
	points.front().right = true;
	std::vector<KIRK_POINT> right;
	std::vector<KIRK_POINT> left;
	KIRK_POINT right_p = points.back();
	KIRK_POINT left_p= points.front();
	
	for (auto el : points)
	{
		bucket[(int)el.y].push_back(el);
	}
	sort_by_buckets(bucket,right,left);
	
	
	EDGE edge;
	EDGE curr;
	EDGE last_edge;
	int which = 1;
	float relative_slope;
	//float objective_slope;
	std::deque<float> slopes;
	edge.p1 = left[0];
	for (int i = 1; i < left.size(); i++)
	{		
		relative_slope=( left[i-1].y- left[i].y)/(left[i-1].x-left[i].x);
		if (relative_slope > 0)
		{
			if (!which) {
				proceed_l_2(slopes, relative_slope, edge,
					left, shell_left, i);
				//which = 1;
				which = (slopes.back() > 0) ? 1 : 0;
				/*if (i + 1 < left.size())
				{
					float next_slope = (float)(left[i+1].y- left[i].y) / (left[i + 1].x - left[i].x);
					
				}*/
			}
			else {
				proceed_l_1(slopes, relative_slope, edge,
					left, shell_left, i);
			}
		}
		else 
		{
			if (which)
			{
				proceed_l_2(slopes, relative_slope, edge,
					left, shell_left, i);
				which = 0;
			}
			else
			{
				proceed_l_1(slopes, relative_slope, edge,
					left, shell_left, i);
			}
		}
	}
	last_edge.p1 = shell_left.back().p2;
	edge.p1 = right[0];
	for (int i = 1; i < right.size(); i++)
	{
		relative_slope = (right[i - 1].y - right[i].y) / (right[i - 1].x - right[i].x);
		if (relative_slope < 0)
		{
			if (!which) {
				proceed_r_2(slopes, relative_slope, edge,
					right, shell_right, i);
				which = (slopes.back() < 0) ? 1 : 0;
			}
			else {
				proceed_r_1(slopes, relative_slope, edge,
					right, shell_right, i);
			}
		}
		else
		{
			if (which)
			{
				proceed_r_2(slopes, relative_slope, edge,
					right, shell_right, i);
				which = 0;
			}
			else
			{
				proceed_r_1(slopes, relative_slope, edge,
					right, shell_right, i);
			}
		}
	}
	last_edge.p2 = shell_right.back().p2;
	shell_right.push_back(last_edge);
	shell_right.insert(shell_right.end(),shell_left.begin(), shell_left.end());
	std::cout << "\n";
	for (int i = 0; i < shell_right.size(); i++)
	{
		std::cout << shell_right[i] << "\n";
	}

	return shell_right;
}

void KIRKPATRICK::sort_by_buckets(std::vector<std::vector<KIRK_POINT>>& bucket,std::vector<KIRK_POINT>& right,
	std::vector<KIRK_POINT>& left)
{
	for (int i = 0; i < bucket.size(); i++)
	{
		if (bucket[i].size() >= 2)
		{
			std::sort(bucket[i].begin(), bucket[i].end(), POINT::compare_x);
			bucket[i].front().right = false;
			bucket[i].front().left = true;
			bucket[i].back().left = false;
			bucket[i].back().right = true;
		}
		
	}
	for (auto el : bucket)
	{
		for (auto el2 : el)
		{
			if (el2.right)
				right.push_back(el2);
			if (el2.left)
				left.push_back(el2);
		}
	}
}

void KIRKPATRICK::proceed_l_1(std::deque<float> &slopes, float &relative_slope,EDGE &edge,
	std::vector<KIRK_POINT> &left, std::vector<EDGE> &shell,int i)
{
	EDGE curr;
	if (!slopes.empty() && (!shell.empty()))
	{
		if (slopes.back() <= relative_slope)
		{
			edge.p2 = left[i];
			shell.push_back(edge);
			edge.clear();
			edge.p1 = left[i];
			slopes.push_back(relative_slope);
		}
		else
		{
			
			while ((!slopes.empty()) && slopes.back() > relative_slope&&((relative_slope>0&& slopes.back()>0)|| (relative_slope < 0 && slopes.back() < 0)))//&& slopes.back() < 0 && relative_slope < 0)
			{
				slopes.pop_back();
				curr = shell.back();
				shell.pop_back();
				curr.p2 = left[i];
				relative_slope = (curr.p1.y - curr.p2.y) / (curr.p1.x - curr.p2.x);
			}
			slopes.push_back(relative_slope);
			shell.push_back(curr);
			edge.p1 = curr.p2;		
		}
		
	}
	else
	{
		edge.p2 = left[i];
		shell.push_back(edge);
		edge.clear();
		edge.p1 = left[i];
		slopes.push_back(relative_slope);
	}
}

void KIRKPATRICK::proceed_l_2(std::deque<float>& slopes, float& relative_slope, EDGE& edge, 
	std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i)
{
	EDGE curr;
	if (!slopes.empty() && (!shell.empty()))
	{
		if (slopes.back() > 0&& relative_slope<0)
		{
			edge.p2 = left[i];
			shell.push_back(edge);
			edge.clear();
			edge.p1 = left[i];
			slopes.push_back(relative_slope);
		}
		if(slopes.back() < 0 && relative_slope > 0)
		{
			while ((!slopes.empty()) && slopes.back() < 0)
			{
				slopes.pop_back();
				curr = shell.back();
				shell.pop_back();
				curr.p2 = left[i];
				relative_slope = (curr.p1.y - curr.p2.y) / (curr.p1.x - curr.p2.x);
			}
			if ((!slopes.empty()) && slopes.back() > relative_slope)
			{
				while ((!slopes.empty()) && slopes.back() > relative_slope&&relative_slope > 0)//&& slopes.back() < 0 && relative_slope < 0)
				{
					slopes.pop_back();
					curr = shell.back();
					shell.pop_back();
					curr.p2 = left[i];
					relative_slope = (curr.p1.y - curr.p2.y) / (curr.p1.x - curr.p2.x);
				}
			}
			slopes.push_back(relative_slope);
			shell.push_back(curr);
			edge.p1 = curr.p2;
		}
	}
	else
	{
		edge.p2 = left[i];
		shell.push_back(edge);
		edge.clear();
		edge.p1 = left[i];
		slopes.push_back(relative_slope);
	}
}

void KIRKPATRICK::proceed_r_1(std::deque<float>& slopes, float& relative_slope, EDGE& edge, std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i)
{
	EDGE curr;
	if (!slopes.empty() && (!shell.empty()))
	{
		if (slopes.back() >= relative_slope)
		{
			edge.p2 = left[i];
			shell.push_back(edge);
			edge.clear();
			edge.p1 = left[i];
			slopes.push_back(relative_slope);
		}
		else
		{

			while ((!slopes.empty()) && slopes.back() < relative_slope && ((relative_slope > 0 && slopes.back() > 0) || (relative_slope < 0 && slopes.back() < 0)))//&& slopes.back() < 0 && relative_slope < 0)
			{
				slopes.pop_back();
				curr = shell.back();
				shell.pop_back();
				curr.p2 = left[i];
				relative_slope = (curr.p1.y - curr.p2.y) / (curr.p1.x - curr.p2.x);
			}
			slopes.push_back(relative_slope);
			shell.push_back(curr);
			edge.p1 = curr.p2;
		}

	}
	else
	{
		edge.p2 = left[i];
		shell.push_back(edge);
		edge.clear();
		edge.p1 = left[i];
		slopes.push_back(relative_slope);
	}

}

void KIRKPATRICK::proceed_r_2(std::deque<float>& slopes, float& relative_slope, EDGE& edge, 
	std::vector<KIRK_POINT>& left, std::vector<EDGE>& shell, int i)
{
	EDGE curr;
	if (!slopes.empty()&& (!shell.empty()))
	{
		if (slopes.back() < 0 && relative_slope > 0)
		{
			edge.p2 = left[i];
			shell.push_back(edge);
			edge.clear();
			edge.p1 = left[i];
			slopes.push_back(relative_slope);
		}
		if (slopes.back() > 0 && relative_slope < 0)
		{
			while ((!slopes.empty()) && slopes.back() > 0)
			{
				slopes.pop_back();
				curr = shell.back();
				shell.pop_back();
				curr.p2 = left[i];
				relative_slope = (curr.p1.y - curr.p2.y) / (curr.p1.x - curr.p2.x);
			}
			if ((!slopes.empty()) && slopes.back() < relative_slope && relative_slope<0)
			{
				while ((!slopes.empty()) && slopes.back() < relative_slope)//&& slopes.back() < 0 && relative_slope < 0)
				{
					slopes.pop_back();
					curr = shell.back();
					shell.pop_back();
					curr.p2 = left[i];
					relative_slope = (curr.p1.y - curr.p2.y) / (curr.p1.x - curr.p2.x);
				}
			}
			slopes.push_back(relative_slope);
			shell.push_back(curr);
			edge.p1 = curr.p2;
		}
	}
	else
	{
		edge.p2 = left[i];
		shell.push_back(edge);
		edge.clear();
		edge.p1 = left[i];
		slopes.push_back(relative_slope);
	}
}

