#ifndef INTERFACE_H
#define INTERFACE_H

#endif // INTERFACE_H

#include <iostream>
#include "Editor.h"

class Interface{
public:
    Interface(){};
    ~Interface(){};
    int iOpen(std::string folderPath);
//    int iConvert();
    int iExcute(int64_t startTime,int64_t endTime,std::string finalOuput);
};
