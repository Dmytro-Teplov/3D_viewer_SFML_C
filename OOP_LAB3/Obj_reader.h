#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Classes.h"

void show(std::vector<std::vector<float>> A);
point parse_point(std::string text, char divider);
//point parse_point(std::string text, char pointer1, char pointer2, char divider);
OBJECT reading(std::string filename);