#include <fstream>
#include "utils/RandomNumberGenerator.h"
#include "utils/FileWriter.h"
#include "ui/UserInterface.h"

using namespace std;
using namespace SDIZO;

string testFileName(string testFor, int number) {
    return "testfiles/" + testFor + "/test" + std::to_string(number) + ".txt";
}

int getNewFileIndex(string testFor) {
    int i = 0;
    while (File::fileExists(testFileName(testFor, i))) {
        i++;
    }

    return i;
}

void _generateTestFile(string testFor, int length) {
    int index = getNewFileIndex(testFor);

    RandomNumberGenerator* generator = new RandomNumberGenerator();
    FileWriter* writer = new FileWriter(testFileName(testFor, index));
    writer->write(to_string(length) + " ");
    for(int i = 0 ; i < length; i++) {
        writer->write(to_string(generator->nextInt()) + " ");
    }

    delete generator;
    delete writer;
}

void _deleteTestFiles(string testFor) {
    int index = getNewFileIndex(testFor);
    for(int i = 0 ; i < index; i++) {
        std::remove(testFileName(testFor, i).c_str());
    }
}

void testFileGeneration(string testFor) {
    UserInterface* ui;
    ui = UserInterface::getInstance();
    ui->info("How long would you like the file to be?");
    int length = ui->getNumber();
    ui->info("Generating test file...");
    _generateTestFile(testFor, length);
    ui->info("Test file generation completed.");
}