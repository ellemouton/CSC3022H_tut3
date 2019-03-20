/*
* huffen.cpp file
*/

#include "huffen.h"

using namespace std;

namespace MTNELL004{
	unordered_map<char, int> buildMap(string input_file){

		unordered_map<char, int> freq_map;

		ifstream file (input_file);
		if(!file){
			cerr << "File open failed"<< endl;
		}
		else{
			char c;
			while(!file.eof()){
				file >> c;
				freq_map[c]++;
			}

			file.close();
		}
		return freq_map;
	}

}