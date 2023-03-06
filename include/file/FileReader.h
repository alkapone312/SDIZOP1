#include <fstream>

namespace SDIZO {
    class FileReader {
        private:
            std::ifstream file;
        public:
            FileReader(std::string fileName);
            ~FileReader();
            static bool fileExists(std::string fileName);
            virtual std::string getData();
            virtual bool isData();
    };
}