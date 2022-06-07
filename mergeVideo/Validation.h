#include <iostream>
#include <string>

#define IS_RIGHT_PATH -2
#define IS_NOT_RIGHT_PATH -3
#define FILE_EXISTS -4
#define DO_NOT_FILE_EXIST -5

class Validation {
public:
	Validation();
	int isExisted(std::string path);
};