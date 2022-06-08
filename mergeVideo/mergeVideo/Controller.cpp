#include <iostream>
#include "Controller.h"
#include "Merge.h"

Controller::Controller() {}

void Controller::callMerge(std::string filePath1, std::string filePath2, std::string savePath) {
	Merge* merge = new Merge(filePath1, filePath2, savePath);
	merge->merge();
	delete merge;
}