/*
* huffen.cpp file
*/

#include "huffen.h"

using namespace std;

namespace MTNELL004{
/*
	bool operator<(const HuffmanNode& a, const HuffmanNode& b){
		cout<<"using custom <"<<endl;
		return a.frequency < b.frequency;
	}

	bool compare(const HuffmanNode& a, const HuffmanNode& b){
		cout<<"using custom compare"<<endl;
		if(a<b) return true;
		else return false;
	}
*/

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

	void HuffmanTree::assignChildren(size_t ind1, size_t indLeft, size_t indRight){
		nodes[ind1]-> left = nodes[indLeft];
		nodes[ind1]-> right = nodes[indRight];
	}

	void HuffmanTree::buildTree(){
		//create a priority tree
		priority_queue<HuffmanNode, std::vector<HuffmanNode>, compare> pq;
		size_t index = 0;
		for (auto& item: freqmap) {
    		//cout << item.first<<" "<<item.second<<endl;	
    		shared_ptr<HuffmanNode> new_node = make_shared<HuffmanNode>(item.first,item.second, index);
    		pq.push(*new_node);
    		nodes.push_back(new_node);
    		index++;
    	}

    	while(pq.size()>1){
    		size_t indLeft = pq.top().index; int freq1 = pq.top().frequency;
    		pq.pop();

    		size_t indRight = pq.top().index; int freq2 = pq.top().frequency;
    		pq.pop();

    		int sum_freq = freq1+freq2;

    		shared_ptr<HuffmanNode> new_node = make_shared<HuffmanNode>(sum_freq, index);
    		nodes.push_back(new_node);
    		pq.push(*new_node);
    		assignChildren(index, indLeft, indRight);
    		//cout<<"new node index: "<<index<<" left node index: "<<indLeft<<" right node index: "<<indRight<<endl;
    		index++;
    	}
    	index_of_head = index-1;

    	for(size_t i = 0; i<= index_of_head; i++){
    		cout<<"node "<<i<<" has letter "<<nodes[i]->letter<<" and frequency "<<nodes[i]->frequency<<endl;//" and has left child: "<<(nodes[i]->left)<<endl;//->index<<" and has right child: "<<nodes[i]->right->index<<endl;
    	}
		
	}

	void buildCodeTable(void){
		
	}

	



}