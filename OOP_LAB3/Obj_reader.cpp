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
std::vector<TRIANGLE> reading(std::string filename)
{
	std::vector<TRIANGLE> mesh;
	std::string text;
	std::string number="";
	std::ifstream myfile;
	float x;
	float y;
	float z;
	std::vector<std::vector<float>> coords;
	std::vector<std::vector<int>> vertices;
	std::vector<float> xyz;
	std::vector<int> vert;
	myfile.open(filename);
	int k = 0;
	int i = 2;
	while (getline(myfile, text)) 
	{
		if (text[0]=='v'&& text[1] == ' ')
		{
			while (text[i] != ' ')
			{
				number += std::string(1, text[i]);
				if(i+1<std::size(text))
					i++;
			}
			xyz.push_back(std::stof(number));
			//std::cout << xyz.back()<<"\t";
			i++;
			number = "";
			while (text[i] != ' ')
			{
				number += std::string(1, text[i]);
				if (i + 1 < std::size(text))
					i++;
			}
			xyz.push_back(std::stof(number));
			//std::cout << xyz.back() << "\t";
			i++;
			number = "";
			while ((text[i] != ' ')&& (i + 1 < std::size(text)))
			{
				number += std::string(1, text[i]);
				if (i + 1 < std::size(text))
					i++;
			}
			xyz.push_back(std::stof(number));
			//std::cout << xyz.back() << "\n";
			i = 2;
			number = "";
			coords.push_back(xyz);
			xyz.clear();
			
		}
		i = 2;
		
		if (text[0] == 'f' && text[1] == ' ')
		{
			while (i < std::size(text))
			{
				if (text[i] == '/'&& text[i+1] == '/')
				{
					k = i-1;
					while (text[k] != ' ')
					{
						number += std::string(1, text[k]);
						k--;
					}
					std::reverse(number.begin(), number.end());
					vert.push_back(std::stoi(number));
					number = "";
				}
				i++;
			}
			vertices.push_back(vert);
			vert.clear();
			i = 2;
		}

	}

	POINT p1;
	std::vector<POINT> p;
	TRIANGLE tris;
	std::vector<TRIANGLE> t;

	for (int j = 0; j < std::size(coords); j++)
	{
		p1.create(coords[j][0], coords[j][1], coords[j][2]);
		p.push_back(p1);
	}

	for (int j = 0; j < std::size(vertices); j++)
	{
		tris.create(p[vertices[j][0] - 1], p[vertices[j][1] - 1], p[vertices[j][2] - 1]);
		tris.border_width = 1;
		t.push_back(tris);
	}
	mesh = t;
	myfile.close();
	return mesh;
}