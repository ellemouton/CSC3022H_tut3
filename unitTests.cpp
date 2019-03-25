#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "huffen.cpp"
using namespace std;


TEST_CASE( "Frequency Map is correct", "[frequency]" ) {

	//create a known input file
	string file_name = "input_test.txt";
	ofstream input;
	input.open(file_name);
	input << "abbcccdddd"<<endl;
	input.close();

	//create new tree and build a frequency map.
	MTNELL004::HuffmanTree tree;
	tree.buildMap(file_name);
	unordered_map<char, int> freqmap = tree.getFreqMap();

	REQUIRE(freqmap['a']==1);
	REQUIRE(freqmap['b']==2);
    REQUIRE(freqmap['c']==3);
	REQUIRE(freqmap['d']==4);
	REQUIRE_FALSE(freqmap['e']>0);
}

TEST_CASE( "Tree is built correctly", "[tree]" ) {

	SECTION( "Input file with 1 character" ) {
		//create a known input file
		string file_name = "input_test.txt";
		ofstream input;
		input.open(file_name);
		input << "a"<<endl;
		input.close();

		//create new tree, build frequency map and then call the buildTree() function.
		MTNELL004::HuffmanTree tree;
		tree.buildMap(file_name);
		tree.buildTree();
		shared_ptr<MTNELL004::HuffmanNode> head = tree.getHeadNode();
		REQUIRE(head->letter=='a');
		REQUIRE(head->frequency==1);
	}

	SECTION( "Input a longer string of characters" ) {
		//create a known input file
		string file_name = "input_test.txt";
		ofstream input;
		input.open(file_name);
		input << "abbcccdddd"<<endl;
		input.close();

		//create new tree, build frequency map and then call the buildTree() function.
		MTNELL004::HuffmanTree tree;
		tree.buildMap(file_name);
		tree.buildTree();
		shared_ptr<MTNELL004::HuffmanNode> head = tree.getHeadNode();

	
		REQUIRE(head->frequency==10);
		REQUIRE(head->getLeft()->letter=='d');
		REQUIRE(head->getLeft()->frequency==4);
		REQUIRE(head->getRight()->frequency==6);
		REQUIRE_FALSE(head->getLeft()->getLeft());
		REQUIRE(head->getRight()->getLeft()->letter=='c');
		REQUIRE(head->getRight()->getLeft()->frequency==3);
		REQUIRE(head->getRight()->getRight()->frequency==3);
		REQUIRE(head->getRight()->getRight()->getLeft()->letter=='a');
		REQUIRE(head->getRight()->getRight()->getLeft()->frequency==1);
		REQUIRE(head->getRight()->getRight()->getRight()->letter=='b');
		REQUIRE(head->getRight()->getRight()->getRight()->frequency==2);
	}

}























