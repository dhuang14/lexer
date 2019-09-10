#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

string readInFile(fileName){
	
	ifstream file;
	file.open(fileName);
	
	if(!file){
		cout << "Cannot find file name with " << fileName << endl;
	}
	
	stringstream ss;
	
	ss << file.rdbuf();
	
	return ss.str();
}

int main(){
	
	cout << readInFile("test.txt") << endl;
	
	return 0;
}