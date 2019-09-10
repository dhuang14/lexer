//
//  main.cpp
//  readInFile
//
//  Created by David Huang on 9/9/19.
//  Copyright © 2019 David Huang. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

string readInFile(string fileName){
    
    ifstream file;
    file.open(fileName);
    
    if(!file){
        cout << "Cannot find file name with " << fileName << endl;
        exit(1);
    }
    
    stringstream ss;
    
    ss << file.rdbuf();
    
    file.close();
    
    return ss.str();
}

int main(){
    
    cout << readInFile("test.txt") << endl;
    
    return 0;
}
