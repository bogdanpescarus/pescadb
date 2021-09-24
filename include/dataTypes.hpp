#include <iostream>
#include <string>

#define INTEGER_TYPE 0x31    // hex value for aschi char 1
#define FLOAT_TYPE   0x32
#define STRING_TYPE  0x34

class DbDataType {
    public:
        int type;
        DbDataType();
        DbDataType(int);
        virtual ~DbDataType() {};
};

class Integer : public DbDataType {
    public:
        int data;
        Integer();
        Integer(int);
        
        int getValue();
        ~Integer() {};
};

class Float : public DbDataType {
    public:
        float data;
        Float();
        Float(float);

        float getValue();
        ~Float() {};
};

class String : public DbDataType {
    public:
        std::string data;
        String();
        String(std::string);

        std::string getValue();
        ~String() {};
};

void print_prompt();
