#pragma once
#include <string>
#include "VideoInfo.h"
class Test {
    std::string m_str;
//    videoInfo* videoInfo;
public:
    Test() {};
    std::string getStr(std::string str);
    void excuteMerge();
};
