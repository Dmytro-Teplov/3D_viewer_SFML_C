#include "Classes.h"
double to_rads(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
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
	
	this->x = this->x* k;
	this->y = this->y* k;
	this->z = this->z* k;
	return *this;
}
bool POINT::null()
{
	return this->x == 0&& this->y == 0;
}
bool POINT::compare_x(POINT p1,POINT p2)
{
	return p1.x<p2.x;
}

void POINT::rotate(float angle,bool is3d)
{
	float x = this->x;
	float y;
	if (is3d) 
	{
		y = this->z;
	}
	else 
	{
		y = this->y;
	}
	angle = to_rads(angle);
	float r2 = pow(x, 2) + pow(y, 2);
	float k;
	if (x != 0)
		k = y / x;
	else
		k = y;
	float k_new = tan(atan(k)+angle);
	float D = (1 + pow(k_new, 2)) * r2;
	float x_new1 = sqrt(D) / ((1 + pow(k_new, 2)));
	float x_new2 = -sqrt(D) / ((1 + pow(k_new, 2)));
	float y_new1 = k_new * x_new1;
	float y_new2 = k_new * x_new2;
	/*std::cout << k<<" ";
	std::cout << k_new<<" ";
	std::cout << x_new1<<" ";
	std::cout << y_new1<<"\n";*/
	if (POINT::distance(x, y, x_new1, y_new1) < POINT::distance(x, y, x_new2, y_new2))
	{
		this->x = x_new1;
		if (is3d)
		{
			this->z = y_new1;
		}
		else
		{
			this->y = y_new1;
		}
	}
	else
	{
		this->x = x_new2;
		if (is3d)
		{
			this->z = y_new2;
		}
		else
		{
			this->y = y_new2;
		}
	}
}

void EDGE::create(POINT a, POINT b)
{
	this->p1=a;
	this->p2=b;
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
void EDGE::draw(sf::RenderWindow& window) const
{
	float margin = 2;
	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(this->p1.x + margin, this->p1.y);
	quad[1].position = sf::Vector2f(this->p1.x - margin, this->p1.y);
	quad[2].position = sf::Vector2f(this->p2.x + margin, this->p2.y);
	quad[3].position = sf::Vector2f(this->p2.x - margin, this->p2.y);
	window.draw(quad);
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
	float Lens = 1000;
	float k1, k2, k3;
	k1 = exp(this->v1.z / Lens);
	k2 = exp(this->v2.z / Lens);
	k3 = exp(this->v3.z / Lens);
	convex.setPoint(0, sf::Vector2f(this->v1.x * k1, -this->v1.y * k1));
	convex.setPoint(1, sf::Vector2f(this->v2.x * k2, -this->v2.y * k2));
	convex.setPoint(2, sf::Vector2f(this->v3.x * k3, -this->v3.y * k3));
	convex.setFillColor(this->color);
	window.draw(convex);
}
void TRIANGLE::scale_this(float lambda)
{
	POINT cen;
	cen = this->center(true);

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
	cen = this->center(true);

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
float TRIANGLE::center() const
{
	POINT centroid;
	centroid.create((this->v1.x + this->v2.x + this->v3.x)/3.0, (this->v1.y + this->v2.y + this->v3.y) / 3.0, (this->v1.z + this->v2.z + this->v3.z) / 3.0);
	return centroid.z;
}
POINT TRIANGLE::center(bool is2d)
{
	POINT centroid;
	centroid.create((this->v1.x + this->v2.x + this->v3.x) / 3.0, (this->v1.y + this->v2.y + this->v3.y) / 3.0, (this->v1.z + this->v2.z + this->v3.z) / 3.0);
	return centroid;
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

void TRIANGLE::rotate(float angle)
{
	this->v1.rotate(angle, true);
	this->v2.rotate(angle, true);
	this->v3.rotate(angle, true);
}

void TRIANGLE::operator=(TRIANGLE tris)
{
	this->border_color = tris.border_color;
	this->color = tris.color;
	this->v1 = tris.v1;
	this->v2 = tris.v2;
	this->v3 = tris.v3;
	this->border_width = tris.border_width;
}

TRIANGLE TRIANGLE::operator*(float k)
{
	this->v1 = this->v1 * k;
	this->v2 = this->v2 * k;
	this->v3 = this->v3 * k;
	return *this;
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
	int pivot = tris[high].center();
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
	int pivot = tris[high].center();
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

void OBJECT::draw(sf::RenderWindow& window)
{
	if (this->border.empty())
	{
		quickSort(this->mesh, 0, std::size(this->mesh) - 1);
		for (int i = 0; i < std::size(this->mesh); i++)
		{
			this->mesh[i].draw_3d(window);
		}
	}
	else
	{
		quickSort2(this->mesh,this->border, 0, std::size(this->mesh) - 1);
		for (int i = 0; i < std::size(this->mesh); i++)
		{
			this->mesh[i].draw_3d(window);
			this->border[i].draw_3d(window);
		}
	}
	
}

void OBJECT::renderInHalfs(sf::RenderWindow& window)
{
	quickSort(this->mesh, 2*(std::size(this->mesh)/3), std::size(this->mesh) - 1);
	for (int i = 2 * (std::size(this->mesh) / 3); i < std::size(this->mesh); i++)
	{
		this->mesh[i].draw_3d(window);
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

void OBJECT::operator=(std::vector<TRIANGLE> mesh)
{

	this->mesh = mesh;
	for (int i = 0; i < std::size(this->mesh); i++)
	{
		if (i % 2)
			this->mesh[i].paint("Green");
		else
			this->mesh[i].paint("Blue");
	}
}

void OBJECT::rotate(float angle)
{
	if (this->border.empty())
	{
		for (int i = 0; i < std::size(this->mesh); i++) {
			this->mesh[i].rotate(angle);
		}
	}
	else
	{
		for (int i = 0; i < std::size(this->mesh); i++) {
			this->mesh[i].rotate(angle);
			this->border[i].rotate(angle);
		}
	}

	
}
