#pragma once
#include <fstream>
#include "utils/File.h"

namespace SDIZO {
    class FileWriter : public SDIZO::File {
        private:
            std::ofstream file;
        public:
            FileWriter(std::string filename);
            ~FileWriter();
            virtual void write(std::string value);
    };
}
