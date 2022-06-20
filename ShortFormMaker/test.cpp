#include "test.h"

std::string Test::getStr(std::string str) {
    m_str = "폴더경로는 " + str;
    return m_str;
}

std::vector<videoInfo> Test::getInfo(std::string str){
//    m_videoInfo.push_back(videoInfo("sample1.mp4",0,117312,"D:/sample/sample1.mp4"));
//    m_videoInfo.push_back(videoInfo("sample2.mp4",117312,208982,"D:/sample/sample2.mp4"));
//    m_videoInfo.push_back(videoInfo("sample3.mp4",208982,389526,"D:/sample/sample3.mp4"));
    return m_videoInfo;
}

