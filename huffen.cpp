/*
* huffen.cpp file
*/

#include "huffen.h"

using namespace std;

namespace MTNELL004{
	//-----------------special member functions for HuffmanNode:--------------------------------------------------------------------

	//constructor 1
	HuffmanNode::HuffmanNode(char let, int freq): letter(let), frequency(freq){}

	//constructor 2
	HuffmanNode::HuffmanNode(int freq): frequency(freq){}
	
	//destructor
	HuffmanNode::~HuffmanNode(void){}

	//copy constructor
	HuffmanNode::HuffmanNode(const HuffmanNode & hfn):frequency(hfn.frequency), letter(hfn.letter), left(hfn.left), right(hfn.right){}

	//Move constructor
	HuffmanNode::HuffmanNode(HuffmanNode && hfn): frequency(std::move(hfn.frequency)), letter(std::move(hfn.letter)){
		left = std::move(hfn.left);
		right = std::move(hfn.right);
	}

	//copy assignment operator
	HuffmanNode & HuffmanNode::operator=(const HuffmanNode & hfn){
		if(this!=&hfn){
			letter = hfn.letter;
			frequency = hfn.frequency;
			left = hfn.left;
			right = hfn.right;
		}
		return *this;
	}

	//move assignment operator
	HuffmanNode & HuffmanNode::operator=(HuffmanNode && hfn){
		if(this!=&hfn){
			letter = std::move(hfn.letter);
			frequency = std::move(hfn.frequency);
			left = std::move(hfn.left);
			right = std::move(hfn.right);
		}
		return *this;
	}

	//---------------special member functions for HuffmanTree-----------------------------------------------------------------------

	//constructor 
	HuffmanTree::HuffmanTree(){}

	//destructor
	HuffmanTree::~HuffmanTree(void){
		head= nullptr;
	}

	//copy constructor
	HuffmanTree::HuffmanTree(const HuffmanTree & hft):codeTable(hft.codeTable), reverseCodeTable(hft.reverseCodeTable), freqmap(hft.freqmap), head(hft.head){
	}
		

	//Move constructor
	HuffmanTree::HuffmanTree(HuffmanTree && hft){
		codeTable = move(hft.codeTable);
		reverseCodeTable = move(hft.reverseCodeTable);
		freqmap = move(hft.freqmap);
		head = move(hft.head);
	}

	//copy assignment operator
	HuffmanTree & HuffmanTree::operator=(const HuffmanTree & hft){
		if(this!=&hft){
			codeTable = hft.codeTable;
			reverseCodeTable = hft.reverseCodeTable;
			freqmap = hft.freqmap;
			head = hft.head;
		}
		return *this;
	}

	//move assignment operator
	HuffmanTree & HuffmanTree::operator=(HuffmanTree && hft){
		if(this!=&hft){
			codeTable = move(hft.codeTable);
			reverseCodeTable = move(hft.reverseCodeTable);
			freqmap = move(hft.freqmap);
			head = move(hft.head);
		}
		return *this;
	}

	//------------------useful functions-----------------------------------------------------------------------------------------

    bool compare::operator()(const HuffmanNode& a, const HuffmanNode& b){
        return a.frequency > b.frequency; 
    } 

    int bin_to_dec(int n){ 
	    int dec = 0; 
	    int base = 1; 
	    int temp = n; 
	    while (temp) { 
	        int last = temp % 10; 
	        temp = temp/10; 
	        dec += last*base; 
	        base = base*2; 
	    } 
	    return dec; 
	} 

	string dec_to_bin(int num){
		string s = std::bitset<8>(num).to_string();
		return s;
	}

	//--------------------HuffmanTree function definitions----------------------------------------------------------------------

	void HuffmanTree::buildMap(string input_file){

		//cout<<"Building Map...\n"<<endl;

		ifstream file (input_file);
		if(!file){
			cerr << "File open failed"<< endl;
		}
		else{
			string input = "";
			string line;
		    while (getline (file,line) ){
		      input.append(line);
		    }
		    file.close();

		    //cout<<"Text input from file is:"<<endl;
			//cout<<input<<"\n"<<endl;

		    for(char& c : input) {
    			freqmap[c]++;
			}
		}
	}

