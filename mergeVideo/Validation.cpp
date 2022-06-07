#include <iostream>
#include <filesystem>
#include "Validation.h"

int Validation::isExisted(std::string path) {
	if (std::filesystem::exists(path)) {
		return FILE_EXISTS;
	}
	else {
		return DO_NOT_FILE_EXIST;
	}
}