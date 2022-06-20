#include "test.h"

std::string Test::getStr(std::string str) {
    m_str = "폴더경로는 " + str;
    return m_str;
}

std::vector<videoInfo> Test::getInfo(std::string str){
    m_videoInfo.push_back(videoInfo("sample1.mp4",0,91258,"D:/videosample/sample1.mp4"));
    m_videoInfo.push_back(videoInfo("sample2.mp4",91258,182049,"D:/videosample/sample2.mp4"));
    m_videoInfo.push_back(videoInfo("sample3.mp4",182049,273841,"D:/videosample/sample3.mp4"));
    m_videoInfo.push_back(videoInfo("sample4.mp4",273841,365233,"D:/videosample/sample4.mp4"));
    return m_videoInfo;
}

