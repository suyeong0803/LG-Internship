#pragma once
#include <iostream>
#include <string>

#define SUCCESS_MERGE -6
#define IS_NOT_CONVERTED -7

class Merge {
	std::string m_filePath1, m_filePath2, m_savePath;
public:
	Merge();
	Merge(std::string filePath1, std::string filePath2, std::string savePath);
	void makeTXTFile();
	bool isConverted();
	int merge();
};