#include <iostream>
#include <string>
#include "interface.h"
#include "Controller.h"

Controller *controller=new Controller();

//Interface::Interface(){};
//Interface::~Interface(){};
int Interface::iOpen(std::string folderPath){
    int value= controller->cSaveInfo(folderPath);
    if(value!=SUCCESS){
        return value;
    }
    else{
        return controller->cConvert();
    }
}

int Interface::iExcute(int64_t startTime,int64_t endTime,std::string finalOutput){
   return controller->cConcatAndSplit(startTime,endTime,finalOutput);
}
