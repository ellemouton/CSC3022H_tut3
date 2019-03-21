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
#include <memory>
# include <vector>

namespace MTNELL004{

	class HuffmanNode; //forward declaration

	//bool compare(const HuffmanNode& a, const HuffmanNode& b);
	//bool operator<(const HuffmanNode& a, const HuffmanNode& b);

	class HuffmanTree{
		private:
			std::unordered_map<char, int> freqmap;
			std::vector<std::shared_ptr<HuffmanNode>> nodes;
			size_t index_of_head;
			std::unordered_map<char, std::string> codeTable;

		public:
		
			//constructor 
			HuffmanTree(){}

			//destructor
			~HuffmanTree(void){
				
			}

			void buildMap(std::string input_file);
			void assignChildren(size_t ind1, size_t indLeft, size_t indRight);
			void buildTree(void);
			void buildCodeTable(void);
			void compressData(std::string input_file, std::string output_file);
			void recurse(size_t index, std::string code);

			
	};

	class HuffmanNode{
		friend class HuffmanTree;
		private:

			std::shared_ptr<HuffmanNode> left;
			std::shared_ptr<HuffmanNode> right;

		public: 
			size_t index;
			int frequency;
			char letter;

			//constructor 1
			HuffmanNode(char let, int freq, size_t ind): letter(let), frequency(freq), index(ind){}
			//constructor 2
			HuffmanNode(int freq, size_t ind): frequency(freq), index(ind){}
			//destructor
			~HuffmanNode(void){}

			/*
			//copy constructor
			HuffmanNode(const HuffmanNode & hfn){}

			//Move constructor
			HuffmanNode(HuffmanNode && hfn){}

			//copy assignment operator
			HuffmanNode & operator=(const HuffmanNode & hfn){}

			//move assignment operator
			HuffmanNode & operator=(const HuffmanNode && hfn){}
			*/

			// Overload < operator to compare two nodes
			//bool operator<(const HuffmanNode& n);

			

	};

	struct compare { 
	    bool operator()(const HuffmanNode& a, const HuffmanNode& b) ;
	}; 

}


#endif