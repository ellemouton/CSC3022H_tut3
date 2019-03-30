/*
* huffen.h file
*/

#ifndef HUFFEN_H
#define HUFFEN_H
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <memory>
#include <vector>
#include <bitset>

namespace MTNELL004{

	class HuffmanNode; //forward declaration

	struct compare { 
	    bool operator()(const HuffmanNode& a, const HuffmanNode& b) ;
	}; 
	
	class HuffmanTree{
		private:
			
			std::unordered_map<char, std::string> codeTable;
			std::unordered_map<std::string, char> reverseCodeTable;
			std::shared_ptr<HuffmanNode> head;
			std::unordered_map<char, int> freqmap;

		public:

			//constructor 
			HuffmanTree();

			//destructor
			~HuffmanTree(void);

			//copy constructor
			HuffmanTree(const HuffmanTree & hft);

			//Move constructor
			HuffmanTree(HuffmanTree && hft);

			//copy assignment operator
			HuffmanTree & operator=(const HuffmanTree & hft);

			//move assignment operator
			HuffmanTree & operator=(const HuffmanTree && hft);

			void buildMap(std::string input_file);
			void buildTree(void);
			void buildCodeTable(void);
			void compressData(std::string input_file, std::string output_file);
			void convertToByteArray(std::string input_file);
			void readAndUnpack(void);
			void recurse(std::string code, std::shared_ptr<HuffmanNode> &node);
			std::unordered_map<char, int> getFreqMap(void); //for unit tests
			std::shared_ptr<HuffmanNode> getHeadNode(void); //for unit tests
			std::unordered_map<char, std::string> getCodeTable(void);
			
	};

	class HuffmanNode{
		friend class HuffmanTree;
		private:
			std::shared_ptr<HuffmanNode> left;
			std::shared_ptr<HuffmanNode> right;

		public: 
			int frequency;
			char letter;

			//constructor 1
			HuffmanNode(char let, int freq);
			//constructor 2
			HuffmanNode(int freq);
			
			//destructor
			~HuffmanNode(void);
			
			//copy constructor
			HuffmanNode(const HuffmanNode & hfn);

			//Move constructor
			HuffmanNode(HuffmanNode && hfn);

			//copy assignment operator
			HuffmanNode & operator=(const HuffmanNode & hfn);

			//move assignment operator
			HuffmanNode & operator=(const HuffmanNode && hfn);

			std::shared_ptr<HuffmanNode> getLeft(void); //for unit tests
			std::shared_ptr<HuffmanNode> getRight(void); //for unit tests
	};

	int bin_to_dec(int n);
	std::string dec_to_bin(int num);

}


#endif