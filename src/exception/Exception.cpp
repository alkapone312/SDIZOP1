#include "Exception.h"

using namespace SDIZO;

Exception::Exception(char* message) {
    this->message = message;
}

Exception::~Exception() {}

char* Exception::getMessage() {
    return this->message;
}
