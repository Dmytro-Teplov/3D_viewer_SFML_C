#include "Classes.h"
std::vector<Edge> border_global;
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
	std::cout << "n";
}
float dot_product(Point a, Point b) 
{
	float product = 0;
	product += a.x * b.x;
	product += a.y * b.y;
	product += a.z * b.z;
	return product;
}
Point cross_product(Point a, Point b) 
{
	Point c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = -(a.x * b.z - a.z * b.x);
	c.z = a.x * b.y - a.y * b.x;
	return c;
}
bool less(Point a, Point b,Point center)
{
	a = a - center;
	b = b - center;
	int det = dot_product(cross_product(a,b),center);
	if (det > 0)
		return true;
	if (det < 0)
		return false;

	int d1 = pow(a.x,2)+ pow(a.y, 2)+ pow(a.z, 2);
	int d2 = pow(b.x,2)+ pow(b.y, 2)+ pow(b.z, 2);
	return d1 < d2;
}

void swap2(std::vector<Point>& vs, int pos1, int pos2, std::vector<int>& ind)
{
	Point t1;
	t1 = vs[pos1];
	vs[pos1] = vs[pos2];
	vs[pos2] = t1;

	int i1;
	i1 = ind[pos1];
	ind[pos1] = ind[pos2];
	ind[pos2] = i1;
	//if (tris[pos1 or 2] is backwards): delete
	//else: previous thing 
}
int partition2(std::vector<Point>& vs, int low, int high, Point center, Point p, Point r, std::vector<int>& ind)
{
	Point pivot = vs[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (less(vs[j],pivot, center))
		{
			i++;
			swap2(vs, i, j,ind);
		}
	}
	swap2(vs, i + 1, high,ind);
	return (i + 1);
}
void quickSort2(std::vector<Point>& vs, int low, int high, Point center, Point p, Point r, std::vector<int>& ind)
{
	if (low < high)
	{
		int pi = partition2(vs, low, high, center, p, r,ind);
		quickSort2(vs, low, pi - 1, center, p, r,ind);
		quickSort2(vs, pi + 1, high, center, p, r,ind);
	}
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
	this->normalv = d.normalv;
}
bool Point::operator==(Point const& p) const
{
	return this->x==p.x && this->y == p.y && this->z==p.z;
}
Point Point::operator*(float k)
{
	Point p = *this;
	p.x = this->x* k;
	p.y = this->y* k;
	p.z = this->z* k;
	this->initialized = true;
	return p;
}
Point Point::operator+(Point b)//NOT TESTED
{
	Point p = *this;
	p.x += b.x;
	p.y += b.y;
	p.z += b.z;
	p.initialized = true;
	return p;
}
Point Point::operator/(float b)//NOT TESTED
{
	Point p = *this;
	p.x = this->x / b;
	p.y = this->y / b;
	p.z = this->z / b;
	this->initialized = true;
	return p;
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
	return vr;
}
void sort_clockwise(std::vector<Point> vs, std::vector<int>& indices)
{
	Point c;
	for (int i = 0; i < std::size(vs); i++)
	{
		
		c = c + vs[i];

	}
	/*for (int i = 0; i < std::size(vs); i++)
	{

		vs[i]= vs[i]-c;

	}*/
	c = c / std::size(vs);
	Point r = vs[0]-c;
	Point p = cross_product(r, c);
	quickSort2(vs, 0, std::size(vs) - 1, c,p, r, indices);
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
	this->adjacentFaces.clear();
}
Point Edge::center()
{
	return (this->p1+this->p2)/2;
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
	this->adjacentFaces = e.adjacentFaces;
	this->thicc = e.thicc;
	this->color = e.color;
}
bool Edge::operator==(Edge const&  e) const
{
	if ((this->p1 == e.p1 && this->p2 == e.p2) ||(this->p1 == e.p2 && this->p2 == e.p1))
	{
		return true;
	} 
	else 
	{
		return false;
	}
	
}
bool Edge::contains(Edge& e, Point p)
{
	if ((e.p1 == p) || (e.p2 == p))
		return true;
	else
		return false;
}	
Edge Edge::operator*(float k)
{
	Edge e;
	e = *this;
	e.p1 = this->p1 * k;
	e.p2 = this->p2 * k;
	return e;
}


