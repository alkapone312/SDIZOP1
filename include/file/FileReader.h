#include <fstream>

namespace SDIZO {
    class FileReader {
        private:
            std::ifstream file;
        public:
            FileReader(std::string fileName);
            ~FileReader();
            virtual std::string getData();
            virtual bool isData();
    };
}