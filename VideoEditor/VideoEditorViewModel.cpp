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
    setRangeSlider(0,4.45);
    delete test;
}

void VideoEditorViewModel::setRangeSlider(double from,double to)
{
    m_rangeSliderFrom=from;
    m_rangeSliderTo=to;
    emit this->rangeSliderChanged();
}

//void VideoEditorViewModel::setRangeText(double from,double to){

//}

QString VideoEditorViewModel::inputInfo() {
    return m_inputInfo;
}

double VideoEditorViewModel::fromRangeSlider(){
    return m_rangeSliderFrom;
}

double VideoEditorViewModel::toRangeSlider(){
    return m_rangeSliderTo;
}

