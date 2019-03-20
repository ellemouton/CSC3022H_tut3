/*
* huffen.h file
*/

#ifndef HUFFEN_H
#define HUFFEN_H
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace MTNELL004{
	std::unordered_map<char, int> buildMap(std::string input_file);

}


#endif