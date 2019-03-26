/*
* huffen.cpp file
*/

#include "huffen.h"

using namespace std;

namespace MTNELL004{

    bool compare::operator()(const HuffmanNode& a, const HuffmanNode& b){
        return a.frequency > b.frequency; 
    } 

	void HuffmanTree::buildMap(string input_file){
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

		    for(char& c : input) {
    			freqmap[c]++;
			}
		}
	}

	void HuffmanTree::buildTree(){
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
		}
		else{
			string strLeft = code; strLeft.append("0");
			string strRight = code; strRight.append("1");

			recurse(strLeft, node->left);
			recurse(strRight, node->right);
		}
	}

	void HuffmanTree::buildCodeTable(void){
		string code = "0";

		recurse(code, head);

		/*for( const auto& n : codeTable ) {
       	 	std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    	}*/
	}

	void HuffmanTree::compressData(string input_file, string output_file){
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
  		//cout<<cstr<<endl;

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
       	 	myfile << "Character: " << n.first << " Code:" << n.second << "\n";
    	}
    	double cc = (buffer.length()/8) + (buffer.length()%8 ? 1 : 0);
    	myfile << "Compression Ratio: " << cc<< "\n";

		myfile.close();
	}

	void HuffmanTree::convertToByteArray(std::string input_file){
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
		
		std::string bit_string = "101";
	    std::bitset<3> b(bit_string);       // [1,0,1,0,1,0,1,0]
	    //unsigned char c = ( b.to_ulong() & 0xFF);
	    //std::cout << static_cast<int>(c); // prints 170
	    //cout<<b.size();
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
	unordered_map<char, std::string> HuffmanTree::getCodeTable(void){
		return codeTable;
	}

	

	//-----------------special member functions for HuffmanNode:--------------------------------------------------------------------

	//constructor 1
	HuffmanNode::HuffmanNode(char let, int freq): letter(let), frequency(freq){
		//std::cout<<"creating "<<letter<<" "<<frequency<<std::endl;
	}
	//constructor 2
	HuffmanNode::HuffmanNode(int freq): frequency(freq){}
	
	//destructor
	HuffmanNode::~HuffmanNode(void){
		//no delete
		//std::cout<<"killing "<<letter<<" "<<frequency<<std::endl;
	}

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
	HuffmanNode & HuffmanNode::operator=(const HuffmanNode && hfn){
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
		//deallocate codeTable and freqmap
		//set head to nullptr
	}


}