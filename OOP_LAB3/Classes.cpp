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
	std::cout << "\n";
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

float POINT::distance(POINT a, POINT b)
{
	return sqrt(pow((a.x-b.x),2)+ pow((a.y - b.y), 2)+ pow((a.z - b.z), 2));
}

float POINT::distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void POINT::middle(POINT a, POINT b)
{
	this->x = (a.x + b.x) / 2;
	this->y = (a.y + b.y) / 2;
	this->z = (a.z + b.z) / 2;
	this->initialized = true;
}
void POINT::create(float a, float b,float c)
{
	this->x = a;
	this->y = b;
	this->z = c;
	this->initialized = true;
}
void POINT::clear()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->initialized = false;
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
	this->initialized = d.initialized;
	this->r_angle = d.r_angle;
	this->adjacent_tris = d.adjacent_tris;
	this->color = d.color;
	this->tripoints = d.tripoints;
}

bool POINT::operator==(POINT p)
{
	return this->x==p.x&& this->y == p.y;
}


POINT POINT::operator*(float k)
{
	
	this->x = this->x* k;
	this->y = this->y* k;
	this->z = this->z* k;
	return *this;
}
float POINT::angle(std::vector<float> vec2)
{
	std::vector<float> vec1 = this->normalv;
	float angle = std::acos((vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]) / (sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)) * sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2))));
	return angle;
}
void POINT::lightness(float l)
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

POINT POINT::operator-(POINT b)
{
	POINT a;
	a.create(this->x-b.x,this->y-b.y,this->z-b.z);
	a.initialized = this->initialized;
	return a;
}
bool POINT::null()
{
	return this->x == 0&& this->y == 0;
}
bool POINT::compare_x(POINT p1,POINT p2)
{
	return p1.x<p2.x;
}

POINT POINT::rotate(float angles,bool is3d)
{
	this->r_angle = angles;
	float angle = to_rads(angles);

	POINT vr;
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
		POINT nr;
		nr.create(this->normalv[0], this->normalv[1], this->normalv[2]);
		nr.rotate(angles);
		vr.normalv.push_back(nr.x);
		vr.normalv.push_back(nr.y);
		vr.normalv.push_back(nr.z);
	}*/
	return vr;
}

std::vector<float> POINT::vector(POINT A)
{

	POINT v;
	v = *this - A;
	std::vector<float> vec;
	vec.push_back(v.x);
	vec.push_back(v.y);
	vec.push_back(v.z);
	return vec;
}

void POINT::Gouraud(POINT& v1, std::vector<float> normalv, POINT light)
{
	this->normalv = normalv;
	float rad = this->angle(v1.vector(light));
	this->lightness(rad / 3.14159265359);
	v1.lightness(rad / 3.14159265359);

}





void EDGE::create(POINT a, POINT b)
{
	this->p1=a;
	this->p2=b;
}
void EDGE::create(POINT a, std::vector<float> normalv)
{
	this->p1 = a;
	POINT b;
	b.create(normalv[0]+a.x, normalv[1] + a.y, normalv[2] + a.z);
	this->p2 = b;
}
void EDGE::create(float x1, float y1, float x2, float y2)
{
	POINT a;
	a.create(x1,y1);
	this->p1 = a;
	a.create(x2, y2);
	this->p2 = a;
}
void EDGE::clear()
{
	this->p1.clear();
	this->p2.clear();
}
void EDGE::draw(sf::RenderWindow& window) 
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
void EDGE::draw_3d(sf::RenderWindow& window) const
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
	window.draw(line, 2, sf::Lines);
}
void EDGE::rotate(float angle)
{
	this->p1=this->p1.rotate(angle, true);
	this->p2=this->p2.rotate(angle, true);

}
void EDGE::operator=(EDGE e)
{
	this->p1 = e.p1;
	this->p2 = e.p2; 
	this->s1 = e.s1;
	this->s2 = e.s2;
}

