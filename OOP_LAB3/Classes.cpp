#include "Classes.h"
double to_rads(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}
void show(std::vector<int> A)
{
	for (int i = 0; i < std::size(A); i++)
	{
		std::cout << A[i] << "\t";
	}
	std::cout << "\this->n";
}

std::vector<double> multiply(std::vector<std::vector<double>> A, std::vector<double> b)
{
	std::vector<double> c;
	double m = 0;
	//show(A, b);
	for (int i = 0; i < std::size(A); i++)
	{
		for (int j = 0; j < std::size(A[0]); j++)
		{
			m += A[i][j] * b[j];
		}
		c.push_back(m);
		//show(c);
		m = 0;
	}

	return c;
}
void HEX::create(int red_num, int green_num, int blue_num)
{
	this->red = red_num;
	this->green = green_num;
	this->blue = blue_num;
}

float Point::distance(Point a, Point b)
{
	return sqrt(pow((a.x-b.x),2)+ pow((a.y - b.y), 2)+ pow((a.z - b.z), 2));
}
float Point::distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
void Point::middle(Point a, Point b)
{
	this->x = (a.x + b.x) / 2;
	this->y = (a.y + b.y) / 2;
	this->z = (a.z + b.z) / 2;
	this->initialized = true;
}
void Point::create(float a, float b,float c)
{
	this->x = a;
	this->y = b;
	this->z = c;
	this->initialized = true;
}
void Point::clear()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->initialized = false;
}
void Point::draw(sf::RenderWindow& window) const
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
	text.setCharacterSize(15);
	text.setString(s);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setFillColor(sf::Color::Red);
	text.setPosition(this->x-2 , -(this->y));
	shape.setPosition(this->x-2,-(this->y-2));
	shape.setFillColor(sf::Color::White);
	window.draw(text);
	window.draw(shape);
	
}
bool Point::operator>(Point d)
{
	return this->y > d.y;
}
bool Point::operator<(Point d)
{
	return this->y < d.y;
}
void Point::operator=(Point d)
{
	this->x = d.x;
	this->y = d.y;
	this->z = d.z;
	this->initialized = d.initialized;
	this->r_angle = d.r_angle;
	this->adjacent_tris = d.adjacent_tris;
	this->color = d.color;
	this->tripoints = d.tripoints;
}
bool Point::operator==(Point p)
{
	return this->x==p.x&& this->y == p.y;
}
Point Point::operator*(float k)
{
	
	this->x = this->x* k;
	this->y = this->y* k;
	this->z = this->z* k;
	return *this;
}
float Point::angle(std::vector<float> vec2)
{
	std::vector<float> vec1 = this->normalv;
	float angle = std::acos((vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]) / (sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)) * sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2))));
	return angle;
}
void Point::lightness(float l)
{
	l = abs(l);
	float m = std::max(this->color.r, std::max(this->color.g, this->color.b));
	if (m == 0)
	{
		this->color.r = 255 * l;
		this->color.g = 255 * l;
		this->color.b = 255 * l;
	}
	else
	{
		/*if (l == 0)
			l = 0.001;*/
		this->color.r *= (255 * l) / m;
		this->color.g *= (255 * l) / m;
		this->color.b *= (255 * l) / m;
	}
}
Point Point::operator-(Point b)
{
	Point a;
	a.create(this->x-b.x,this->y-b.y,this->z-b.z);
	a.initialized = this->initialized;
	return a;
}
bool Point::null()
{
	return this->x == 0&& this->y == 0;
}
bool Point::compare_x(Point p1,Point p2)
{
	return p1.x<p2.x;
}
Point Point::rotate(float angles,bool is3d)
{
	this->r_angle = angles;
	float angle = to_rads(angles);

	Point vr;
	std::vector<std::vector<double>> Zp;
	std::vector<double> vec;
	vec.push_back(cos(angle));
	vec.push_back(0);
	vec.push_back(sin(angle));
	Zp.push_back(vec);
	vec.clear();
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(0);
	Zp.push_back(vec);
	vec.clear();
	vec.push_back(-sin(angle));
	vec.push_back(0);
	vec.push_back(cos(angle));
	Zp.push_back(vec);
	vec.clear();
	vec.push_back(this->x);
	vec.push_back(this->y);
	vec.push_back(this->z);
	vec = multiply(Zp, vec);
	vr.create(vec[0], vec[1], vec[2]);

	vr.adjacent_tris = this->adjacent_tris;
	vr.color = this->color;
	vr.tripoints = this->tripoints;
	//Rotating normal
	/*if (!this->normalv.empty()) {
		Point nr;
		nr.create(this->normalv[0], this->normalv[1], this->normalv[2]);
		nr.rotate(angles);
		vr.normalv.push_back(nr.x);
		vr.normalv.push_back(nr.y);
		vr.normalv.push_back(nr.z);
	}*/
	return vr;
}
std::vector<float> Point::vector(Point A)
{

	Point v;
	v = *this - A;
	std::vector<float> vec;
	vec.push_back(v.x);
	vec.push_back(v.y);
	vec.push_back(v.z);
	return vec;
}
void Point::Gouraud(Point& v1, std::vector<float> normalv, Point light)
{
	this->normalv = normalv;
	float rad = this->angle(v1.vector(light));
	this->lightness(rad / 3.14159265359);
	v1.lightness(rad / 3.14159265359);

}





