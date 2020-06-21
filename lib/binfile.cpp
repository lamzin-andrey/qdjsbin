#include "binfile.h"

BinFile::BinFile(char* filename )
{
    this->filename = filename;
}

void BinFile::writeByte(long pos, char byte)
{
    ofstream bin(this->filename, ios_base::in|ios_base::binary);
    //bin.open(this->filename, ios_base::in|ios_base::binary);
    bin.seekp(pos,ios_base::beg);
    bin.put(byte);
    bin.close();
}

void BinFile::writeInt2(long pos, vector<int>data)
{
    this->writeInt(pos, data);
}

void BinFile::writeInt4(long pos, vector<int>data)
{
    this->writeInt(pos, data);
}

void BinFile::writeInt(long pos, vector<int>data)
{
    ofstream bin(this->filename, ios_base::binary);
    this->unpack(data);
    for (int i = 0; i < data.size(); i++)
    {
        bin.seekp(pos + i, ios_base::beg);
        bin.put(data[i]);
    }
    bin.close();
}


void BinFile::readByte(long pos, short &byte)
{
    ifstream b(this->filename, ios_base::binary);
    b.seekg(pos, ios_base::beg);
    byte = b.get();
    //cout << n << "\r\n";
    b.close();
}

long int BinFile::readInt2(long pos, vector<int> &data)
{
    data.clear();
    data.push_back(0);
    data.push_back(0);
    ifstream b(this->filename, ios_base::binary);
    b.seekg(pos, ios_base::beg);
    data[0] = b.get();
    b.seekg(pos + 1, ios_base::beg);
    data[1] = b.get();
    //cout << n << "\r\n";
    b.close();
    return this->pack(data);
}

long int BinFile::readInt4(long pos, vector<int> &data)
{
    data.clear();
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);
    ifstream b(this->filename, ios_base::binary);
    b.seekg(pos, ios_base::beg);
    data[0] = b.get();
    b.seekg(pos + 1, ios_base::beg);
    data[1] = b.get();
    b.seekg(pos + 1, ios_base::beg);
    data[2] = b.get();
    b.seekg(pos + 1, ios_base::beg);
    data[3] = b.get();
    //cout << n << "\r\n";
    b.close();
    return this->pack(data);
}


long BinFile::pack(vector<int> &data)   //invert from Intel notacion
{
    long result = 0;
    vector <int> invert;
    for (int i = data.size() - 1; i > -1; i--)
    {
        long n = data[i] << (i*8);
        result += n;
        invert.push_back(data[i]);
    }
    data = invert;
    return result;
}

void BinFile::unpack(vector<int> &data) //invert to Intel notacion
{
    vector <int> invert;
    for (int i = data.size() - 1; i > -1; i--)
    {
        invert.push_back(data[i]);
    }
    data = invert;
}
