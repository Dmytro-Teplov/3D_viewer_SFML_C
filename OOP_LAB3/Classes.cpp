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
void POINT::create(float a, float b,float c)
{
	this->x = a;
	this->y = b;
	this->z = c;
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
	s.push_back(',');
	s += std::to_string((int)this->z);
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
	text.setPosition(this->x-2 , -(this->y));
	shape.setPosition(this->x-2,-(this->y-2));
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
	this->z = d.z;

}
bool POINT::operator==(POINT p)
{
	return this->x==p.x&& this->y == p.y;
}
POINT POINT::operator*(float k)
{
	POINT newP;
	newP.create(this->x * k, this->y * k,this->z*k);
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
	convex.setPoint(0, sf::Vector2f(this->v1.x, -this->v1.y));
	convex.setPoint(1, sf::Vector2f(this->v2.x, -this->v2.y));
	convex.setPoint(2, sf::Vector2f(this->v3.x, -this->v3.y));

	convex.setOutlineThickness(this->border_width);
	convex.setOutlineColor(this->border_color);
	convex.setFillColor(this->color);
	window.draw(convex);
	
}
void TRIANGLE::draw_3d(sf::RenderWindow& window) const
{
	sf::ConvexShape convex;
	convex.setPointCount(3);
	float k1, k2, k3;
	if (this->v1.z < 0)
		k1 = exp(this->v1.z / 1000);
	else
		k1 = exp(this->v1.z / 380);

	if (this->v2.z < 0)
		k2 = exp(this->v2.z / 1000);
	else
		k2 = exp(this->v2.z / 380);

	if (this->v3.z < 0)
		k3 = exp(this->v3.z / 1000);
	else
		k3 = exp(this->v3.z/380);
	//std::cout << k1 << " " << k2 << " " << k3;
	convex.setPoint(0, sf::Vector2f(this->v1.x*k1, -this->v1.y*k1));
	convex.setPoint(1, sf::Vector2f(this->v2.x*k2, -this->v2.y*k2));
	convex.setPoint(2, sf::Vector2f(this->v3.x*k3, -this->v3.y*k3));

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
	os << "(" << p.x << "," << p.y<<","<<p.z << ")";
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


void OBJECT::draw(sf::RenderWindow& window) const
{
	
}