void Face::draw(sf::RenderWindow& window) const
{
	sf::ConvexShape convex;
	convex.setPointCount(3);
	for (int i = 0; i < 3; i++)
	{
		convex.setPoint(i, sf::Vector2f(this->v[i].x, -this->v[i].y));
	}
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

		
		for (int i = 0; i < this->n; i++)
		{
			Face[i].position = sf::Vector2f(this->v[i].x * k[i], -this->v[i].y * k[i]);
			Face[i].color = this->v[i].color;
		}
		window.draw(Face);
		if (border)
		{
			for (int i = 0; i < this->n; i++)
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
	return tris;
}
//void Face::update(Point v1, Point v2, Point v3)
//{
//	if(this->border)
//	{
//		this->borders[0].p1 = v1;
//		this->borders[0].p2 = v2;
//
//		this->borders[1].p1 = v2;
//		this->borders[1].p2 = v3;
//
//		this->borders[2].p1 = v3;
//		this->borders[2].p2 = v1;
//	}
//	this->v[0] = v1;
//	this->v[1] = v2;
//	this->v[2] = v3;
//}
//void Face::update(Point v1, Point v2, Point v3, Point v4)
//{
//	if (this->border)
//	{
//		this->borders[0].p1 = v1;
//		this->borders[0].p2 = v2;
//
//		this->borders[1].p1 = v2;
//		this->borders[1].p2 = v3;
//
//		this->borders[2].p1 = v3;
//		this->borders[2].p2 = v4;
//
//		this->borders[3].p1 = v4;
//		this->borders[3].p2 = v1;
//	}
//	this->v = { Point(),Point(),Point(),Point() };
//	this->v[0] = v1;
//	this->v[1] = v2;
//	this->v[2] = v3;
//	this->v[3] = v4;
//}
//void Face::create(Point& v1, Point& v2, Point& v3, int tris_index)
//{
//	this->n = 3;
//	v1.adjacent_tris.push_back(tris_index);
//	v2.adjacent_tris.push_back(tris_index);
//	v3.adjacent_tris.push_back(tris_index);
//	this->v[0] = v1;
//	this->v[1] = v2;
//	this->v[2] = v3;
//	v1.tripoints[tris_index] = "v1";
//	v2.tripoints[tris_index] = "v2";
//	v3.tripoints[tris_index] = "v3";
//	
//	
//	Edge e;
//	this->borders = { Edge(),Edge(),Edge() };
//	//----------
//	e.create(v1, v2);
//	std::vector<Edge>::iterator dupl = std::find(border_global.begin(), border_global.end(), e);
//	if (dupl == border_global.end())
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(), dupl + 1) - 1].adjacentFaces.push_back(tris_index);
//	this->borders[0] = e;
//	//----------
//	e.clear();
//	e.create(v2, v3);
//	dupl = std::find(border_global.begin(), border_global.end(), e);
//	if (dupl == border_global.end())
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(), dupl + 1) - 1].adjacentFaces.push_back(tris_index);
//	this->borders[1] = e;
//	//----------
//	e.clear();
//	e.create(v3, v1);
//	dupl = std::find(border_global.begin(), border_global.end(), e);
//	if (dupl == border_global.end())
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(), dupl + 1) - 1].adjacentFaces.push_back(tris_index);
//	this->borders[2] = e;
//	this->border = true;
//	
//}
void Face::update(std::vector<Point> v)
{
	int v_count = std::size(v);
	this->n = v_count;
	//Edge e;
	this->v = std::vector<Point>(v_count);
	if (this->border)
	{
		this->borders = std::vector<Edge>(v_count);
	}
	for (int i = 0; i < v_count; i++)
	{
		this->v[i] = v[i];
		if (this->border)
		{
			//this->borders = std::vector<Edge>(v_count);
			if (i != v_count-1) 
			{
				this->borders[i].p1 = v[i];
				this->borders[i].p2 = v[i+1];
			}
			else 
			{
				this->borders[i].p1 = v[i];
				this->borders[i].p2 = v[0];
			}
		}
	}
}
void Face::create(std::vector<Point*> v, int tris_index)
{
	int v_count = std::size(v);
	this->n = v_count;
	Edge e;
	this->borders = std::vector<Edge>(v_count);
	this->v = std::vector<Point>(v_count);

	for (int i = 0; i < v_count; i++)
	{
		v[i]->adjacent_tris.push_back(tris_index);
		this->v[i] = *v[i];
		v[i]->tripoints[tris_index] = "v"+std::to_string(i+1);
		//---------------------------
		if (i != v_count - 1) 
			e.create(v[i], v[i + 1]);
		else
			e.create(v[i], v[0]);

		std::vector<Edge>::iterator dupl = std::find(border_global.begin(), border_global.end(), e);
		if (dupl == border_global.end())
		{
			e.adjacentFaces.push_back(tris_index);
			border_global.push_back(e);
		}
		else
			border_global[std::distance(border_global.begin(), dupl + 1) - 1].adjacentFaces.push_back(tris_index);
		this->borders[i] = e;
		e.clear();
	}
	this->border = true;
}
//void Face::create(Point& v1, Point& v2, Point& v3,  Point& v4, int tris_index)
//{
//	this->n = 4;
//	this->v = { Point(),Point(),Point(),Point() };
//	
//	v1.adjacent_tris.push_back(tris_index);
//	v2.adjacent_tris.push_back(tris_index);
//	v3.adjacent_tris.push_back(tris_index);
//	v4.adjacent_tris.push_back(tris_index);
//	v1.tripoints[tris_index] = "v1";
//	v2.tripoints[tris_index] = "v2";
//	v3.tripoints[tris_index] = "v3";
//	v4.tripoints[tris_index] = "v4";
//	this->v[0] = v1;
//	this->v[1] = v2;
//	this->v[2] = v3;
//	this->v[3] = v4;
//	
//
//
//	
//
//	Edge e;
//	this->borders = std::vector<Edge>(4);
//	//----------
//	e.create(v1, v2);
//	std::vector<Edge>::iterator dupl = std::find(border_global.begin(), border_global.end(),e);
//	if (dupl == border_global.end()) 
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(),dupl+1) - 1].adjacentFaces.push_back(tris_index);
//	this->borders[0]=e;
//	//----------
//	e.clear();
//	e.create(v2, v3);
//	dupl = std::find(border_global.begin(), border_global.end(), e);
//	if (dupl == border_global.end())
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(), dupl + 1) - 1].adjacentFaces.push_back(tris_index);
//	this->borders[1] = e;
//	//----------
//	e.clear();
//	e.create(v3, v4);
//	dupl = std::find(border_global.begin(), border_global.end(), e);
//	if (dupl == border_global.end())
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(), dupl + 1) - 1].adjacentFaces.push_back(tris_index);
//	this->borders[2] = e;
//	//----------
//	e.clear();
//	e.create(v4, v1);
//	dupl = std::find(border_global.begin(), border_global.end(), e);
//	if (dupl == border_global.end())
//	{
//		e.adjacentFaces.push_back(tris_index);
//		border_global.push_back(e);
//	}
//	else
//		border_global[std::distance(border_global.begin(), dupl + 1)-1].adjacentFaces.push_back(tris_index);
//	this->borders[3] = e;
//	//----------
//	this->border = true;
//	
//}
float Face::center()
{
	Point centre;
	centre = std::accumulate(this->v.begin(), this->v.end(), Point()) / std::size(this->v);
	this->centroid = centre;
	return this->centroid.z;
}
Point Face::center_point()
{
	if (!this->centroid.initialized)
	{
		Point center;
		/*if (std::size(v) == 3)
			center.create((this->v[0].x + this->v[1].x + this->v[2].x) / 3.0, (this->v[0].y + this->v[1].y + this->v[2].y) / 3.0, (this->v[0].z + this->v[1].z + this->v[2].z) / 3.0);
		else if (std::size(v) == 4)
			center.create((this->v[0].x + this->v[1].x + this->v[2].x + this->v[3].x) / 4.0, (this->v[0].y + this->v[1].y + this->v[2].y + this->v[3].y) / 4.0, (this->v[0].z + this->v[1].z + this->v[2].z + this->v[3].z) / 4.0);*/
		center = std::accumulate(this->v.begin(),this->v.end(),Point())/std::size(this->v);
		this->centroid = center;
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
	//Face tris;
	std::vector<Point> v(std::size(this->v));
	for (int i = 0; i < std::size(v);i++)
	{
		v[i] = this->v[i].rotate(angle, true);
	}
	this->update(v);
	/*if(std::size(v)==3)
		this->update
	(
		this->v[0].rotate(angle, true),
		this->v[1].rotate(angle, true),
		this->v[2].rotate(angle, true)
	);
	else if(std::size(v)==4)
		this->update
		(
			this->v[0].rotate(angle, true),
			this->v[1].rotate(angle, true),
			this->v[2].rotate(angle, true), 
			this->v[3].rotate(angle, true)
		);*/
	this->r_angle = angle;
	return *this;
}
std::vector<float> Face::normal(bool update)
{
	float nx=0, ny=0, nz=0;
	if (update)
	{
		//if (this->n ==3) {
			nx = (this->v[1].y - this->v[0].y) * (this->v[2].z - this->v[0].z) - (this->v[1].z - this->v[0].z) * (this->v[2].y - this->v[0].y);
			ny = (this->v[1].z - this->v[0].z) * (this->v[2].x - this->v[0].x) - (this->v[1].x - this->v[0].x) * (this->v[2].z - this->v[0].z);
			nz = (this->v[1].x - this->v[0].x) * (this->v[2].y - this->v[0].y) - (this->v[1].y - this->v[0].y) * (this->v[2].x - this->v[0].x);
		//}
		/*else if (this->n == 4)
		{
			nx = (this->v[1].y - this->v[0].y) * (this->v[2].z - this->v[0].z) - (this->v[1].z - this->v[0].z) * (this->v[2].y - this->v[0].y);
			ny = (this->v[1].z - this->v[0].z) * (this->v[2].x - this->v[0].x) - (this->v[1].x - this->v[0].x) * (this->v[2].z - this->v[0].z);
			nz = (this->v[1].x - this->v[0].x) * (this->v[2].y - this->v[0].y) - (this->v[1].y - this->v[0].y) * (this->v[2].x - this->v[0].x);
			float nx2, ny2, nz2;
			nx2 = (this->v[1].y - this->v[3].y) * (this->v[2].z - this->v[3].z) - (this->v[1].z - this->v[3].z) * (this->v[2].y - this->v[3].y);
			ny2 = (this->v[1].z - this->v[3].z) * (this->v[2].x - this->v[3].x) - (this->v[1].x - this->v[3].x) * (this->v[2].z - this->v[3].z);
			nz2 = (this->v[1].x - this->v[3].x) * (this->v[2].y - this->v[3].y) - (this->v[1].y - this->v[3].y) * (this->v[2].x - this->v[3].x);
			
			nx = (nx+nx2)/2;
			ny = (ny+ny2)/2;
			nz = (nz+nz2)/2;
			
		}*/
		float lenth = sqrt(pow(nx, 2) + pow(ny, 2) + pow(nz, 2));
		nx *= 10 / lenth;
		ny *= 10 / lenth;
		nz *= 10 / lenth;
		if (this->normalv.empty())
		{
			this->normalv.push_back(nx);
			this->normalv.push_back(ny);
			this->normalv.push_back(nz);
			/*std::cout << this->normalv[0]<<"n";
			std::cout << this->normalv[1] << "n";
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
	this->n = tris.n;
}
bool Face::operator==(Face tris)//NOT CHECKED
{
	if (this->v == tris.v)
		return true;
	else
		return false;
}
bool Face::operator!=(Face tris)//NOT CHECKED
{
	return !(*this == tris);
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
	os << "[" << e.p1 << "," << e.p2 << "]\n";
	return os;
}
std::ostream& operator<<(std::ostream& os, Face t)
{
	for (int i = 0; i <3; i++)
	{
		os << "(" << t.v[i].x << "," << t.v[i].y << "," << t.v[i].z << ")n";
	}
	/*os << "(" << t.v2.x << "," << t.v2.y << "," << t.v2.z << ")n";
	os << "(" << t.v3.x << "," << t.v3.y << "," << t.v3.z << ")n";*/
	return os;
}
std::ostream& operator<<(std::ostream& os, Object o)
{
	for (int i = 0; i < std::size(o.mesh); i++)
	{
		os << "tris " << i + 1 << "n";
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
		//this->vertex_normals_vis[i] = this->vertex_normals_vis[i] * koefficient;
	}
	for (int i = 0; i < std::size(this->border); i++)
	{
		this->border[i] = this->border[i] * koefficient;
	}
	for (int i = 0; i < std::size(this->points); i++)
	{
		this->points[i] = this->points[i] * koefficient;
	}
}
void swap(std::vector<Face> &tris, int pos1, int pos2)
{
	Face t1;
	t1=tris[pos1];
	tris[pos1] = tris[pos2];
	tris[pos2] = t1;
	//if (tris[pos1 or 2] is backwards): delete
	//else: previous thing 
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
				for (int k = 0; k < std::size(obj.mesh[obj.points[i].adjacent_tris[j]].v); k++)
				{
					if (vertex == "v"+std::to_string(k+1))
						obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v[k], obj.vertex_normals[i], light);
				}
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
	//is->color = sf::Color();

}
void Object::paint(sf::Color color)
{
	HEX col;
	col.create(color.r, color.g, color.b);
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		this->mesh[i].paint(col);
	}
	this->color.r = color.r;
	this->color.g = color.g;
	this->color.b = color.b;
	//this->mesh[100].paint("Red");
	
}
void Object::create(std::vector<Face> mesh, std::vector<Point> points)
{
	this->mesh = mesh;
	this->points = points;
	this->border = border_global;

	for (int i = 0; i < std::size(this->mesh); i++)
	{
		for (int j = 0; j < this->mesh[i].n; j++)
		{
			auto it = std::find(border_global.begin(), border_global.end(), this->mesh[i].borders[j]);
			this->mesh[i].borders[j].adjacentFaces = border_global[std::distance(border_global.begin(), it)].adjacentFaces;
;		}
	}

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
		/*this->vertex_normals_vis.push_back(e);
		e.clear();*/
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
	this->border = obj.border;
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
		//obj.vertex_normals_vis[i].rotate(angle);
		p.create(obj.vertex_normals[i][0], obj.vertex_normals[i][1], obj.vertex_normals[i][2]);
		p = p.rotate(angle, true);
		obj.vertex_normals[i][0] = p.x;
		obj.vertex_normals[i][1] = p.y;
		obj.vertex_normals[i][2] = p.z;
	}
	return obj;
}

