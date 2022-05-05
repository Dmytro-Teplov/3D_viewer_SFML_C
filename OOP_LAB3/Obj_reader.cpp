#include "Obj_reader.h"

void show(std::vector<std::vector<float>> A)
{
	for (int i = 0; i < std::size(A); i++)
	{
		for (int j = 0; j < std::size(A[i]); j++)
		{
			std::cout << A[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
void show(std::vector<std::vector<int>> A)
{
	for (int i = 0; i < std::size(A); i++)
	{
		for (int j = 0; j < std::size(A[i]); j++)
		{
			std::cout << A[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
Point parse_point(std::string text,char divider)
{
	int vertex_count = 3;
	std::vector<float> xyz;
	std::string number="";
	int i = 2;
	for (int j = 0;std::size(xyz)< vertex_count; j++)
	{
		while (text[i] != divider && i < std::size(text))
		{
			number += std::string(1, text[i]);
			i++;
		}
		if(number!="")
			xyz.push_back(std::stof(number));
		number.clear();
		i++;
	}
	Point p;
	p.create(xyz[0],xyz[1],xyz[2]);
	return p;
}
std::vector<std::vector<int>> parse_face(std::string text)
{
	int vertex_count = 3;
	std::vector<std::vector<int>> face;
	std::vector<int> vertex;
	std::string number="";
	int i = 2;
	while (i <= std::size(text))
		{
			
			if (text[i] == ' '|| i >= std::size(text))
			{
				if (number != "")
					vertex.push_back(std::stof(number));

				else
					vertex.push_back(0);
				face.push_back(vertex);
				vertex.clear();
				number = "";
				
			}else if (text[i] == '/')
			{
				if (number != "")
					vertex.push_back(std::stof(number));

				else
					vertex.push_back(0);
				number = "";
				if(text[i-1] == '/')
					i++;
			}
			else
			{
				number += std::string(1, text[i]);
			}
			
			i++;
	}
		//face.push_back(vertex);
		//vertex.clear();
	i++;
	
	return face;
}
Object reading(std::string filename)
{
	std::vector<Face> mesh;
	std::string text;
	std::ifstream myfile;
	std::vector<std::vector<int>> vertices;
	myfile.open(filename);
	
	std::vector<Point> v;
	std::vector<Point> vt;
	std::vector<Point> vn;
	Face tris;
	std::vector<Face> f;
	while (getline(myfile, text))
	{
		if (text[0] == 'v' && text[1] == ' ')
		{
			v.push_back(parse_point(text, ' '));
		}
		if (text[0] == 'v' && text[1] == 'n' && text[2] == ' ')
		{
			vn.push_back(parse_point(text, ' '));
		}
		if (text[0] == 'v' && text[1] == 't' && text[2] == ' ')
		{
			vt.push_back(parse_point(text, ' '));
		}
		if (text[0] == 'f' && text[1] == ' ')
		{
			vertices = parse_face(text);
			if (std::size(vertices)==3)
				tris.create(v[vertices[0][0] - 1], v[vertices[1][0] - 1], v[vertices[2][0] - 1], std::size(f));
			else if(std::size(vertices) == 4)
				tris.create(v[vertices[0][0] - 1], v[vertices[1][0] - 1], v[vertices[2][0] - 1], v[vertices[3][0] - 1], std::size(f));
			f.push_back(tris);
		}
	}
	Object obj;
	obj.create(f,v);
	//mesh = f;
	myfile.close();
	return obj;
}