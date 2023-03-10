#include "utils/FileWriter.h"

using namespace SDIZO;
using namespace std;

FileWriter::FileWriter(string filename) {
    this->file.open(filename);
}

FileWriter::~FileWriter() {
    this->file.close();
}

void FileWriter::write(string value) {
    this->file << value;
}