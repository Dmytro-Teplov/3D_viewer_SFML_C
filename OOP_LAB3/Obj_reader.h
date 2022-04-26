#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Classes.h"

void show(std::vector<std::vector<float>> A);
Point parse_point(std::string text, char divider);
std::vector<std::vector<int>> parse_face(std::string text);
Object reading(std::string filename);