void Edge::create(Point a, Point b)
{
	this->p1=a;
	this->p2=b;
}
void Edge::create(Point* a, Point* b)
{
	this->p1 = *a;
	this->p2 = *b;
}
void Edge::create(Point a, std::vector<float> normalv)
{
	this->p1 = a;
	Point b;
	b.create(normalv[0]+a.x, normalv[1] + a.y, normalv[2] + a.z);
	this->p2 = b;
}
void Edge::create(float x1, float y1, float x2, float y2)
{
	Point a;
	a.create(x1,y1);
	this->p1 = a;
	a.create(x2, y2);
	this->p2 = a;
}
void Edge::clear()
{
	this->p1.clear();
	this->p2.clear();
}
void Edge::draw(sf::RenderWindow& window) 
{
	//float margin = 5;
	//sf::VertexArray quad(sf::Quads, 4);
	//quad[0].position = sf::Vector2f(this->p1.x + margin, this->p1.y);
	//quad[1].position = sf::Vector2f(this->p1.x - margin, this->p1.y);
	//quad[2].position = sf::Vector2f(this->p2.x + margin, this->p2.y);
	//quad[3].position = sf::Vector2f(this->p2.x - margin, this->p2.y);
	//window.draw(quad);

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(this->p1.x, -this->p1.y)),
		sf::Vertex(sf::Vector2f(this->p2.x, -this->p2.y))
	};
	window.draw(line, 3, sf::Lines);
	this->p1.draw(window);

}
void Edge::draw_3d(sf::RenderWindow& window) const
{
	float Lens = 1000;
	float k1, k2;
	k1 = exp(this->p1.z / Lens);
	k2 = exp(this->p2.z / Lens);

	
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(this->p1.x*k1, -this->p1.y*k1)),
		sf::Vertex(sf::Vector2f(this->p2.x*k2, -this->p2.y*k2))
	};
	line[0].color = this->color;
	line[1].color = this->color;
	window.draw(line, 2, sf::Lines);
}
void Edge::rotate(float angle)
{
	this->p1=this->p1.rotate(angle, true);
	this->p2=this->p2.rotate(angle, true);

}
void Edge::operator=(Edge e)
{
	this->p1 = e.p1;
	this->p2 = e.p2; 
	this->s1 = e.s1;
	this->s2 = e.s2;
}
Edge Edge::operator*(float k)
{
	this->p1 = this->p1 * k;
	this->p2 = this->p2 * k;
	return *this;
}


