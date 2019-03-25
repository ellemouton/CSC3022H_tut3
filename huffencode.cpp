#include "huffen.h"
using namespace std;

int main(int argc, char * argv[]){
	if(argc==3){
		string input_file = argv[1];
		string output_file = argv[2];

		MTNELL004::HuffmanTree tree;
		tree.buildMap(input_file);
		tree.buildTree();
		tree.buildCodeTable();
		tree.compressData(input_file, output_file);
	}
	else{
		cout << "invalid number of arguments\n";
	}
	return 0;
}

