#include "huffen.h"

using namespace std;

int main(int argc, char * argv[]){
	if(argc==3){
		//read in file names
		string input_file = argv[1];
		string output_file = argv[2];

		//build frequency table using unordered map
		unordered_map<char, int> freq_map = MTNELL004::buildMap(input_file);

		//build the tree

		//build code table

		//create output


	}
	else{
		cout << "invalid number of arguments\n";
	}
	return 0;
}