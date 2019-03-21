#include "huffen.h"

using namespace std;

int main(int argc, char * argv[]){
	if(argc==3){
		//read in file names
		string input_file = argv[1];
		string output_file = argv[2];

		MTNELL004::HuffmanTree tree;
		tree.buildMap(input_file);
		tree.buildTree();
		tree.buildCodeTable();

		//create output

	}
	else{
		cout << "invalid number of arguments\n";
	}
	return 0;
}