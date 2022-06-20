#include "Editor.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <QDebug>

int Controller::cSaveInfo(std::string folderPath){
    qDebug()<<"save 성공";
    return SUCCESS;
}

int Controller::cConvert(){
    qDebug()<<"convert 성공";
    return SUCCESS;
}

int Controller::cConcatAndSplit(int64_t startTime,int64_t endTime,std::string finalOutput){
    qDebug()<<"concatAndsplit 성공";
    return SUCCESS;
}



//	Editor *videoEditor = new Editor();
//	std::string folderPath = "D:\\00000003REC"; // -> user

//    int saveInfo(std::string folderPath){
//        int result = 100;

//        result = videoEditor->saveInfo(folderPath);
//        if (result != SUCCESS)
//        {
//            if (result == ERR_INPUTOPEN) return ERR_INPUTOPEN;
//            if (result == ERR_NOTEXIST) return ERR_NOTEXIST;
//            if (result == ERR_EMPTYFOLDER) return ERR_EMPTYFOLDER;

//            return ERR_SAVEINFO;
//        }
//        return result;
//    }

//    int convert(){
//        std::filesystem::create_directory("D:\\convert");
//        for (int i = 0; i < videoEditor->m_folder.size(); i++)
//        {
//          result = videoEditor->convert(videoEditor->m_folder[i].m_path, "D:\\convert\\output_convert" + std::to_string(i) + ".mp4");
//            if (result != SUCCESS)
//            {
//                if (result == ERR_INPUTOPEN) return ERR_INPUTOPEN;
//                return ERR_CONVERT;
//            }
//        }
//        return result;
//    }

//    int concat(int64_t startTime,int64_t endTime){
//        result = videoEditor->concat(startTime, endTime);
//        if (result < SUCCESS)
//            return ERR_CONCAT;

//        else videoEditor->setIndex(result);
//        result = videoEditor->split(videoEditor->getIndex(), startTime, endTime, final_output);
//        if (result != SUCCESS)
//        {
//            if (result == ERR_OUTPUTCREATE) return ERR_OUTPUTCREATE;
//            return ERR_SPLIT;
//        }
//    }


//	int64_t startTime = 8168160, endTime = 56297281; // -> user
//	//int64_t startTime = videoEditor->getStartTime(), endTime = videoEditor->getEndTime(); // -> user
//	result = videoEditor->concat(startTime, endTime);
//	if (result < SUCCESS)
//		return ERR_CONCAT;

//	else videoEditor->setIndex(result);



//	std::string final_output = "D:\\output.mp4";
//	//std::string final_output = videoEditor->getOutputPath();
//	result = videoEditor->split(videoEditor->getIndex(), startTime, endTime, final_output);
//	if (result != SUCCESS)
//	{
//		if (result == ERR_OUTPUTCREATE) return ERR_OUTPUTCREATE;
//		return ERR_SPLIT;
//	}

//	videoEditor->remove();

