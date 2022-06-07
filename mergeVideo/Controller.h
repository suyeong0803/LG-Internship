#pragma once
#include <iostream>

class Controller {
public:
	Controller() {};
	void callMerge(std::string filePath1, std::string filePath2, std::string savePath);
};