void Face::draw(sf::RenderWindow& window) const
{
	sf::ConvexShape convex;
	convex.setPointCount(3);
	for (int i = 0; i < 3; i++)
	{
		convex.setPoint(i, sf::Vector2f(this->v[i].x, -this->v[i].y));
	}
	/*convex.setPoint(0, sf::Vector2f(this->v1.x, -this->v1.y));
	convex.setPoint(1, sf::Vector2f(this->v2.x, -this->v2.y));
	convex.setPoint(2, sf::Vector2f(this->v3.x, -this->v3.y));*/
	convex.setOutlineThickness(this->border_width);
	convex.setOutlineColor(this->border_color);
	convex.setFillColor(this->color);
	window.draw(convex);
	
}
void Face::draw_3d(sf::RenderWindow& window, Point light,bool islit,bool gouraud, bool border)
{
	
	float Lens = 1000;
	std::vector<float> k(this->n);
	for (int i = 0; i < this->n; i++)
	{
		k[i] = exp(this->v[i].z / Lens);
	}
	if (!gouraud) 
	{
		sf::ConvexShape convex;
		convex.setPointCount(this->n);
		for (int i = 0; i < this->n; i++)
		{
			convex.setPoint(i, sf::Vector2f(this->v[i].x * k[i], -this->v[i].y * k[i]));
		}
		this->normal(true);
		if (islit)
		{
			float rad = this->angle(this->center_point().vector(light));
			this->lightness(rad / 3.14159265359);
		}
		convex.setFillColor(this->color);
		window.draw(convex);
		if (border)
		{
			for (int i = 0; i < this->n; i++)
			{
				this->borders[i].draw_3d(window);
			}
		}
	}
	else
	{
		sf::VertexArray Face(sf::Triangles, this->n);
		if (this->n == 4) 
			Face.setPrimitiveType(sf::Quads);

		
		// define the position of the Face's points
		for (int i = 0; i < this->n; i++)
		{
			Face[i].position = sf::Vector2f(this->v[i].x * k[i], -this->v[i].y * k[i]);
			Face[i].color = this->v[i].color;
		}
		window.draw(Face);
		if (border)
		{
			for (int i = 0; i < 3; i++)
			{
				this->borders[i].draw_3d(window);
			}
		}
	}
	
	
	

}
void Face::scale_this(float lambda)
{
	Point cen;
	cen = this->center_point();

	for (int i = 0; i < this->n; i++)
	{
		this->v[i].x = (this->v[i].x + lambda * cen.x) / (1 + lambda);
		this->v[i].y = (this->v[i].y + lambda * cen.y) / (1 + lambda);
		this->v[i].z = (this->v[i].z + lambda * cen.z) / (1 + lambda);
	}
	/*this->v1.x = (this->v1.x + lambda * cen.x) / (1 + lambda);
	this->v1.y = (this->v1.y + lambda * cen.y) / (1 + lambda);
	this->v1.z = (this->v1.z + lambda * cen.z) / (1 + lambda);

	this->v2.x = (this->v2.x + lambda * cen.x) / (1 + lambda);
	this->v2.y = (this->v2.y + lambda * cen.y) / (1 + lambda);
	this->v2.z = (this->v2.z + lambda * cen.z) / (1 + lambda);

	this->v3.x = (this->v3.x + lambda * cen.x) / (1 + lambda);
	this->v3.y = (this->v3.y + lambda * cen.y) / (1 + lambda);
	this->v3.z = (this->v3.z + lambda * cen.z) / (1 + lambda);*/
}
Face Face::scale(float lambda)
{
	Face tris = *this;
	Point cen;
	cen = this->center_point();

	for (int i = 0; i < this->n; i++)
	{
		tris.v[i].x = (this->v[i].x + lambda * cen.x) / (1 + lambda);
		tris.v[i].y = (this->v[i].y + lambda * cen.y) / (1 + lambda);
		tris.v[i].z = (this->v[i].z + lambda * cen.z) / (1 + lambda);
	}
	/*tris.v1.x = (this->v1.x + lambda * cen.x) / (1 + lambda);
	tris.v1.y = (this->v1.y + lambda * cen.y) / (1 + lambda);
	tris.v1.z = (this->v1.z + lambda * cen.z) / (1 + lambda);

	tris.v2.x = (this->v2.x + lambda * cen.x) / (1 + lambda);
	tris.v2.y = (this->v2.y + lambda * cen.y) / (1 + lambda);
	tris.v2.z = (this->v2.z + lambda * cen.z) / (1 + lambda);

	tris.v3.x = (this->v3.x + lambda * cen.x) / (1 + lambda);
	tris.v3.y = (this->v3.y + lambda * cen.y) / (1 + lambda);
	tris.v3.z = (this->v3.z + lambda * cen.z) / (1 + lambda);*/
	return tris;
}
void Face::create(Point v1, Point v2, Point v3)
{
	this->n = 3;
	this->v[0] = v1;
	this->v[1] = v2;
	this->v[2] = v3;

	Edge e;
	e.create(v1, v2);
	this->borders[0] = e;
	e.create(v1, v3);
	this->borders[1] = e;
	e.create(v2, v3);
	this->borders[2] = e;
	this->border = true;
}
void Face::create(Point v1, Point v2, Point v3, Point v4)
{
	this->n = 4;
	this->v = { Point(),Point(),Point(),Point() };
	this->v[0] = v1;
	this->v[1] = v2;
	this->v[2] = v3;
	this->v[3] = v4;

	Edge e;
	e.create(v1, v2);
	this->borders[0] = e;
	e.create(v2, v3);
	this->borders[1] = e;
	e.create(v1, v4);
	this->borders[2] = e;
	e.create(v3, v4);
	this->borders[2] = e;
	this->border = true;
}
void Face::create(Point& v1, Point& v2, Point& v3, int tris_index)
{
	this->n = 3;
	v1.adjacent_tris.push_back(tris_index);
	v2.adjacent_tris.push_back(tris_index);
	v3.adjacent_tris.push_back(tris_index);
	this->v[0] = v1;
	this->v[1] = v2;
	this->v[2] = v3;
	v1.tripoints[tris_index] = "v1";
	v2.tripoints[tris_index] = "v2";
	v3.tripoints[tris_index] = "v3";
	
	
	Edge e;
	e.create(v1, v2);
	this->borders[0] = e;
	e.create(v1, v3);
	this->borders[1] = e;
	e.create(v2, v3);
	this->borders[2] = e;
	this->border = true;
	
}
void Face::create(Point& v1, Point& v2, Point& v3,  Point& v4, int tris_index)
{
	this->n = 4;
	this->v = { Point(),Point(),Point(),Point() };
	v1.adjacent_tris.push_back(tris_index);
	v2.adjacent_tris.push_back(tris_index);
	v3.adjacent_tris.push_back(tris_index);
	v4.adjacent_tris.push_back(tris_index);
	this->v[0] = v1;
	this->v[1] = v2;
	this->v[2] = v3;
	this->v[3] = v4;
	v1.tripoints[tris_index] = "v1";
	v2.tripoints[tris_index] = "v2";
	v3.tripoints[tris_index] = "v3";
	v4.tripoints[tris_index] = "v4";


	Edge e;
	e.create(v1, v2);
	this->borders[0] = e;
	e.create(v2, v3);
	this->borders[1] = e;
	e.create(v1, v4);
	this->borders[2] = e;
	e.create(v3, v4);
	this->borders[2] = e;
	this->border = true;

}
float Face::center()//TUTA?
{
	if (!this->centroid.initialized) 
	{
		Point centre;
		if(std::size(v)==3)
			centre.create((this->v[0].x + this->v[1].x + this->v[2].x) / 3.0, (this->v[0].y + this->v[1].y + this->v[2].y) / 3.0, (this->v[0].z + this->v[1].z + this->v[2].z) / 3.0);
		else if(std::size(v) == 4)
			centre.create((this->v[0].x + this->v[1].x + this->v[2].x+ this->v[3].x) / 4.0, (this->v[0].y + this->v[1].y + this->v[2].y + this->v[3].y) / 4.0, (this->v[0].z + this->v[1].z + this->v[2].z + this->v[3].z) / 4.0);
		this->centroid = centre;
	}
	return this->centroid.z;
}
Point Face::center_point()//TUTA?
{
	if (!this->centroid.initialized)
	{
		Point centre;
		if (std::size(v) == 3)
			centre.create((this->v[0].x + this->v[1].x + this->v[2].x) / 3.0, (this->v[0].y + this->v[1].y + this->v[2].y) / 3.0, (this->v[0].z + this->v[1].z + this->v[2].z) / 3.0);
		else if (std::size(v) == 4)
			centre.create((this->v[0].x + this->v[1].x + this->v[2].x + this->v[3].x) / 4.0, (this->v[0].y + this->v[1].y + this->v[2].y + this->v[3].y) / 4.0, (this->v[0].z + this->v[1].z + this->v[2].z + this->v[3].z) / 4.0);
		this->centroid = centre;
	}
	return this->centroid;
}
void Face::paint(std::string Col)
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
	for (int i = 0; i < this->n; i++)
	{

		this->v[i].color = this->color;
	}

}
void Face::paint(HEX color)
{
	this->color = sf::Color(color.red, color.green, color.blue);
	this->border_color = sf::Color(color.red - (color.red * 100) / 255, color.green - (color.green * 100) / 255, color.blue - (color.blue * 100) / 255);
	for (int i = 0; i < this->n; i++)
	{
		this->v[i].color =this->color;
		this->borders[i].color = this->border_color;
	}
	
	/*this->v2.color = sf::Color(color.red, color.green, color.blue);
	this->v3.color = sf::Color(color.red, color.green, color.blue);*/
}
void Face::lightness(float l)
{
	l = abs(l);
	float m=std::max(this->color.r, std::max(this->color.g, this->color.b));
	if (m == 0)
	{
		this->color.r = 255 * l;
		this->color.g = 255 * l;
		this->color.b = 255 * l;
	}
	else
	{
		/*if (l == 0)
			l = 0.001;*/
		this->color.r *= (255 * l) / m;
		this->color.g *= (255 * l) / m;
		this->color.b *= (255 * l) / m;
	}
	
}
Face Face::rotate(float angle)//TUTA?
{
	Face tris;
	if(std::size(v)==3)
		tris.create
	(
		this->v[0].rotate(angle, true),
		this->v[1].rotate(angle, true),
		this->v[2].rotate(angle, true)
	);
	else if(std::size(v)==4)
		tris.create
		(
			this->v[0].rotate(angle, true),
			this->v[1].rotate(angle, true),
			this->v[2].rotate(angle, true), 
			this->v[3].rotate(angle, true)
		);
	tris.normalv = this->normalv;
	this->r_angle = angle;
	tris.color = this->color;
	

	return tris;
}
std::vector<float> Face::normal(bool update)
{
	float nx, ny, nz;
	if (update)
	{
		
		nx = (this->v[1].y - this->v[0].y) * (this->v[2].z - this->v[0].z) - (this->v[1].z - this->v[0].z) * (this->v[2].y - this->v[0].y);
		ny = (this->v[1].z - this->v[0].z) * (this->v[2].x - this->v[0].x) - (this->v[1].x - this->v[0].x) * (this->v[2].z - this->v[0].z);
		nz = (this->v[1].x - this->v[0].x) * (this->v[2].y - this->v[0].y) - (this->v[1].y - this->v[0].y) * (this->v[2].x - this->v[0].x);
		float lenth = sqrt(pow(nx, 2) + pow(ny, 2) + pow(nz, 2));
		nx *= 10 / lenth;
		ny *= 10 / lenth;
		nz *= 10 / lenth;
		if (this->normalv.empty())
		{
			this->normalv.push_back(nx);
			this->normalv.push_back(ny);
			this->normalv.push_back(nz);
			/*std::cout << this->normalv[0]<<"\this->n";
			std::cout << this->normalv[1] << "\this->n";
			std::cout << this->normalv[2];*/
		}
		else
		{
			this->normalv[0] = nx;
			this->normalv[1] = ny;
			this->normalv[2] = nz;
		}
	}
	else
	{
		float lenth = sqrt(pow(this->normalv[0], 2) + pow(this->normalv[1], 2) + pow(this->normalv[2], 2));
		this->normalv[0] *= 10 / lenth;
		this->normalv[1] *= 10 / lenth;
		this->normalv[2] *= 10 / lenth;
	}
	return this->normalv;
}
void Face::operator=(Face tris)
{
	this->border_color = tris.border_color;
	this->color = tris.color;
	this->v = tris.v;
	this->border_width = tris.border_width;
	this->centroid = tris.centroid;
	this->normalv = tris.normalv;
	this->r_angle = tris.r_angle;
	this->border = tris.border;
	this->borders = tris.borders;
}
Face Face::operator*(float k)
{
	for (int i = 0; i < this->n; i++)
	{
		this->v[i] = this->v[i]* k;
	}
	/*this->v2 = this->v2 * k;
	this->v3 = this->v3 * k;*/
	return *this;
}

