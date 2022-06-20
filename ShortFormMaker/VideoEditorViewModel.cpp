#include "VideoEditorViewModel.h"
//#include "Editor.h"
#include "test.h"
//#include "Controller.h"
#include "interface.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
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

void VideoEditorViewModel::open(QString folderPath)
{
    Test* test=new Test();
    m_result=-1002;
//    m_result=controller->cSaveInfo(folderPath.toStdString().substr(8,folderPath.toStdString().length()));
//    if(m_result!=SUCCESS){
//        return;
//    }
//    m_result=controller->cConvert();
    if(m_result!=SUCCESS){
        emit errorDetected(m_result);
        return;
    }
    std::vector<videoInfo> videoinfo=test->getInfo(folderPath.toStdString());

//    for(int i=0;i<Editor::m_folder.size();i++){
//        m_fileList.push_back(Editor::m_folder[i]);
//    }
    for(int i=0;i<videoinfo.size();i++){
        m_fileList.push_back(videoinfo[i]);
    }
    qDebug()<<videoinfo.size();
    for(int i=0;i<m_fileList.size();i++){
        QJsonObject qjsonObj;
        qjsonObj.insert("startTime",m_fileList[i].startTime);
        qjsonObj.insert("endTime",m_fileList[i].endTime);
        qjsonObj.insert("Path",QString::fromStdString(m_fileList[i].m_path));

        qDebug()<<qjsonObj;
        m_qjsonArr.push_back(qjsonObj);
    }

    std::string str1="";
    str1+="파일경로\t 파일길이\n";
    for(int i=0;i<m_fileList.size();i++){
        str1+=m_fileList[i].m_path+" "+std::to_string(m_fileList[i].endTime-m_fileList[i].startTime)+"\n";
    }
    m_inputInfo=QString::fromStdString(str1);

    emit inputInfoChanged();

    setRangeSlider(m_fileList[m_fileList.size()-1].endTime);
//    setRangeSlider(Editor::m_folder[Editor::m_folder.size()-1].endTime);
//    setRangeSlider(389526);
//    setFileList(res.c_str());
    delete test;
}


void VideoEditorViewModel::excute(int64_t startTime,int64_t endTime,QString savePath){

    qDebug()<<savePath<<endTime<<startTime;
    m_outputInfo=savePath;
    m_result=-1003;
//    m_result=interface->iExcute(startTime,endTime,savePath.toStdString());
//    m_result=controller->cConcatAndSplit(startTime,endTime,savePath.toStdString().substr(8,savePath.toStdString().length()));
    if(m_result!=SUCCESS){
        emit errorDetected(m_result);
        return;
    }
    emit outputInfoChanged();
//    delete controller;
}


void VideoEditorViewModel::setRangeSlider(int64_t duration)
{
    m_rangeSliderDuration=duration;
    emit this->rangeSliderChanged();
}


QString VideoEditorViewModel::inputInfo() {
    return m_inputInfo;
}

QString VideoEditorViewModel::outputInfo(){
    return m_outputInfo;
}

int64_t VideoEditorViewModel::rangeSliderDuration(){
    return m_rangeSliderDuration;
}

QJsonArray VideoEditorViewModel::jsonInfo(){
    return m_qjsonArr;
}

int VideoEditorViewModel::result(){
    return m_result;
}
