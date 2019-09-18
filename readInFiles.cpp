#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

string readInFile() {

	string fileName;

	cout << "Enter the filename (include .txt): ";
	getline(cin, fileName);

	ifstream file;
	file.open(fileName);

	if (!file) {
		cout << "Cannot find file name with " << fileName << endl;
		exit(1);
	}

	stringstream ss;

	ss << file.rdbuf();

	file.close();

	return ss.str();
}

int main() {

	cout << readInFile() << endl;

	return 0;
}