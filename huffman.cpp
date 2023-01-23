#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;

}

bool HuffmanTree:: inTree(char ch) {
	if(ch == lookUp(ch))
		return true;
	return false;
}

int HuffmanTree:: GetFrequency(char ch) {
	int x = (int) ch;
	return GetFrequency(x);
}

int HuffmanTree:: GetFrequency(int i) {
	return nodes[i].weight;
}

int HuffmanTree:: lookUp(char ch) {
	for(int i=0; i<numChars; i++){
		if(nodes[i].ch == ch)
			return i;
	}	
	return -1;
}

string HuffmanTree:: GetCode(char ch) {
	return GetCode(lookUp(ch));
}


string HuffmanTree:: GetCode(int i) {
	if(nodes[i].parent== 0)
		return "";
	else{
		return (GetCode(nodes[i].parent)+(char)(nodes[i].childType+'0'));
	}
}

void HuffmanTree:: PrintTable() {
	cout<<"\t## ENCODING TABLE FOR ZIP FILE ##\n\n\tIndex\tChar\tWeight\tParent\tChildType"<<endl;
	int counter = 1;
	for(int i =0; i< numChars; i++){
		if(nodes[i].ch!='*'&&nodes[i].ch!='\0')
			cout<<"\t"<<i<<"\t"<<nodes[i].ch<<"\t"<<nodes[i].weight<<"\t"<<nodes[i].parent<<"\t"<<nodes[i].childType<<endl;
		else if(nodes[i].ch=='\0'&&nodes[i].childType!=-1){
			cout<<"\t"<<i<<"\t"<<"T"<<counter<<"\t"<<nodes[i].weight<<"\t"<<nodes[i].parent<<"\t"<<nodes[i].childType<<endl;
			counter++;
		}
		else{
			cout<<"\t"<<i<<"\t"<<"T"<<counter<<"\t"<<nodes[i].weight<<"\t"<<nodes[i].parent<<"\t"<<"N/A"<<endl;
			counter++;
		}
	}
}

int HuffmanTree:: numNodes() {
	return numChars;
}

void HuffmanTree:: build() {
	int ASCII = 256;
	int min, leaf, leaf1;
	int run = numChars*2-1;
	while(run>numChars){
		min = ASCII;
		for(int i = 0; i<numChars; i++){
			if(nodes[i].parent==-1){
				if(nodes[i].weight<min){
					leaf=i;
					min = nodes[i].weight;
				}
			}
		}	
		min=ASCII;
		for(int i = 0; i<numChars; i++){
			if(nodes[i].parent==-1){
				if(nodes[i].weight<min && i!=leaf){
					leaf1=i;
					min = nodes[i].weight;
				}	
			}		
		} 
		int val = nodes[leaf].weight + nodes[leaf1].weight;
		insert('\0', val);
		nodes[leaf].parent = nodes.size()-1;
		nodes[leaf1].parent = nodes.size()-1;
		nodes[leaf].childType = 0;
		nodes[leaf1].childType = 1;
	}
	nodes[nodes.size()-1].parent=0;
	built = true;	
}


