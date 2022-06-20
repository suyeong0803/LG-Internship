#ifndef CONTROLLER_H
#define CONTROLLER_H

#endif // CONTROLLER_H

#include <iostream>
#include "Editor.h"
class Controller{
public:
    Controller(){};
    int cSaveInfo(std::string folderPath);
    int cConvert();
    int cConcatAndSplit(int64_t startTime,int64_t endTime,std::string finalOutput);
};
