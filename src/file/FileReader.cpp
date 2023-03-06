#include <iostream>
#include <fstream>
#include "file/FileReader.h"

using namespace SDIZO;
using namespace std;

FileReader::FileReader(string fileName) {
    this->file.open(fileName);
}

FileReader::~FileReader() {
    this->file.close();
}

string FileReader::getData() {
    string data;
    this->file >> data;

    return data;
}

bool FileReader::isData() {
    return !this->file.eof();
}