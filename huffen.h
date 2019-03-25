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

	struct compare { 
	    bool operator()(const HuffmanNode& a, const HuffmanNode& b) ;
	}; 
	
	class HuffmanTree{
		private:
			
			std::unordered_map<char, std::string> codeTable;
			std::shared_ptr<HuffmanNode> head;
			std::unordered_map<char, int> freqmap;

		public:

			//constructor 
			HuffmanTree(){}

			//destructor
			~HuffmanTree(void){
				
			}

			void buildMap(std::string input_file);
			void buildTree(void);
			void buildCodeTable(void);
			void compressData(std::string input_file, std::string output_file);
			void recurse(std::string code, std::shared_ptr<HuffmanNode> &node);
			std::unordered_map<char, int> getFreqMap(void); //for unit tests
			std::shared_ptr<HuffmanNode> getHeadNode(void); //for unit tests
			
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
			HuffmanNode(char let, int freq): letter(let), frequency(freq){
				//std::cout<<"creating "<<letter<<" "<<frequency<<std::endl;
			}
			//constructor 2
			HuffmanNode(int freq): frequency(freq){}
			//destructor
			~HuffmanNode(void){
				//std::cout<<"killing "<<letter<<" "<<frequency<<std::endl;
			}

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

			std::shared_ptr<HuffmanNode> getLeft(void); //for unit tests
			std::shared_ptr<HuffmanNode> getRight(void); //for unit tests
	};

	

}


#endif