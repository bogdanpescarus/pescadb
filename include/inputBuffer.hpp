#include <iostream>
#include <string>
#include <vector>
#include <fstream>

enum inputType {
    INVALID = 0,
    CREATE_TABLE = 1,
    UPDATE_TABLE = 2
};

class InputBuffer {
    private:
        std::string inputString;
        inputType type;

    public:
        InputBuffer(std::string);
        int checkMeta(std::string);
        void setInputType();
        int getInputType();

        std::vector<std::string> tokenizeString(std::string);
        int execCommand();
        int createTable(std::vector<std::string>);
        int updateTable(std::vector<std::string>);
};






