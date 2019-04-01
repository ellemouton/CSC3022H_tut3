#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "huffen.cpp"
using namespace std;


TEST_CASE( "Frequency Map is correct", "[frequency]" ) {
	cout << "---------------------Testing Frequency Map---------------------" << endl;

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
	cout << "---------------------Testing tree Build---------------------" << endl;
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

TEST_CASE( "Check Code table", "[code]" ) {
	cout << "---------------------Testing code table---------------------" << endl;

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
	tree.buildCodeTable();

	//get and check the code table
	unordered_map<char, std::string> codeTable = tree.getCodeTable();

	REQUIRE(codeTable['d']=="00");
	REQUIRE(codeTable['c']=="010");
	REQUIRE(codeTable['a']=="0110");
	REQUIRE(codeTable['b']=="0111");

}

TEST_CASE( "Check Compression of data", "[compress]" ) {
	cout << "---------------------Testing compression of data---------------------" << endl;


	//create a known input file
	string input_file_name = "input_test.txt";
	string output_file_name = "output_test";
	ofstream input;
	input.open(input_file_name);
	input << "abbcccdddd"<<endl;
	input.close();

	//create new tree, build frequency map and then call the buildTree() function.
	MTNELL004::HuffmanTree tree;
	tree.buildMap(input_file_name);
	tree.buildTree();
	tree.buildCodeTable();
	tree.compressData(input_file_name, output_file_name);

	//get and check the compressed data in buffer.dat and load into string s
	string buffer_file = "buffer.dat";
	ifstream outputBufferFile;
	outputBufferFile.open(buffer_file);
	string s;
	outputBufferFile>>s;
	outputBufferFile.close();

	//check that the string is as expected from the code table
	REQUIRE(s=="01100111011101001001000000000");
}

TEST_CASE( "Check Conversion to byte array", "[byteArray]" ) {
	cout << "---------------------Testing conversion to byte array---------------------" << endl;

	//create a known input file
	string input_file_name = "input_test.txt";
	string output_file_name = "output_test";
	ofstream input;
	input.open(input_file_name);
	input << "abbcccdddd"<<endl;
	input.close();

	//create new tree, build frequency map and then call the buildTree() function.
	MTNELL004::HuffmanTree tree;
	tree.buildMap(input_file_name);
	tree.buildTree();
	tree.buildCodeTable();
	tree.convertToByteArray(input_file_name);

	//open the file that 'tree.convertToByteArray()' would have written to
	stringstream bfile;
    stringstream hFile;
    bfile << "binary_out.raw";
    hFile << "header.dat";
    string binary_file = bfile.str();
    string header_file = hFile.str();

    //read from header file
    int num_bits;
	ifstream header_in;
	header_in.open(header_file);
	if(!header_in){
		cerr << "Header file not found\n";
	}
	else{
		//read in number of bits in final sequence
		header_in >> num_bits;
	}
	header_in.close();

	REQUIRE(num_bits==29);

}

TEST_CASE( "Check that unpacking is correct", "[unpacking]" ) {
	cout << "---------------------Testing unpacking from byte array---------------------" << endl;

	//create a known input file

	string message = "Testing testing...testing 123";

	string input_file_name = "input_test.txt";
	ofstream input;
	input.open(input_file_name);
	input << message<<endl;
	input.close();

	MTNELL004::HuffmanTree tree;
	tree.buildMap(input_file_name);
	tree.buildTree();
	tree.buildCodeTable();
	tree.convertToByteArray(input_file_name);
	string uncompressed_message = tree.readAndUnpack();

	//check that uncompressed message is the same as the original message
	REQUIRE(uncompressed_message==message);
}



TEST_CASE( "Check special member functions of Huffman Node", "[member_node]" ) {
	
	SECTION( "HuffmanNode copy constructor" ) {
		cout << "---------------------Testing Copy constructor of HuffmanNode---------------------" << endl;
		MTNELL004::HuffmanNode hn1('a', 1);
		MTNELL004::HuffmanNode hn2('b', 1);
		MTNELL004::HuffmanNode hn3('c', 1);
		hn1.setLeft(hn2);
		hn1.setRight(hn3);

		REQUIRE(hn1.letter=='a');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft());
		REQUIRE(hn1.getRight());

		MTNELL004::HuffmanNode hn4(hn1);

		REQUIRE_FALSE(&hn1==&hn4);

		REQUIRE(hn1.letter=='a');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()->letter == 'b');
		REQUIRE(hn1.getRight()->letter == 'c');

		REQUIRE(hn4.letter=='a');
		REQUIRE(hn4.frequency==1);
		REQUIRE(hn4.getLeft()->letter == 'b');
		REQUIRE(hn4.getRight()->letter == 'c');

	}

	SECTION( "HuffmanNode move constructor" ) {
		cout << "---------------------Testing Move constructor of HuffmanNode---------------------" << endl;
		MTNELL004::HuffmanNode hn1('a', 1);
		MTNELL004::HuffmanNode hn2('b', 1);
		MTNELL004::HuffmanNode hn3('c', 1);
		hn1.setLeft(hn2);
		hn1.setRight(hn3);

		REQUIRE(hn1.letter=='a');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()->letter == 'b');
		REQUIRE(hn1.getRight()->letter == 'c');

		MTNELL004::HuffmanNode hn4(std::move(hn1));

		REQUIRE(hn1.letter=='a');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()==nullptr);
		REQUIRE(hn1.getRight()==nullptr);

		REQUIRE(hn4.letter=='a');
		REQUIRE(hn4.frequency==1);
		REQUIRE(hn4.getLeft()->letter == 'b');
		REQUIRE(hn4.getRight()->letter == 'c');
	}

	SECTION( "HuffmanNode copy assignment operator" ) {
		cout << "---------------------Testing Copy Assignment of HuffmanNode---------------------" << endl;
		MTNELL004::HuffmanNode hn1('a', 1);
		MTNELL004::HuffmanNode hn2('b', 1);
		MTNELL004::HuffmanNode hn3('c', 1);
		hn1.setLeft(hn2);
		hn1.setRight(hn3);

		MTNELL004::HuffmanNode hn4('d', 1);
		MTNELL004::HuffmanNode hn5('e', 1);
		MTNELL004::HuffmanNode hn6('f', 1);
		hn4.setLeft(hn5);
		hn4.setRight(hn6);

		REQUIRE(hn1.letter=='a');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()->letter == 'b');
		REQUIRE(hn1.getRight()->letter == 'c');

		REQUIRE(hn4.letter=='d');
		REQUIRE(hn4.frequency==1);
		REQUIRE(hn4.getLeft()->letter == 'e');
		REQUIRE(hn4.getRight()->letter == 'f');
		
		hn1 = hn4;

		REQUIRE(hn1.letter=='d');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()->letter == 'e');
		REQUIRE(hn1.getRight()->letter == 'f');

		REQUIRE(hn4.letter=='d');
		REQUIRE(hn4.frequency==1);
		REQUIRE(hn4.getLeft()->letter == 'e');
		REQUIRE(hn4.getRight()->letter == 'f');
	}

	SECTION( "HuffmanNode move assignment operator" ) {
		cout << "---------------------Testing Move Assignment of HuffmanNode---------------------" << endl;
		MTNELL004::HuffmanNode hn1('a', 1);
		MTNELL004::HuffmanNode hn2('b', 1);
		MTNELL004::HuffmanNode hn3('c', 1);
		hn1.setLeft(hn2);
		hn1.setRight(hn3);

		MTNELL004::HuffmanNode hn4('d', 1);
		MTNELL004::HuffmanNode hn5('e', 1);
		MTNELL004::HuffmanNode hn6('f', 1);
		hn4.setLeft(hn5);
		hn4.setRight(hn6);

		REQUIRE(hn1.letter=='a');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()->letter == 'b');
		REQUIRE(hn1.getRight()->letter == 'c');

		REQUIRE(hn4.letter=='d');
		REQUIRE(hn4.frequency==1);
		REQUIRE(hn4.getLeft()->letter == 'e');
		REQUIRE(hn4.getRight()->letter == 'f');
		
		hn1 = std::move(hn4);

		REQUIRE(hn1.letter=='d');
		REQUIRE(hn1.frequency==1);
		REQUIRE(hn1.getLeft()->letter == 'e');
		REQUIRE(hn1.getRight()->letter == 'f');

		REQUIRE(hn4.letter=='d');
		REQUIRE(hn4.frequency==1);
		REQUIRE(hn4.getLeft() ==nullptr);
		REQUIRE(hn4.getRight() ==nullptr);
	}

}

