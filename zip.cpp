#include <iostream>
#include <fstream>
#include <cctype>
#include <stdlib.h>
#include "huffman.cpp"

using namespace std;
void loadLetters (const int Letters[], HuffmanTree &tree, int &x, int &bits1);


const int NumLetters = 256;

int main(int argc, char *argv[])
{
	//////////////////////////////////////////////////////////////////////////////////		OPEN FILE and BUILD TREE
	HuffmanTree tree;				// data structure declaration
	int header = 0, bits1 = 0, bits = 0;		// first line of output file, char count
	ifstream ifs;					// input file
	string file, line;				// file name and encoded string
	int Letters[NumLetters];			// freq of chars array

	if(argc != 2){
		cout<<"ZIP: Invalid format\nTry `ZIP --help' for more information."<<endl;
		return 0;
	}
	else{
		file = argv[1];
		ifs.open(file.c_str(), ios:: in);
		if(!ifs.is_open()){
			cout<<"ZIP: File "<<file<<" is not a valid file"<<endl;
			return 0;
		}
		char ch;
        for (char ch = char(0);  ch <= char(126);  ch++)
                Letters[ch] = 0;

        while (ifs)
        {
        	ifs.get(ch);
		line += ch;
                Letters[ch] += 1;
        }   
		ifs.close();			
	}
	loadLetters(Letters, tree, header, bits1);
	tree.build();	
	if(true)
		tree.PrintTable();
	
	/////////////////////////////////////////////////////////////////////////////////////		OUTPUT FILE
	ofstream ofs;
	file+=".zip";
	ofs.open(file.c_str(), ios:: out);
	ofs<<header<<endl;							//outputs # unique chars
        
	for (char ch = char(0);  ch <= char(126);  ch++){			//outputs char ASCII and code
			int output = (int) ch;
		if(Letters[ch]!=0){
        		if (ch != '\n'&& ch != ' '){
				ofs << output <<"\t"<<tree.GetCode(ch)<<endl;
			}
			else if (ch == '\n'){
				ofs << output <<"\t"<<tree.GetCode('/')<<endl;
			}
			else if (ch == ' '){	
				ofs << output <<"\t"<<tree.GetCode('_')<<endl;
			}
		}
	}
	
	for(int i = 0; i<line.size(); i++){
		bits++;	
		if(line[i]==' ')
			ofs<<tree.GetCode('_');
		else if(line[i]=='\n')
			ofs<<tree.GetCode('/');
		else	
			ofs<<tree.GetCode(line[i]);
	}
	
	ofs.close();
	double val = bits1*8;
	val =(double) bits/val;
	double ratio =(1.0-val)*100.0;
	cout<<"File Succesfully Compressed to "<<bits<<" Bits("<<abs(ratio)<<" % Less)"<<endl;

	 
    return 0;
}


void loadLetters (const int Letters[], HuffmanTree &tree, int &x, int &bits1)
{
        for (char ch = char(0);  ch <= char(126);  ch++)
          if ((Letters[ch] != 0) && (ch != '\n') && (ch != ' ')){
		tree.insert(ch, Letters[ch]);	
		x++;
		bits1++;
	}
          else if ((Letters[ch] != 0) && (ch == '\n')){
		tree.insert('/', Letters[ch]);	
		x++;
		bits1++;
	}
          else if ((Letters[ch] != 0) && (ch == ' ')){
		tree.insert('_', Letters[ch]);
		x++;
		bits1++;
	}
}

