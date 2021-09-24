#include "../include/inputBuffer.hpp"
#include "../include/dataTypes.hpp"
#include "../include/utils.hpp"
#include <memory>
#include <sys/stat.h>

// overload the << operator to output a vector 
// into a file
std::ofstream& operator<<(std::ofstream& out, const std::vector<char>& vec) {
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        out << *it;
    }
    return out;
}

std::ofstream& operator<<(std::ofstream& out, const std::vector<std::string>& vec) {
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        out << *it;
    }
    return out;
}

InputBuffer::InputBuffer(std::string _inputString) : inputString(_inputString) {}

void InputBuffer::setInputType() {
    size_t pos = 0;
    std::string token;
    this->type = INVALID;

    if((pos = inputString.find(' ')) != std::string::npos) {
        token = inputString.substr(0, pos);    
    }

    if(token.compare("insert") == 0) {
        this->type = UPDATE_TABLE;
    }
    if(token.compare("delete") == 0) {
        this->type = UPDATE_TABLE;
    }
    if(token.compare("create") == 0) {
        this->type = CREATE_TABLE;
    }
}

int InputBuffer::getInputType() {
    return this->type;
}

std::vector<std::string> InputBuffer::tokenizeString(std::string _string) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> tokenized;

    while((pos = _string.find(' ')) != std::string::npos) {
        token = _string.substr(0, pos);
        tokenized.push_back(token);
        _string.erase(0, pos+1);
    }
    tokenized.push_back(_string);

    return tokenized;
}

int InputBuffer::execCommand() {
    std::vector<std::string> tokenized = tokenizeString(this->inputString);
    
    if(tokenized[0].compare("insert") == 0 || tokenized[0].compare("delete") == 0) {
       this->type = UPDATE_TABLE; 
       updateTable(tokenized);
    }
    if(tokenized[0].compare("create") == 0) {
        this->type = CREATE_TABLE;
        createTable(tokenized);
    }
    
    return true;
}

int InputBuffer::createTable(std::vector<std::string> _tokenized) {
    /* can't create a table with no columns */
    if(_tokenized.size() <= 2) {
        std::cout<<"Can't create table with no columns.\n";
        return -1;
    }     

//    std::cout<<_tokenized.size()<<std::endl;
//    DbDataType* columns = new DbDataType[_tokenized.size()-2];
    std::vector<DbDataType*> columns;

    std::vector<std::string> columnNames;
    /* we will parse all of the values in tokenized, 
     * except for the first two (command and table name) */
    for(int i = 2; i < _tokenized.size(); ++i) {
        if(_tokenized[i].compare("Integer") == 0) {
            /* this will also set the type = 1 */
            columns.push_back(new Integer());
            columnNames.push_back("Integer ");
        }
        else if(_tokenized[i].compare("Float") == 0) {
            columns.push_back(new Float());
            columnNames.push_back("Float ");
        }
        else if(_tokenized[i].compare("String") == 0) {
            columns.push_back(new String());
            columnNames.push_back("String ");
        } else {
            std::cout<<"Invalid type ("<<_tokenized[i]<<") specified.\n";
            return false;
        }
    }
    std::cout<<"The table has "<<columns.size()<<" columns."<<std::endl;

		// if the 'tables' directory is not present, we
		// have to create it
		if(!isTableDirectoryPresent()) {
			createTablesDirectory();
		}

		// format the name of the table -> add the extension '.tab'
		// and put the file in the './tables' directory
    std::string tableName = _tokenized[1];
    std::string tableNameFinal = "./tables/" + tableName + ".tab";
    std::ofstream outfile(tableNameFinal);
    outfile << tableNameFinal << " ";

    std::vector<char> tableHeaderMask;

    for(auto it = columns.begin(); it != columns.end(); it++) {
//        std::cout<<(*it)->data<<std::endl; 
        if(auto* x = dynamic_cast<Integer*>(*it)) {
            outfile << "Integer ";
            tableHeaderMask.push_back(INTEGER_TYPE);
        }
        else if(auto* x = dynamic_cast<Float*>(*it)) {
            outfile << "Float ";
            tableHeaderMask.push_back(FLOAT_TYPE);
        }
        else if(auto* x = dynamic_cast<String*>(*it)) {
            outfile << "String ";
            tableHeaderMask.push_back(STRING_TYPE);
        }
    }
    outfile << tableHeaderMask;
    outfile << " ";
    outfile << columns.size();;
    outfile << "\n";
    outfile << columnNames;
    std::cout<<"Table "<<tableName<<" successfully created\n";
    return true;
}

int InputBuffer::updateTable(std::vector<std::string> _tokenizedInput) {
    std::string firstLine;
    std::ifstream tableFile(_tokenizedInput[1]);

    if(!tableFile.is_open()) {
        std::cout<<"Unable to open file "<<_tokenizedInput[1]<<std::endl;
        return false;
    }

    /* process the user input, to make sure that it 
       fits the columns of the table */
    unsigned int inputNumber = 0;
    for(auto it = _tokenizedInput.begin(); it != _tokenizedInput.end(); it++) {
        std::cout<<"___   "<<*it<<std::endl;
        ++inputNumber;
    }
    
    getline(tableFile, firstLine);
    std::cout<<"This is what I read "<<firstLine<<std::endl;

    /* here we'll read the first line in the table file 
     * to see what type of values we can add in the table */
    std::vector<std::string> tableData = tokenizeString(firstLine);
    std::cout<<tableData.size()<<std::endl;

    if((inputNumber-2) != (tableData[tableData.size()-2].size())) {
        std::cout<<"Wrong number of elements inserted in table "<<tableData[0]<<std::endl;
    }

//    std::cout<<"BGD   "<<tableData[tableData.size()-2]<<std::endl;
    
    std::cout<<"tableData: ";
    for(int i = 0; i < tableData.size(); ++i) {
        std::cout<<tableData[i]<<" ";
    }
    std::cout<<std::endl;

    for(int i = 0; i < _tokenizedInput.size(); ++i) {
        std::cout<<_tokenizedInput[i]<<" ";
    }
    std::cout<<std::endl;

    unsigned int validColumnsNum = tableData[tableData.size()-2].size();
    std::string columnTypes = tableData[tableData.size()-2];    

    for(int i = 0; i < validColumnsNum; ++i) {
        if(columnTypes[i] == '1') {
            int value = 0;
            try {
                value = std::stoi(_tokenizedInput[i+2]);
                std::cout<<"Received "<<value<<std::endl;
            } catch (std::invalid_argument iaex) {
                std::cout<<"Invalid argument ("<<i<<") passed - "<<iaex.what()<<std::endl;
                return false;
            }
        }
        if(columnTypes[i] == '2') {
            float value = 0;
            try {
                value = std::stof(_tokenizedInput[i+2]);
                std::cout<<"Received "<<value<<std::endl;
            } catch (std::invalid_argument iaex) {
                std::cout<<"Invalid argument ("<<i<<") passed - "<<iaex.what()<<std::endl;
                return false;
            }
        }
        if(columnTypes[i] == '4') {
            if(std::string* value = dynamic_cast<std::string*>(&_tokenizedInput[i+2])) {
                std::cout<<"Successfully casted value to String "<<*value<<std::endl; 
            } else {
                std::cout<<"Value number "<<i<<" is of incorrect type (should be String)\n";
                return false;
            }
        }
    }



    return true;
}



