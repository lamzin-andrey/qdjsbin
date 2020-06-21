#ifndef BINFILE_H
#define BINFILE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class BinFile
{
public:
    BinFile(char* filename);
    void writeByte(long int pos, char byte);
    void writeInt2(long int pos, vector<int> data);
    void writeInt4(long int pos, vector<int> data);

    void readByte(long int pos, short &byte);
    long readInt2(long int pos, vector<int> &data);
    long readInt4(long int pos, vector<int> &data);
private:
    long pack(vector<int> &data);   //invert from Intel notacion
    void unpack(vector<int> &data); //invert to Intel notacion
    void writeInt(long int pos, vector<int> data);
    char* filename;
};

#endif // BINFILE_H