float Face::angle(std::vector<float> vec2)
{
	std::vector<float> vec1 = this->normalv;
	float angle = std::acos((vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]) / (sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)) * sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2))));
	return angle;
}

std::ostream& operator<<(std::ostream& os, Point p)
{
	os << "(" << p.x << "," << p.y<<","<<p.z << ")";
	return os;
}
std::ostream& operator<<(std::ostream& os, Edge& e)
{
	os << "[" << e.p1 << "," << e.p2 << "]\this->n";
	return os;
}
std::ostream& operator<<(std::ostream& os, Face t)
{
	for (int i = 0; i <3; i++)
	{
		os << "(" << t.v[i].x << "," << t.v[i].y << "," << t.v[i].z << ")\this->n";
	}
	/*os << "(" << t.v2.x << "," << t.v2.y << "," << t.v2.z << ")\this->n";
	os << "(" << t.v3.x << "," << t.v3.y << "," << t.v3.z << ")\this->n";*/
	return os;
}
std::ostream& operator<<(std::ostream& os, Object o)
{
	for (int i = 0; i < std::size(o.mesh); i++)
	{
		os << "tris " << i + 1 << "\this->n";
		os << o.mesh[i];
	}
	return os;
}

void Object::scale(float koefficient)
{
	
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		this->mesh[i] = this->mesh[i] * koefficient;
	}
	for (int i = 0; i < std::size(this->vertex_normals); i++)
	{
		this->vertex_normals[i][0] = this->vertex_normals[i][0] * koefficient;
		this->vertex_normals[i][1] = this->vertex_normals[i][1] * koefficient;
		this->vertex_normals[i][2] = this->vertex_normals[i][2] * koefficient;
		this->vertex_normals_vis[i] = this->vertex_normals_vis[i] * koefficient;
		this->points[i] = this->points[i] * koefficient;
	}
}
void swap(std::vector<Face> &tris, int pos1, int pos2)
{
	Face t1;
	t1=tris[pos1];
	tris[pos1] = tris[pos2];
	tris[pos2] = t1;
}
int partition(std::vector<Face> &tris, int low, int high)
{
	float pivot = tris[high].center();
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (tris[j].center() < pivot)
		{
			i++; 
			swap(tris, i, j);
		}
	}
	swap(tris, i+1,high);
	return (i + 1);
}
void quickSort(std::vector<Face> &tris, int low, int high)
{
	if (low < high)
	{
		int pi = partition(tris, low, high);
		quickSort(tris, low, pi - 1);
		quickSort(tris, pi + 1, high);
	}
}

