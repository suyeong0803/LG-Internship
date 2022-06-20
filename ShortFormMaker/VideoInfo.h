#pragma once
#include <stdio.h>
#include <string>

class videoInfo {
public:
    std::string m_name;
    int64_t startTime,endTime;
    std::string m_path;
public:
    videoInfo(){};
    videoInfo(std::string name,int64_t startTime, int64_t endTime,std::string path){
        m_name=name;
        this->startTime=startTime;
        this->endTime=endTime;
        m_path=path;
    };
//    std::string getVideoInfoName(){
//        return m_name;
//    };
//    std::string getVideoInfoPath(){
//        return m_path;
//    };
//    int64_t getVideoStartTime(){
//        return m_startTime;
//    };
//    int64_t getVideoEndTime(){
//        return m_endTime;
//    };
};

//#pragma once
//#include <stdio.h>
//#include <string>

//class videoInfo {
//public:
//    std::string m_path;
//    int64_t startTime, endTime;
//    std::string m_createDate;
//};