EDGE EDGE::operator*(float k)
{
	this->p1 = this->p1 * k;
	this->p2 = this->p2 * k;
	return *this;
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
void TRIANGLE::draw_3d(sf::RenderWindow& window, POINT light, bool islit, bool gouraud)
{
	
	float Lens = 1000;
	float k1, k2, k3;
	k1 = exp(this->v1.z / Lens);
	k2 = exp(this->v2.z / Lens);
	k3 = exp(this->v3.z / Lens);
	if (!gouraud) 
	{
		sf::ConvexShape convex;
		convex.setPointCount(3);
		convex.setPoint(0, sf::Vector2f(this->v1.x * k1, -this->v1.y * k1));
		convex.setPoint(1, sf::Vector2f(this->v2.x * k2, -this->v2.y * k2));
		convex.setPoint(2, sf::Vector2f(this->v3.x * k3, -this->v3.y * k3));
		this->normal(true);
		if (islit)
		{
			float rad = this->angle(this->center_point().vector(light));
			this->lightness(rad / 3.14159265359);
		}
		convex.setFillColor(this->color);

		window.draw(convex);

		/*if (normal_visible)
		{
			EDGE n;
			n.create(this->center_point(), this->normal());
			n.draw_3d(window);

		}*/
	}
	else
	{
		sf::VertexArray triangle(sf::Triangles, 3);

		// define the position of the triangle's points
		triangle[0].position = sf::Vector2f(this->v1.x * k1, -this->v1.y * k1);
		triangle[1].position = sf::Vector2f(this->v2.x * k2, -this->v2.y * k2);
		triangle[2].position = sf::Vector2f(this->v3.x * k3, -this->v3.y * k3);

		// define the color of the triangle's points
		triangle[0].color = this->v1.color;
		triangle[1].color = this->v2.color;
		triangle[2].color = this->v3.color;
		window.draw(triangle);
	}
	
	
	

}
void TRIANGLE::scale_this(float lambda)
{
	POINT cen;
	cen = this->center_point();

	this->v1.x = (this->v1.x + lambda * cen.x) / (1 + lambda);
	this->v1.y = (this->v1.y + lambda * cen.y) / (1 + lambda);
	this->v1.z = (this->v1.z + lambda * cen.z) / (1 + lambda);

	this->v2.x = (this->v2.x + lambda * cen.x) / (1 + lambda);
	this->v2.y = (this->v2.y + lambda * cen.y) / (1 + lambda);
	this->v2.z = (this->v2.z + lambda * cen.z) / (1 + lambda);

	this->v3.x = (this->v3.x + lambda * cen.x) / (1 + lambda);
	this->v3.y = (this->v3.y + lambda * cen.y) / (1 + lambda);
	this->v3.z = (this->v3.z + lambda * cen.z) / (1 + lambda);
}
TRIANGLE TRIANGLE::scale(float lambda)
{
	TRIANGLE tris = *this;
	POINT cen;
	cen = this->center_point();

	tris.v1.x = (this->v1.x + lambda * cen.x) / (1 + lambda);
	tris.v1.y = (this->v1.y + lambda * cen.y) / (1 + lambda);
	tris.v1.z = (this->v1.z + lambda * cen.z) / (1 + lambda);

	tris.v2.x = (this->v2.x + lambda * cen.x) / (1 + lambda);
	tris.v2.y = (this->v2.y + lambda * cen.y) / (1 + lambda);
	tris.v2.z = (this->v2.z + lambda * cen.z) / (1 + lambda);

	tris.v3.x = (this->v3.x + lambda * cen.x) / (1 + lambda);
	tris.v3.y = (this->v3.y + lambda * cen.y) / (1 + lambda);
	tris.v3.z = (this->v3.z + lambda * cen.z) / (1 + lambda);
	return tris;
}
void TRIANGLE::create(POINT v1, POINT v2, POINT v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
}
void TRIANGLE::create(POINT& v1, POINT& v2, POINT& v3, int tris_index)
{
	v1.adjacent_tris.push_back(tris_index);
	v2.adjacent_tris.push_back(tris_index);
	v3.adjacent_tris.push_back(tris_index);
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	v1.tripoints[tris_index] = "v1";
	v2.tripoints[tris_index] = "v2";
	v3.tripoints[tris_index] = "v3";
	//std::cout << v3.tripoints[tris_index];
}
float TRIANGLE::center()
{
	if (!this->centroid.initialized) 
	{
		POINT centre;
		centre.create((this->v1.x + this->v2.x + this->v3.x) / 3.0, (this->v1.y + this->v2.y + this->v3.y) / 3.0, (this->v1.z + this->v2.z + this->v3.z) / 3.0);
		this->centroid = centre;
	}
	
	return this->centroid.z;
}

POINT TRIANGLE::center_point()
{
	if (!this->centroid.initialized)
	{
		POINT centre;
		centre.create((this->v1.x + this->v2.x + this->v3.x) / 3.0, (this->v1.y + this->v2.y + this->v3.y) / 3.0, (this->v1.z + this->v2.z + this->v3.z) / 3.0);
		this->centroid = centre;
	}
	return this->centroid;
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
	this->v1.color = sf::Color(color.red, color.green, color.blue);
	this->v2.color = sf::Color(color.red, color.green, color.blue);
	this->v3.color = sf::Color(color.red, color.green, color.blue);
}
void TRIANGLE::lightness(float l)
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
TRIANGLE TRIANGLE::rotate(float angle)
{
	TRIANGLE tris;
	tris.create
	(
		this->v1.rotate(angle, true),
		this->v2.rotate(angle, true),
		this->v3.rotate(angle, true)
	);
	tris.normalv = this->normalv;
	this->r_angle = angle;
	tris.color = this->color;
	return tris;
}

std::vector<float> TRIANGLE::normal(bool update)
{
	float nx, ny, nz;
	if (update)
	{
		
		nx = (this->v2.y - this->v1.y) * (this->v3.z - this->v1.z) - (this->v2.z - this->v1.z) * (this->v3.y - this->v1.y);
		ny = (this->v2.z - this->v1.z) * (this->v3.x - this->v1.x) - (this->v2.x - this->v1.x) * (this->v3.z - this->v1.z);
		nz = (this->v2.x - this->v1.x) * (this->v3.y - this->v1.y) - (this->v2.y - this->v1.y) * (this->v3.x - this->v1.x);
		float lenth = sqrt(pow(nx, 2) + pow(ny, 2) + pow(nz, 2));
		nx *= 10 / lenth;
		ny *= 10 / lenth;
		nz *= 10 / lenth;
		if (this->normalv.empty())
		{
			this->normalv.push_back(nx);
			this->normalv.push_back(ny);
			this->normalv.push_back(nz);
			/*std::cout << this->normalv[0]<<"\n";
			std::cout << this->normalv[1] << "\n";
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

void TRIANGLE::operator=(TRIANGLE tris)
{
	this->border_color = tris.border_color;
	this->color = tris.color;
	this->v1 = tris.v1;
	this->v2 = tris.v2;
	this->v3 = tris.v3;
	this->border_width = tris.border_width;
	this->centroid = tris.centroid;
	this->normalv = tris.normalv;
	this->r_angle = tris.r_angle;
}

TRIANGLE TRIANGLE::operator*(float k)
{
	this->v1 = this->v1 * k;
	this->v2 = this->v2 * k;
	this->v3 = this->v3 * k;
	return *this;
}


float TRIANGLE::angle(std::vector<float> vec2)
{
	std::vector<float> vec1 = this->normalv;
	float angle = std::acos((vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]) / (sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)) * sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2))));
	return angle;
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
std::ostream& operator<<(std::ostream& os, TRIANGLE t)
{
	os << "(" << t.v1.x << "," << t.v1.y << "," << t.v1.z << ")\n";
	os << "(" << t.v2.x << "," << t.v2.y << "," << t.v2.z << ")\n";
	os << "(" << t.v3.x << "," << t.v3.y << "," << t.v3.z << ")\n";
	return os;
}
std::ostream& operator<<(std::ostream& os, OBJECT o)
{
	for (int i = 0; i < std::size(o.mesh); i++)
	{
		os << "tris " << i + 1 << "\n";
		os << o.mesh[i];
	}
	return os;
}

void OBJECT::scale(float koefficient)
{
	
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		this->mesh[i] = this->mesh[i] * koefficient;
		
		if (!this->border.empty())
		{
			this->border[i] = this->border[i] * koefficient;
		}
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
void swap(std::vector<TRIANGLE>& tris, int pos1, int pos2)
{
	TRIANGLE t1;
	t1=tris[pos1];
	tris[pos1] = tris[pos2];
	tris[pos2] = t1;
}
int partition(std::vector<TRIANGLE>& tris, int low, int high)
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
void quickSort(std::vector<TRIANGLE>& tris, int low, int high)
{
	if (low < high)
	{
		int pi = partition(tris, low, high);
		quickSort(tris, low, pi - 1);
		quickSort(tris, pi + 1, high);
	}
}

int partition2(std::vector<TRIANGLE>& tris, std::vector<TRIANGLE>& border, int low, int high)
{
	float pivot = tris[high].center();

	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (tris[j].center() < pivot)
		{
			i++;
			swap(tris, i, j);
			swap(border, i, j);
		}
	}
	swap(tris, i + 1, high);
	swap(border, i + 1, high);
	return (i + 1);
}
void quickSort2(std::vector<TRIANGLE>& tris, std::vector<TRIANGLE>& border, int low, int high)
{
	if (low < high)
	{
		int pi = partition2(tris,border, low, high);
		quickSort2(tris, border, low, pi - 1);
		quickSort2(tris, border, pi + 1, high);
	}
}

void OBJECT::draw(sf::RenderWindow& window, POINT light, bool islit, bool normal_visible, float angle, bool gouraud)
{
	
	OBJECT obj;
	obj = this->rotate(angle);
	
	if (obj.border.empty())
	{

		//PAINT
		if (gouraud) 
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
					{
						obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v1, obj.vertex_normals[i], light);
					}
					if (vertex == "v2")
					{
						obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v2, obj.vertex_normals[i], light);
					}
					if (vertex == "v3")
					{
						obj.points[i].Gouraud(obj.mesh[obj.points[i].adjacent_tris[j]].v3, obj.vertex_normals[i], light);
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
			obj.mesh[i].draw_3d(window, light, islit, gouraud);
		}
		if (normal_visible)
		{
			for (int i = 0; i < std::size(obj.vertex_normals); i++)
			{

				EDGE n;
				n.create(obj.points[i], obj.vertex_normals[i]);
				n.draw_3d(window);
			}
		}
		
	}
	else
	{
		quickSort2(obj.mesh,obj.border, 0, std::size(obj.mesh) - 1);
		for (int i = 0; i < std::size(obj.mesh); i++)
		{
			obj.mesh[i].draw_3d(window, light, normal_visible, islit);
			obj.border[i].draw_3d(window, light, normal_visible, islit);
		}
	}
}

void OBJECT::renderInHalfs(sf::RenderWindow& window, POINT light)
{
	quickSort(this->mesh, 2*(std::size(this->mesh)/3), std::size(this->mesh) - 1);
	for (int i = 2 * (std::size(this->mesh) / 3); i < std::size(this->mesh); i++)
	{
		this->mesh[i].draw_3d(window, light);
	}
}

void OBJECT::create_hard_mode(std::vector<TRIANGLE> mesh)
{
	std::vector<TRIANGLE> border;
	this->mesh = mesh;
	for (int i = 0; i < std::size(mesh); i++)
	{
		border.push_back(mesh[i].scale(0.2));
		if (i % 2)
			border[i].paint("Green");
		else
			border[i].paint("Blue");
	}
	this->border = border;
}
void OBJECT::paint(HEX color)
{
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		this->mesh[i].paint(color);
	}
	this->color.r = color.red;
	this->color.g = color.green;
	this->color.b = color.blue;
}
void OBJECT::create(std::vector<TRIANGLE> mesh, std::vector<POINT> point)
{
	this->mesh = mesh;
	this->points = point;


	std::vector<float> vertex_normal = { 0,0,0 };
	std::vector<float> tris_normal = { 0,0,0 };
	float lenth;
	EDGE e;
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
void OBJECT::operator=(std::vector<TRIANGLE> mesh)
{
	this->mesh = mesh;
}

void OBJECT::operator=(OBJECT obj)
{
	this->mesh = obj.mesh;
	this->points = obj.points;
	this->vertex_normals = obj.vertex_normals;
	this->vertex_normals_vis = obj.vertex_normals_vis;

	this->border = obj.border;
	this->r_angle = obj.r_angle;
	this->sorted = obj.sorted;
	this->color = obj.color;

}

OBJECT OBJECT::rotate(float angle)
{
	/*OBJECT o;
	this->r_angle = angle;
	std::vector<TRIANGLE> trises;
	if (this->border.empty())
	{
		for (int i = 0; i < std::size(this->mesh); i++) {
			trises.push_back(this->mesh[i].rotate(angle));
		}
	}
	else
	{
		for (int i = 0; i < std::size(this->mesh); i++) {
			trises.push_back(this->mesh[i].rotate(angle));
			trises.push_back(this->border[i].rotate(angle));
		}
	}
	o = trises;*/
	OBJECT obj;
	POINT p;

	obj = *this;
	if (obj.border.empty())
	{
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
	}
	/*else
	{
		for (int i = 0; i < std::size(this->mesh); i++) {
			trises.push_back(this->mesh[i].rotate(angle));
			trises.push_back(this->border[i].rotate(angle));
		}
	}*/
	return obj;
}