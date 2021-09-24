#include "../include/utils.hpp"

bool isTableDirectoryPresent() {
	std::string tables = "tables";
	for(const auto& entry : std::filesystem::directory_iterator(".")) {
		// entry will be something like "./file_name",
		// so the first two characters ("./") need to be stripped and
		// stored in tmp
					std::string _path = entry.path();
		std::string tmp = _path.substr(2);

		// now we check to see if we have a file/directory named 'tables'
		if(tables.compare(tmp) == 0) {
			return true;
		}
	}	
	return false;
}

void createTablesDirectory() {
	if(mkdir("tables", 0777) == -1) {
		std::cout<<"Can't create tables directory\n";
	}
}
