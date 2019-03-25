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
			char c;
			while(!file.eof()){
				file >> c;
				freqmap[c]++;
			}
			file.close();
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

		for( const auto& n : codeTable ) {
       	 	std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    	}
	}

	void HuffmanTree::compressData(string input_file, string output_file){
		//construct buffer
		string buffer = "";

		ifstream file_in (input_file);
		if(!file_in){
			cerr << "File open failed"<< endl;
		}
		else{
			char c;
			while(!file_in.eof()){
				file_in >> c;
				buffer.append(codeTable[c]);
			}
			file_in.close();
		}
		
		char * cstr = new char [buffer.length()+1];
  		std::strcpy (cstr, buffer.c_str());
  		cout<<cstr<<endl;

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
		myfile.close();
	}

}