void Object::draw(sf::RenderWindow& window, Point light, sf::Color, bool islit, bool normal_visible, float angle, bool gouraud,bool border)
{
	
	Object obj;
	obj = this->rotate(angle);
	this->r_angle = angle;
	
	

	//PAINT

	if (gouraud && islit)
	{
		for (int i = 0; i < std::size(obj.points); i++)
		{
			for (int j = 0; j < std::size(obj.points[i].adjacent_tris); j++)
			{

				std::string vertex = obj.points[i].tripoints
					[
						obj.points[i].adjacent_tris[j]
					];

				if (vertex == "v1")
					obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v[0], obj.vertex_normals[i], light);
				
				if (vertex == "v2")
					obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v[1], obj.vertex_normals[i], light);
				
				if (vertex == "v3")
					obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v[2], obj.vertex_normals[i], light);
				
				if (std::size(obj.mesh[obj.points[i].adjacent_tris[j]].v) == 4)
					if (vertex == "v4")
						obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v[3], obj.vertex_normals[i], light);
			}
		}
	}
	if (!obj.sorted)
	{
		quickSort(obj.mesh, 0, std::size(obj.mesh) - 1);
		obj.sorted = true;
	}
	for (int i = 0; i < std::size(obj.mesh); i++)
	{
		obj.mesh[i].draw_3d(window, light, islit, gouraud,border);
	}
	if (normal_visible)
	{
		for (int i = 0; i < std::size(obj.vertex_normals); i++)
		{
			Edge n;
			n.create(obj.points[i], obj.vertex_normals[i]);
			n.draw_3d(window);
		}
	}
	
}
void Object::paint(std::string Col)
{
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		this->mesh[i].paint(Col);
	}
	

}
void Object::paint(HEX color)
{
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		this->mesh[i].paint(color);
	}
	this->color.r = color.red;
	this->color.g = color.green;
	this->color.b = color.blue;
	//this->mesh[100].paint("Red");
	
}
void Object::create(std::vector<Face> mesh, std::vector<Point> Point)
{
	this->mesh = mesh;
	this->points = Point;
	
	this->calculate_center();

	std::vector<float> vertex_normal = { 0,0,0 };
	std::vector<float> tris_normal = { 0,0,0 };
	float lenth;
	Edge e;
	for (int i = 0; i < std::size(this->points); i++)
	{
		for (int j = 0; j < std::size(points[i].adjacent_tris); j++)
		{
			tris_normal = mesh[points[i].adjacent_tris[j]].normal();
			vertex_normal[0] += tris_normal[0];
			vertex_normal[1] += tris_normal[1];
			vertex_normal[2] += tris_normal[2];
		}
		lenth = sqrt(pow(vertex_normal[0], 2) + pow(vertex_normal[1], 2) + pow(vertex_normal[2], 2));
		vertex_normal[0] *= 10 / lenth;
		vertex_normal[1] *= 10 / lenth;
		vertex_normal[2] *= 10 / lenth;
		this->vertex_normals.push_back(vertex_normal);
		e.create(points[i], vertex_normal);
		this->vertex_normals_vis.push_back(e);
		e.clear();
		vertex_normal = { 0,0,0 };
	}
}
void Object::operator=(std::vector<Face> mesh)
{
	this->mesh = mesh;

}
void Object::operator=(Object obj)
{
	this->mesh = obj.mesh;
	this->points = obj.points;
	this->vertex_normals = obj.vertex_normals;
	this->vertex_normals_vis = obj.vertex_normals_vis;

	this->r_angle = obj.r_angle;
	this->sorted = obj.sorted;
	this->color = obj.color;

}
Object Object::rotate(float angle)
{
	Object obj;
	Point p;

	obj = *this;
	for (int i = 0; i < std::size(obj.mesh); i++)
	{
		obj.mesh[i] = obj.mesh[i].rotate(angle);
	}
	for (int i = 0; i < std::size(obj.points); i++)
	{
		obj.points[i] = obj.points[i].rotate(angle);
		obj.vertex_normals_vis[i].rotate(angle);
		p.create(obj.vertex_normals[i][0], obj.vertex_normals[i][1], obj.vertex_normals[i][2]);
		p = p.rotate(angle, true);
		obj.vertex_normals[i][0] = p.x;
		obj.vertex_normals[i][1] = p.y;
		obj.vertex_normals[i][2] = p.z;
	}
	return obj;
}
void Object::Subdivide(int i, std::string subd_type)
{

}
void Object::calculate_center()
{
	if (!this->center.initialized)
	{
		float x, y, z;
		x = 0;
		y = 0;
		z = 0;
		for (int i = 0; i < std::size(this->mesh); i++)
		{
			x += this->mesh[i].center_point().x;
			y += this->mesh[i].center_point().y;
			z += this->mesh[i].center_point().z;
		}
		x = x / std::size(this->mesh);
		y = y / std::size(this->mesh);
		z = z / std::size(this->mesh);
		this->center.create(x, y, z);
	}
}