Object Object::Subdivide(int i, std::string subd_type)
{
	border_global.clear();
	std::vector<Face> subdivided;
	std::vector<Point> pSbD;
	std::vector<std::vector<int>> vertices;
	std::vector<int> vertex;
	Face face;
	if (subd_type == "Catmull-Clark")
	{
		for (int i = 0; i < std::size(this->mesh); i++)
		{
			std::vector<Point> updatedVertex;
			std::vector<Point> edgePoint;
			Point facePoint;

			// MAKING VECTORS NOT EMPTY

			updatedVertex = std::vector<Point>(this->mesh[i].n);
			edgePoint = std::vector<Point>(this->mesh[i].n);

			// CALCULATE FACE POINT

			facePoint = this->mesh[i].center_point();
			int face_ind = std::size(pSbD);
			pSbD.push_back(facePoint);
			for (int j = 0; j < this->mesh[i].n; j++)
			{
				// CALCULATE UPDATED FIRST VERTEX AND EDGE POINT OF ONE EDGE
				updatedVertex[j] = this->updateVertex(this->mesh[i].v[j]);
				edgePoint[j] = this->calculateEdgePoint(this->mesh[i].borders[j]);// borders are badly sorted
				if (j == 0)
				{
					edgePoint[this->mesh[i].n-1] = this->calculateEdgePoint(this->mesh[i].borders[this->mesh[i].n-1]);
				}
				
				// MAKE UNIQUE
				
				auto it_vert = std::find(pSbD.begin(), pSbD.end(), updatedVertex[j]);
				if (it_vert == pSbD.end())
				{
					vertex.push_back(std::size(pSbD));
					pSbD.push_back(updatedVertex[j]);
				}
				else 
				{
					vertex.push_back(std::distance(pSbD.begin(), it_vert));
				}

				auto it_edge = std::find(pSbD.begin(), pSbD.end(), edgePoint[j]);
				if (it_edge == pSbD.end())
				{
					vertex.push_back(std::size(pSbD));
					pSbD.push_back(edgePoint[j]);
				}
				else
				{
					vertex.push_back(std::distance(pSbD.begin(), it_edge));
				}
				
				vertex.push_back(face_ind);
				if (j != 0)
				{
					auto it_edge = std::find(pSbD.begin(), pSbD.end(), edgePoint[j-1]);
					vertex.push_back(std::distance(pSbD.begin(), it_edge));
				}
				else
				{
					auto it_edge = std::find(pSbD.begin(), pSbD.end(), edgePoint[this->mesh[i].n - 1]);
					if (it_edge == pSbD.end())
					{
						vertex.push_back(std::size(pSbD));
						pSbD.push_back(edgePoint[this->mesh[i].n - 1]);
					}
					else
					{
						vertex.push_back(std::distance(pSbD.begin(), it_edge));
					}

					
				}	
				Face face;
				std::vector<Point*> pointz;
				for (int i = 0; i < std::size(vertex); i++)
				{
					pointz.push_back(&pSbD[vertex[i]]);
				}
				face.create(pointz, std::size(subdivided));
				pointz.clear();
				subdivided.push_back(face);
				vertex.clear();
			}
		}
	}
	else if (subd_type == "Linear")
	{
		for (int i = 0; i < std::size(this->mesh); i++)
		{
			std::vector<Point> updatedVertex;
			std::vector<Point> edgePoint;
			Point facePoint;

			// MAKING VECTORS NOT EMPTY

			updatedVertex = std::vector<Point>(this->mesh[i].n);
			edgePoint = std::vector<Point>(this->mesh[i].n);

			// CALCULATE FACE POINT

			facePoint = this->mesh[i].center_point();
			int face_ind = std::size(pSbD);
			pSbD.push_back(facePoint);
			for (int j = 0; j < this->mesh[i].n; j++)
			{
				// CALCULATE UPDATED FIRST VERTEX AND EDGE POINT OF ONE EDGE
				updatedVertex[j] = this->mesh[i].v[j];
				updatedVertex[j].adjacent_tris.clear();
				updatedVertex[j].tripoints.clear();
				edgePoint[j] = this->mesh[i].borders[j].center();
				edgePoint[j].adjacent_tris.clear();
				edgePoint[j].tripoints.clear();
				if (j == 0)
				{
					edgePoint[this->mesh[i].n - 1] = this->mesh[i].borders[this->mesh[i].n - 1].center();
					edgePoint[this->mesh[i].n - 1].adjacent_tris.clear();
					edgePoint[this->mesh[i].n - 1].tripoints.clear();
				}

				// MAKE UNIQUE

				auto it_vert = std::find(pSbD.begin(), pSbD.end(), updatedVertex[j]);
				if (it_vert == pSbD.end())
				{
					vertex.push_back(std::size(pSbD));
					pSbD.push_back(updatedVertex[j]);
				}
				else
				{
					vertex.push_back(std::distance(pSbD.begin(), it_vert));
				}

				auto it_edge = std::find(pSbD.begin(), pSbD.end(), edgePoint[j]);
				if (it_edge == pSbD.end())
				{
					vertex.push_back(std::size(pSbD));
					pSbD.push_back(edgePoint[j]);
				}
				else
				{
					vertex.push_back(std::distance(pSbD.begin(), it_edge));
				}

				vertex.push_back(face_ind);
				if (j != 0)
				{
					auto it_edge = std::find(pSbD.begin(), pSbD.end(), edgePoint[j - 1]);
					vertex.push_back(std::distance(pSbD.begin(), it_edge));
				}
				else
				{
					auto it_edge = std::find(pSbD.begin(), pSbD.end(), edgePoint[this->mesh[i].n - 1]);
					if (it_edge == pSbD.end())
					{
						vertex.push_back(std::size(pSbD));
						pSbD.push_back(edgePoint[this->mesh[i].n - 1]);
					}
					else
					{
						vertex.push_back(std::distance(pSbD.begin(), it_edge));
					}


				}
				Face face;
				std::vector<Point*> pointz;
				for (int i = 0; i < std::size(vertex); i++)
				{
					pointz.push_back(&pSbD[vertex[i]]);
				}
				face.create(pointz, std::size(subdivided));
				pointz.clear();
				subdivided.push_back(face);
				vertex.clear();
			}
		}
	}
	else if (subd_type == "Doo-Sabin")//ADD THE HOLE 
	{
		int amount_of_polys=std::size(this->mesh)+std::size(this->points)+std::size(this->border);
		for (int i = 0; i < std::size(this->mesh); i++)//CALCULATING FACE SHRINKING
		{
			std::vector<int> vertex(std::size(this->mesh[i].v));
			Point new_v;
			for (int j = 0; j < std::size(this->mesh[i].v); j++)
			{
				new_v.middle(this->mesh[i].v[j], this->mesh[i].center_point());
				pSbD.push_back(new_v);
				vertex[j] = std::size(pSbD) - 1;
			}
			vertices.push_back(vertex);
		}
		for (int i = 0; i < std::size(this->points); i++)//CALCULATING POINT SUBDIVISION
		{
			std::vector<int> vertex(std::size(this->points[i].adjacent_tris));
			Point new_v;
			for (int j = 0; j < std::size(this->points[i].adjacent_tris); j++)
			{
				new_v.middle(this->points[i],this->mesh[this->points[i].adjacent_tris[j]].center_point());
				auto it = std::find(pSbD.begin(), pSbD.end(), new_v);
				int index = std::distance(pSbD.begin(), it);
				vertex[j] = index;
			}
			//SORT CLOCKWISE
			std::vector<Point> vs(std::size(vertex));
			for (int j = 0; j < std::size(vertex); j++)
			{
				vs[j] = pSbD[vertex[j]];
			}
			sort_clockwise(vs, vertex);
			vs.clear();
			vertices.push_back(vertex);
		}
		for (int i = 0; i < std::size(this->border); i++)//CALCULATING EDGE SUBDIVISION
		{
			std::vector<int> vertex(4);
			Point new_v;
			//vertex.clear();
			if (std::size(this->border[i].adjacentFaces) == 2)
			{
				//FIRST POINT - FIRST FACE
				new_v.middle(this->border[i].p2, this->mesh[this->border[i].adjacentFaces[0]].center_point());
				auto it = std::find(pSbD.begin(), pSbD.end(), new_v);
				int index = std::distance(pSbD.begin(), it);
				vertex[0] = index;
				//SECOND POINT - FIRST FACE
				new_v.middle(this->border[i].p1, this->mesh[this->border[i].adjacentFaces[0]].center_point());
				it = std::find(pSbD.begin(), pSbD.end(), new_v);
				index = std::distance(pSbD.begin(), it);
				vertex[1] = index;
				//SECOND POINT - SECOND FACE
				new_v.middle(this->border[i].p1, this->mesh[this->border[i].adjacentFaces[1]].center_point());
				it = std::find(pSbD.begin(), pSbD.end(), new_v);
				index = std::distance(pSbD.begin(), it);
				vertex[2] = index;
				//FIRST POINT - SECOND FACE
				new_v.middle(this->border[i].p2, this->mesh[this->border[i].adjacentFaces[1]].center_point());
				it = std::find(pSbD.begin(), pSbD.end(), new_v);
				index = std::distance(pSbD.begin(), it);
				vertex[3] = index;
			}
			vertices.push_back(vertex);
		}
		for (int i = 0; i < std::size(this->mesh)+ std::size(this->border)+ std::size(this->points); i++)
		{
			Face face;
			std::vector<Point*> pointz;
			for (int j = 0; j < std::size(vertices[i]); j++)
			{
				pointz.push_back(&pSbD[vertices[i][j]]);
			}
			face.create(pointz, std::size(subdivided));
			pointz.clear();
			subdivided.push_back(face);

		}
	}
	
	Object obj;
	obj.create(subdivided, pSbD);
	obj.color = this->color;
	obj.paint(this->color);
	//obj.paint("Green");
	return obj;
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

Point Object::calculateEdgePoint(Edge e)//NOT TESTED
{
	e.p1.adjacent_tris.clear();
	e.p2.adjacent_tris.clear();
	e.p1.tripoints.clear();
	e.p2.tripoints.clear();
	std::vector<Edge>::iterator it = std::find(this->border.begin(), this->border.end(),e);
	int k = std::distance(this->border.begin(), it);
	Point endPoint1, endPoint2, facePoint1, facePoint2, edgePoint;
	endPoint1 = e.p1;
	endPoint2 = e.p2;
	if (it != this->border.end()) {
		if (std::size(this->border[k].adjacentFaces) == 2) 
		{
			facePoint1 = this->mesh[this->border[k].adjacentFaces[0]].center_point();
			facePoint2 = this->mesh[this->border[k].adjacentFaces[1]].center_point();
			edgePoint = (endPoint1 + endPoint2 + facePoint1 + facePoint2) / 4;
		}
		else
		{
			
			edgePoint = (endPoint1 + endPoint2) / 2;

		}
	}
	
	return edgePoint;
}

Point Object::calculateFacePoint(Edge e,Face f)
{
	Point facePoint;
	bool found = false;
	int i = 0;
	while (!found)
	{
		for(int j=0;j<std::size(mesh[i].borders);j++)
			if ((e == this->mesh[i].borders[j])&&(this->mesh[i]!=f))
			{
				found = true;
			}
		i++;
	}

	return this->mesh[i-1].center_point();
}

Point Object::updateVertex(Point v)
{
	//std::vector<Edge> adjEdge;
	std::vector<Point> edgePoint;
	std::vector<Point> facePoint;
	Point result;
	Point vertex;
	int adjEdges=0;

	
	auto it = std::find(this->points.begin(), this->points.end(), v);
	int k = std::distance(this->points.begin(), it);
	vertex = this->points[k];
	std::vector<Edge>::iterator adjEdg = std::find_if(this->border.begin(), this->border.end(), std::bind(Edge::contains, std::placeholders::_1, v));
	std::vector<std::vector<Edge>::iterator> iterEdges;
	while (adjEdg != this->border.end())
	{
		//std::cout << *adjEdg;
		iterEdges.push_back(adjEdg);
		adjEdg = std::find_if(adjEdg+1, this->border.end(), std::bind(Edge::contains, std::placeholders::_1, v));
		adjEdges++;
	}
	//std::cout << "\n";
	if (adjEdges != std::size(vertex.adjacent_tris))
	{
		//std::cout << "0\n";
		
		for (int i = 0; i < std::size(iterEdges); i++)
		{
			adjEdges = std::distance(this->border.begin(), iterEdges[i]);
			if (std::size(this->border[adjEdges].adjacentFaces) == 1) 
			{
				
				Point p = this->calculateEdgePoint(this->border[adjEdges]);
				result = result + p;
			}
			
		}
		result = result + vertex;
		result = result / 3;
	}
	else {

		for (int i = 0; i < std::size(vertex.adjacent_tris); i++)
		{
			for (int j = 0; j < this->mesh[vertex.adjacent_tris[i]].n; j++)
			{
				if ((this->mesh[vertex.adjacent_tris[i]].borders[j].p1 == vertex) ||
					(this->mesh[vertex.adjacent_tris[i]].borders[j].p2 == vertex))
				{
					Point p = this->calculateEdgePoint(this->mesh[vertex.adjacent_tris[i]].borders[j]);
					auto it2 = std::find(edgePoint.begin(), edgePoint.end(), p);
					k = std::distance(edgePoint.begin(), it2);
					if (it2 == edgePoint.end())
					{
						edgePoint.push_back(p);
					}
					//result = result + edgePoint;
				}
			}
			facePoint.push_back(this->mesh[vertex.adjacent_tris[i]].center_point());
			//result = result + this->mesh[vertex.adjacent_tris[i]].center_point();
		}

		int l = std::size(vertex.adjacent_tris) - 3;
		if (l < 0)
		{
			result.clear();
			for (int i = 0; i < l; i++)
				result = result + this->mesh[vertex.adjacent_tris[i]].center_point();
			result = (result + vertex) / 2;
		}
		else
		{
			Point face, edge, vert;
			for (int i = 0; i < std::size(edgePoint); i++)
			{
				edge = edge + edgePoint[i] / std::size(edgePoint);
				face = face + facePoint[i] / std::size(edgePoint);
			}
			vert = vertex * l;
			result = (edge * 2 + face + vert) / std::size(vertex.adjacent_tris);
		}
		/*if (l == 0)
		{
			result = (result + vertex*0.75) / 2;
		}*/
	}
	return result;
}
