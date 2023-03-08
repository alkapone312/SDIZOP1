#include <iostream>
#include <fstream>
#include "file/FileReader.h"
#include "exception/Exception.h"

using namespace SDIZO;
using namespace std;

FileReader::FileReader(string fileName) {
    if(!FileReader::fileExists(fileName)) {
        throw new Exception((char*)"File does not exist");
    }
    this->file.open(fileName);
}

FileReader::~FileReader() {
    this->file.close();
}

int FileReader::getData() {
    int data;
    this->file >> data;

    return data;
}

bool FileReader::isData() {
    return !this->file.eof();
}

bool FileReader::fileExists(std::string fileName) {
    ifstream f(fileName);
    bool ok = f.good();
    f.close();
    return ok;
}