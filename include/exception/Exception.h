namespace SDIZO {
    class Exception {
        private:
            char* message;
        public:
            Exception(char* message);
            ~Exception();
            virtual char* getMessage();
    };
}