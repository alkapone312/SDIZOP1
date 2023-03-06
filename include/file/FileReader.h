#include <fstream>

namespace SDIZO {
    class FileReader {
        private:
            std::ifstream file;
        public:
            FileReader(char* fileName);
            ~FileReader();
            virtual void getData(char* data);
            virtual bool isData();
    };
}