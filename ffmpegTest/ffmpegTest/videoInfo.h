/**
	@file videoInfo.h
	@brief video information for editing
*/

#pragma once
#include <stdio.h>
#include <string>

class videoInfo {
public:
	std::string m_path;
	int64_t startTime, endTime;
	std::string m_createDate;
};
