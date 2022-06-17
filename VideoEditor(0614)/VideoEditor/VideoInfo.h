#pragma once
#include <stdio.h>
#include <string>

class videoInfo {
    std::string m_name;
    double m_duration;
    std::string m_path;
public:
    videoInfo(){};
    videoInfo(std::string name,double duration,std::string path){
        m_name=name;
        m_duration=duration;
        m_path=path;
    };
    std::string getVideoInfoName(){
        return m_name;
    };
    std::string getVideoInfoPath(){
        return m_path;
    };
    double getVideoInfoDuration(){
        return m_duration;
    };
};
