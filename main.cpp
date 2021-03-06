#include "./include/dataTypes.hpp"
#include "./include/inputBuffer.hpp"

int main() {

    std::string input_string;

    // load tables

    while(true) {
        print_prompt();

        getline(std::cin, input_string);
        if(input_string.compare(".exit") == 0) {
            std::cout<<"Exitting...\n";
            return 0;
        }
        InputBuffer userInput(input_string);

        userInput.execCommand();

    }

    return 0;
}
