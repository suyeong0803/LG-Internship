#include "VideoEditorViewModel.h"
//#include "Editor.h"
#include "test.h"
//#include "Controller.h"
#include "interface.h"
#include <QDebug>
//#include <QObject>

//Controller* controller=new Controller();
Interface *interface=new Interface();
//int result=0;

VideoEditorViewModel::VideoEditorViewModel(QObject* parent)
    : QObject{ parent },
    m_inputInfo("")
{

}

VideoEditorViewModel::~VideoEditorViewModel()
{

}

void VideoEditorViewModel::open(QString str)
{
    Test* test=new Test();
    m_result=interface->iOpen(str.toStdString());
//    if(m_result!=SUCCESS){
//        return;
//    }
//    m_result=controller->cConvert();
    std::vector<videoInfo> videoinfo=test->getInfo(str.toStdString());
//    FileStruct fileStruct;
//    for(int i=0;i<Editor::m_folder.size();i++){
//        m_fileList.push_back(Editor::m_folder[i]);
//    }
    for(int i=0;i<videoinfo.size();i++){
        m_fileList.push_back(videoinfo[i]);
        m_fileInfo.push_back(videoinfo[i]);
    }

    m_fileInfo2.setValue(m_fileInfo);

//    for(int i=0;i<m_fileInfo.size();i++){
//        m_fileInfo2<<m_fileInfo[i];
//    }

//    m_fileList.push_back(fileStruct);
    std::string str1="";
    str1+="파일경로\t 파일길이\n";
    for(int i=0;i<m_fileList.size();i++){
        str1+=m_fileList[i].m_path+" "+std::to_string(m_fileList[i].endTime-m_fileList[i].startTime)+"\n";
    }
    m_inputInfo=QString::fromStdString(str1);
    emit this->inputInfoChanged();

//    setRangeSlider(365233);
//    setRangeSlider(Editor::m_folder[Editor::m_folder.size()-1].endTime);
    setRangeSlider(389526);
//    setFileList(res.c_str());
    delete test;
}

//int VideoEditorViewModel::open(QString str)
//{
//    Test* test=new Test();
//    m_result=interface->iOpen(str.toStdString());
////    if(m_result!=SUCCESS){
////        return;
////    }
////    m_result=controller->cConvert();
//    if(m_result==SUCCESS){
//    std::vector<videoInfo> videoinfo=test->getInfo(str.toStdString());
////    FileStruct fileStruct;
////    for(int i=0;i<Editor::m_folder.size();i++){
////        m_fileList.push_back(Editor::m_folder[i]);
////    }

//    for(int i=0;i<videoinfo.size();i++){
//        m_fileList.push_back(videoinfo[i]);
//    }

////    m_fileList.push_back(fileStruct);
//    std::string str1="";
//    str1+="파일경로\t 파일길이\n";
//    for(int i=0;i<m_fileList.size();i++){
//        str1+=m_fileList[i].m_path+" "+std::to_string(m_fileList[i].endTime-m_fileList[i].startTime)+"\n";
//    }
//    m_inputInfo=QString::fromStdString(str1);
//    emit this->inputInfoChanged();

////    setRangeSlider(365233);
////    setRangeSlider(Editor::m_folder[Editor::m_folder.size()-1].endTime);
//    setRangeSlider(389526);}
////    setFileList(res.c_str());
////    delete test;
//    return m_result;
//}


void VideoEditorViewModel::excute(int64_t startTime,int64_t endTime,QString savePath){
//    Controller* controller=new Controller();
//    controller->cConvert();
    qDebug()<<savePath<<endTime<<startTime;
    m_outputInfo=savePath;
    m_result=interface->iExcute(startTime,endTime,savePath.toStdString());
    if(m_result!=SUCCESS){
        return;
    }
    emit this->outputInfoChanged();
//    delete controller;
}


void VideoEditorViewModel::setRangeSlider(int64_t duration)
{
    m_rangeSliderDuration=duration;
    emit this->rangeSliderChanged();
}

QString VideoEditorViewModel::inputInfo() {
//    std::string str1="";
//    str1+="파일경로\t 파일길이\n";
//    for(int i=0;i<m_fileList.size();i++){
//        str1+=m_fileList[i].m_path+" "+std::to_string(m_fileList[i].endTime-m_fileList[i].startTime)+"\n";
//    }
//    m_inputInfo=QString::fromStdString(str1);
//    emit this->inputInfoChanged();

    return m_inputInfo;
}

QString VideoEditorViewModel::outputInfo(){
    return m_outputInfo;
}

int64_t VideoEditorViewModel::rangeSliderDuration(){
    return m_rangeSliderDuration;
}

void VideoEditorViewModel::setFileList(QString str){
//    Test* test=new Test();
//    std::vector<videoInfo> videoinfo=test->getInfo(str.toStdString());
//    FileStruct fileStruct;
//    std::vector<videoInfo>::iterator iter;
//    for(int i=0;i<videoinfo.size();i++){
//        m_fileList.push_back(videoinfo[i]);
//    }
//    m_fileList.push_back(fileStruct);
//    std::string str1="";
//    str1+="파일명\t 파일길이\t 파일경로\n";
//    for(int i=0;i<m_fileList.size();i++){
//        str1+=m_fileList[i].getVideoInfoName()+" "+std::to_string(m_fileList[i].getVideoInfoDuration())+" "+m_fileList[i].getVideoInfoPath()+"\n";
//    }
//    m_fileInfo=QString::fromStdString(str1);
//    emit this->inputInfoChanged();
//    delete test;
}

QVector<videoInfo> VideoEditorViewModel::fileInfo(){
//    std::string str="";
//    for(int i=0;i<m_fileList.size();i++){
//        str+=m_fileList[i].getVideoInfoName()+" "+std::to_string(m_fileList[i].getVideoInfoDuration())+" "+m_fileList[i].getVideoInfoPath()+"\n";
//    }
//    m_fileInfo=QString::fromStdString(str);
    return m_fileInfo;
}

QVariant VideoEditorViewModel::fileInfo2(){
    return m_fileInfo2;
}

//QJsonArray VideoEditorViewModel::jsonInfo(){
//    return toJson(m_fileList);
//}

int VideoEditorViewModel::result(){
    return m_result;
}

//QJsonArray toJson(const std::vector<videoInfo>& myVec) {
//    QJsonArray result;
//    std::copy (myVec.begin(), myVec.end(), std::back_inserter(result));
//    return result;
//}

