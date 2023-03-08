#include <fstream>

namespace SDIZO {
    class FileReader {
        private:
            std::ifstream file;
        public:
            FileReader(std::string fileName);
            ~FileReader();
            static bool fileExists(std::string fileName);
            virtual int getData();
            virtual bool isData();
    };
}