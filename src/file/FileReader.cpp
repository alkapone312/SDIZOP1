#include <iostream>
#include <fstream>
#include "file/FileReader.h"

using namespace SDIZO;
using namespace std;

FileReader::FileReader(char* fileName) {
    this->file.open(fileName);
}

FileReader::~FileReader() {
    this->file.close();
}

void FileReader::getData(char* data) {
    this->file >> data;
}

bool FileReader::isData() {
    return this->file.eof();
}