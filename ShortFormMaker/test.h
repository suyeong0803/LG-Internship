#pragma once
#include <string>
#include <vector>
#include "videoInfo.h"
class Test {
    std::string m_str;
    std::vector<videoInfo> m_videoInfo;

//    videoInfo* videoInfo;
public:
    Test() {};
    std::string getStr(std::string str);
    std::vector<videoInfo> getInfo(std::string str);

};