TEST_CASE( "Check special member functions of HuffmanTree", "[member_tree]" ) {
	
	SECTION( "HuffmanTree copy constructor" ) {
		cout << "---------------------Testing Copy constructor of HuffmanTree---------------------" << endl;
		MTNELL004::HuffmanTree t1;
		t1.buildMap("input.txt");
		t1.buildTree();

		MTNELL004::HuffmanTree t2(t1);

		REQUIRE(t1.getHeadNode()->frequency == t2.getHeadNode()->frequency);
		REQUIRE_FALSE(&t1== &t2);

	}

	SECTION( "HuffmanTree move constructor" ) {
		cout << "---------------------Testing Move constructor of HuffmanTree---------------------" << endl;
		MTNELL004::HuffmanTree t1;
		t1.buildMap("input.txt");
		t1.buildTree();

		REQUIRE(t1.getHeadNode());

		MTNELL004::HuffmanTree t2(std::move(t1));

		REQUIRE(t2.getHeadNode());
		REQUIRE(t1.getHeadNode()==nullptr);

	}

	SECTION( "HuffmanTree copy assignment operator" ) {
		cout << "---------------------Testing Copy Assignment of HuffmanTree---------------------" << endl;
		MTNELL004::HuffmanTree t1;
		t1.buildMap("input.txt");
		t1.buildTree();

		MTNELL004::HuffmanTree t2;
		t2.buildMap("input2.txt");
		t2.buildTree();

		REQUIRE(t1.getHeadNode());
		REQUIRE(t2.getHeadNode());

		t2 = t1;

		REQUIRE(t1.getHeadNode());
		REQUIRE(t2.getHeadNode());
		REQUIRE(t2.getHeadNode()->frequency==t1.getHeadNode()->frequency);

	}

	SECTION( "HuffmanTree move assignment operator" ) {
		cout << "---------------------Testing Move Assignment of HuffmanTree---------------------" << endl;
		
		MTNELL004::HuffmanTree t1;
		t1.buildMap("input.txt");
		t1.buildTree();

		MTNELL004::HuffmanTree t2;
		t2.buildMap("input2.txt");
		t2.buildTree();

		REQUIRE(t1.getHeadNode());
		REQUIRE(t2.getHeadNode());

		t2 = std::move(t1);

		REQUIRE(t2.getHeadNode());
		REQUIRE(t1.getHeadNode()==nullptr);
		
	}

}



















