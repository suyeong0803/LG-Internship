#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "Merge.h"

Merge::Merge() {}

Merge::Merge(std::string filePath1, std::string filePath2, std::string savePath) {
	m_filePath1 = filePath1;
	m_filePath2 = filePath2;
	m_savePath = savePath;
}

void Merge::makeTXTFile() {
	std::ofstream writeFile("list.txt");
	writeFile << "file " << m_filePath1;
	writeFile << std::endl;
	writeFile << "file " << m_filePath2;
	writeFile.close();
}

bool Merge::isConverted() {
	if (std::filesystem::path(m_filePath1).extension().compare(std::filesystem::path(m_filePath2).extension()) != 0) {
		return false;
	}
	else {
		return true;
	}
}

int Merge::merge() {
	makeTXTFile();
	if (isConverted()) {
		std::string command = "ffmpeg -f concat -i list.txt -c copy " + m_savePath;
		system(command.c_str());
		return SUCCESS_MERGE;
	}
	else {
		return IS_NOT_CONVERTED;
	}
}