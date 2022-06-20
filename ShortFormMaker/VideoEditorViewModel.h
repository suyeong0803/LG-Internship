#ifndef VIDEOEDITORVIEWMODEL_H
#define VIDEOEDITORVIEWMODEL_H

#include <QJsonArray>
#include <QObject>
#include <vector>
#include "VideoInfo.h"

struct FileStruct{
    QString name="";
    QString path="";
    double duration=0;
};

class VideoEditorViewModel : public QObject
{
    Q_OBJECT
public:
    explicit VideoEditorViewModel(QObject* parent = nullptr);
    virtual ~VideoEditorViewModel();
    //void setInputInfo(QString str);
    Q_INVOKABLE void setFileList(QString str);
//    Q_INVOKABLE int open(QString str);
    Q_INVOKABLE void open(QString str);
    Q_INVOKABLE void excute(int64_t startTime,int64_t endTime,QString savePath);
    Q_INVOKABLE QString inputInfo();
    Q_INVOKABLE void setRangeSlider(int64_t duration);
    Q_INVOKABLE int64_t rangeSliderDuration();
    Q_INVOKABLE QString outputInfo();
    Q_INVOKABLE QVector<videoInfo> fileInfo();
    Q_INVOKABLE int result();
//    Q_INVOKABLE QJsonArray toJson(const std::vector<videoInfo>& myVec);
//    Q_INVOKABLE QJsonArray jsonInfo();
    Q_INVOKABLE QVariant fileInfo2();
signals:
    void folderChanged();
    void inputInfoChanged();
    void rangeSliderChanged();
    void outputInfoChanged();
private:
    QString m_inputInfo;
    int64_t m_rangeSliderDuration;
    std::vector<videoInfo> m_fileList;
    QString m_outputInfo;
    QVector<videoInfo> m_fileInfo;
    QVariant m_fileInfo2;
//    QJsonArray m_jsonInfo;
    int m_result;

//    QList m_file
};

#endif // VIDEOEDITORVIEWMODEL_H
