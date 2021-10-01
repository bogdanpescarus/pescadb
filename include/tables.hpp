#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Table {
	private:
		std::string tableName;
		int numColumns;
		std::vector<DbDataType> smth;

	public:
		Table();
		// read the table from the file, then construct the object 
		Table(std::string);
};
