#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
	map <string, char> pam;			// best way to store chars with encoded value
	string line, encode, curr;
	int index, num, val=0;
	ifstream ifs;
	ofstream ofs;
		if(argc != 2){
			cout<<"Error. -- Now Aborting."<<endl;
		}
		else{
			string f = argv[1];
			ifs.open(f.c_str(), ios:: in);		
			if(f.substr(f.length()-3, 3)!="zip"){
				cout<<"        File Entered Is Not A Zip File -- Now Aborting."<<endl;
				return 1;
			}			// file is now open
		
		ifs>>num;			// stores number of lines to loop to map chars w/ indeces
		for(int i=0; i<num; i++){
			ifs>>index>>encode;		
			pam[encode]= (char) index;	// outputs char value of the ASCII index
		}
		ifs>>line;	ifs.close();
	//	cout<<line;			// string to be decoded
		f=f.substr(0, f.length()-4);
	//	cout<<f;			// output file name	
		ofs.open(f.c_str());
		int j = 1;
		for(int i = 0; i<line.length(); i++){
			curr = line.substr(val, j);
			if(!(pam.find(curr)==pam.end())){
				ofs<<pam.at(curr);
				val=i+1;
				j=val-i;
			}
			else
				j++;
			}
		ofs.close();
		cout<<"File Successfully Inflated Back To Original."<<endl;
		}
    return 0;
}
