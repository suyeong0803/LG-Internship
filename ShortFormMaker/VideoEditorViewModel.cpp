#include "VideoEditorViewModel.h"
#include "test.h"
#include <QDebug>
//#include <QObject>

VideoEditorViewModel::VideoEditorViewModel(QObject* parent)
    : QObject{ parent },
    m_inputInfo("")
{

}

VideoEditorViewModel::~VideoEditorViewModel()
{

}

void VideoEditorViewModel::setInputInfo(QString str)
{
    Test* test=new Test();
    std::string res=test->getStr(str.toStdString());
    m_inputInfo = QString(res.c_str());
    emit this->inputInfoChanged();

//    setRangeSlider(208645);
    setRangeSlider(365233);
    setFileList(res.c_str());
    delete test;
}

void VideoEditorViewModel::setRangeSlider(double duration)
{
    m_rangeSliderDuration=duration;
    emit this->rangeSliderChanged();
}

QString VideoEditorViewModel::inputInfo() {
    return m_inputInfo;
}

double VideoEditorViewModel::rangeSliderDuration(){
    return m_rangeSliderDuration;
}

//double VideoEditorViewModel::fromRangeSlider(){
//    return m_rangeSliderFrom;
//}

//double VideoEditorViewModel::toRangeSlider(){
//    return m_rangeSliderTo;
//}

void VideoEditorViewModel::setFileList(QString str){
    Test* test=new Test();
    std::vector<videoInfo> videoinfo=test->getInfo(str.toStdString());
    FileStruct fileStruct;
    std::vector<videoInfo>::iterator iter;
    for(int i=0;i<videoinfo.size();i++){
        m_fileList.push_back(videoinfo[i]);
    }
//    m_fileList.push_back(fileStruct);
    std::string str1="";
    str1+="파일명\t 파일길이\t 파일경로\n";
    for(int i=0;i<m_fileList.size();i++){
        str1+=m_fileList[i].getVideoInfoName()+" "+std::to_string(m_fileList[i].getVideoInfoDuration())+" "+m_fileList[i].getVideoInfoPath()+"\n";
    }
    m_fileInfo=QString::fromStdString(str1);
    emit this->inputInfoChanged();
    delete test;
}

QString VideoEditorViewModel::fileInfo(){
//    std::string str="";
//    for(int i=0;i<m_fileList.size();i++){
//        str+=m_fileList[i].getVideoInfoName()+" "+std::to_string(m_fileList[i].getVideoInfoDuration())+" "+m_fileList[i].getVideoInfoPath()+"\n";
//    }
//    m_fileInfo=QString::fromStdString(str);
    return m_fileInfo;
}

//int VideoEditorViewModel::getListSize()
//{
//    return m_fileList.size();
//}

//QString VideoEditorViewModel::getListName(int index)
//{
//    return m_fileList.at(index).name;
//}

//QString VideoEditorViewModel::getListPath(int index)
//{
//    return m_fileList.at(index).path;
//}

//double VideoEditorViewModel::getListDuration(int index)
//{
//    return m_fileList.at(index).duration;
//}
