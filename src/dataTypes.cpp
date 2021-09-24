#include "../include/dataTypes.hpp"

DbDataType::DbDataType() : type(0) {}

DbDataType::DbDataType(int _type) : type(_type) {}


Integer::Integer() : data(0), DbDataType(INTEGER_TYPE) {}

Integer::Integer(int _data) : data(_data) {}

int Integer::getValue() { 
    std::cout<<"Integer getValue()\n";
    return this->data; 
}


Float::Float() : data(0), DbDataType(FLOAT_TYPE) {}

Float::Float(float _data) : data(_data) {}

float Float::getValue() { 
    std::cout<<"Float getValue()\n";    
    return this->data;
}


String::String() : data(""), DbDataType(STRING_TYPE) {}

String::String(std::string _data) : data(_data) {}

std::string String::getValue() { 
    std::cout<<"String getValue()\n";    
    return this->data;
}

void print_prompt() {
    std::cout<<"db > ";
    return;
}
