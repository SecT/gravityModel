#ifndef MYLIB_H
#define MYLIB_H

#include <vector>
#include <string>
#include <fstream>

using std::ifstream;
using std::string;
using std::vector;

void readFromFile(vector<float>& config, std::string filename)
{
    ifstream indata; // indata is like cin
    float num; // variable for input value
    indata.open(filename); // opens the file
    if(!indata)   // file couldn't be opened
    {
        //cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    indata >> num;

    while ( !indata.eof() )   // keep reading until end-of-file
    {
        //cout << "The next number is " << num << endl;
        config.push_back(num);
        indata >> num; // sets EOF flag if no value found
    }
    indata.close();
    //cout << "End-of-file reached.." << endl;
}

#endif