	void HuffmanTree::buildTree(){
		//cout<<"Building Tree...\n"<<endl;

		//create a priority tree
		priority_queue<HuffmanNode, std::vector<HuffmanNode>, compare> pq; //automatic variable

		for (auto& item: freqmap) {
    		HuffmanNode new_node(item.first,item.second);
    		pq.push(new_node);
    	}

    	while(pq.size()>1){
    		HuffmanNode n1 = pq.top(); pq.pop();
    		HuffmanNode n2 = pq.top(); pq.pop();

    		int sum_freq = n1.frequency+n2.frequency;

    		HuffmanNode new_node(sum_freq);

    		new_node.left = make_shared<HuffmanNode>(n1);
    		new_node.right = make_shared<HuffmanNode>(n2);
    		pq.push(new_node);
    	}

    	head = make_shared<HuffmanNode>(pq.top());
	}

	void HuffmanTree::recurse(string code, shared_ptr<HuffmanNode> &node){
		
		if(node->left == NULL){
			char let = node->letter;
			codeTable[let] = code;
			reverseCodeTable[code] = let;
		}
		else{
			string strLeft = code; strLeft.append("0");
			string strRight = code; strRight.append("1");

			recurse(strLeft, node->left);
			recurse(strRight, node->right);
		}
	}

	void HuffmanTree::buildCodeTable(void){
		//cout<<"Building Code table...\n"<<endl;

		string code = "0";
		recurse(code, head);

		/*cout<<"The code table is as follows:"<<endl;
		for( const auto& n : codeTable ) {
       	 	std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    	}*/
	}

	void HuffmanTree::compressData(string input_file, string output_file){
		//cout<<"\nCompressing data and writing the output string to: 'buffer.dat' and writing the code table to '"<<output_file<<".hdr'...\n"<<endl;

		//construct buffer
		string buffer = "";
		string input;

		ifstream file_in (input_file);
		if(!file_in){
			cerr << "File open failed"<< endl;
		}
		else{
			string line;
		    while (getline (file_in,line) ){
		      input.append(line);
		    }
		    file_in.close();

		    for(char& c : input) {
    			buffer.append(codeTable[c]);
			}
		}
		
		char * cstr = new char [buffer.length()+1];
  		std::strcpy (cstr, buffer.c_str());

		string buffer_file = "buffer.dat";
		ofstream outputBufferFile;
		outputBufferFile.open(buffer_file);
		outputBufferFile.write(cstr, buffer.length());
		outputBufferFile.close();

		output_file.append(".hdr");
		ofstream myfile;
		myfile.open(output_file);
		myfile << "Field Count: "<<codeTable.size()<<"\n"<<endl;

		for( const auto& n : codeTable ) {
       	 	myfile << "Character: " << n.first << " Code:" << n.second << "\n"<<endl;
    	}

    	//cout<<"The final bitstream is:\n"<<cstr<<"\n"<<endl;

    	double bytes = (buffer.length()/8) + (buffer.length()%8 ? 1 : 0);
    	myfile << "This would require: " << bytes<< " bytes to store\n"<<endl;

    	//compression ratio
    	double cc = bytes/(buffer.length()*8);
    	myfile << "The compression ratio is: " << cc<< " [(bit string size in bytes)/(input chars in bytes)]\n"<<endl;

    	//print info to screen:
    	//cout<<"Size of origional message: "<<buffer.length()*8<<" bytes"<<endl;
    	//cout<<"Size of compressed message: "<<bytes<<" bytes"<<endl;
    	//cout<<"The compression ratio is: "<<cc<<"\n"<<endl;

		myfile.close();
	}


	void HuffmanTree::convertToByteArray(std::string input_file){

		//cout<<"Converting to bitstream and writing to binary file: 'binary_out.raw' and writing header file 'header.dat'...\n"<<endl;
		//create binary file and header file name
	    stringstream bfile;
	    stringstream hFile;
	    bfile << "binary_out.raw";
	    hFile << "header.dat";
	    string binary_file = bfile.str();
	    string header_file = hFile.str();

		//construct buffer
		string buffer = "";

		//For each character in the input_file, consult the code-table and append the appropriate code to buffer.
		string input;
		ifstream file_in (input_file);
		if(!file_in){
			cerr << "File open failed"<< endl;
		}
		else{
			string line;
		    while (getline (file_in,line) ){
		      input.append(line);
		    }
		    file_in.close();

		    for(char& c : input) {
    			buffer.append(codeTable[c]);
			}
		}

		//store the origional length of buffer and then do zero-padding so that the length is divisable by 8. Thus making it easy to split into bytes.
		int len_of_origional = buffer.length();

		while(!((buffer.length())%8==0)){
			buffer.append("0");
		}

		//create a memory block 
		int length =buffer.length();
		int num_bytes = (int)length/8;
		char* byte = new char[num_bytes];
		
		//split the buffer sections of 8. Then convert the substring byte to an integer and convert to from binary to decimal and store in the byte array.
		for(int i = 0; i< num_bytes; i++){
			string str = buffer.substr ((i*8),8);
			stringstream temp_stream(str); 
			int num  = 0;
			int bin = 0; 
    		temp_stream >> bin;
    		num = bin_to_dec(bin);
    		byte[i] = num; 
		}


		//create and write to output binary file
	    ofstream binary;
	  	binary.open (binary_file,  ios::out | ios::binary);
	  	binary.write (byte,num_bytes);
	  	binary.close();

	  	//create header file that will have the number of bits in the file.
	    ofstream myHeaderFile;
	  	myHeaderFile.open (header_file);
	    myHeaderFile << len_of_origional;
	    myHeaderFile.close();
		
	}

	string HuffmanTree::readAndUnpack(void){
		//cout<<"Reading and unpacking the bitstream from 'binary_out.raw'...\n"<<endl;
		int num_bits;
		int num_bytes;

		//create binary file and header file name
	    stringstream bfile;
	    stringstream hFile;
	    bfile << "binary_out.raw";
	    hFile << "header.dat";
	    string binary_file = bfile.str();
	    string header_file = hFile.str();

	    //read from header file
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

		int length = num_bits+(8-num_bits%8);
		num_bytes = length/8;

		//read in the binary file 
		char* bytes = new char[length];
		ifstream binary_in;

		binary_in.open (binary_file,  ios::in | ios::binary);
		if(!binary_in){
			cout << binary_file << " not found\n";
		}
		else{
			binary_in.read (bytes,length);
		}
		binary_in.close();


		string buffer = "";

		int i;
		for(i=0; i<num_bytes; i++){
			int num = (int)(unsigned char)bytes[i];
			buffer.append(dec_to_bin(num));
		}

		//remove the zero padding
		buffer =buffer.substr(0, num_bits);


		//--------------------------Unpack---------------------------------
		string message = "";
		string temp_code = "";

		for(char& c : buffer) {
		    temp_code.push_back(c);
		    if(reverseCodeTable[temp_code]){
		    	message.push_back(reverseCodeTable[temp_code]);
		    	temp_code = "";
		    }

		}

		//cout<<"The unpacked message is: "<<endl;
		//cout<<message<<endl;
		return message;
	}

	unordered_map<char, int> HuffmanTree::getFreqMap(void){
		return freqmap;
	}

	shared_ptr<HuffmanNode> HuffmanTree::getHeadNode(void){
		return head;
	}

	shared_ptr<HuffmanNode> HuffmanNode::getLeft(void){
		return left;
	}
	shared_ptr<HuffmanNode> HuffmanNode::getRight(void){
		return right;
	}

	void HuffmanNode::setLeft(HuffmanNode l){
		left = make_shared<HuffmanNode>(l);
	} 
	void HuffmanNode::setRight(HuffmanNode r){
		right = make_shared<HuffmanNode>(r);
	}

	unordered_map<char, std::string> HuffmanTree::getCodeTable(void){
		return codeTable;
	}



}