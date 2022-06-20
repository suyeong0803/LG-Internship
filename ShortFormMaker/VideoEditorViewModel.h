#ifndef VIDEOEDITORVIEWMODEL_H
#define VIDEOEDITORVIEWMODEL_H

#include <QJsonArray>
#include <QJsonObject>
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

    Q_INVOKABLE void open(QString folderPath);
    Q_INVOKABLE void excute(int64_t startTime,int64_t endTime,QString savePath);
    Q_INVOKABLE QString inputInfo();
    Q_INVOKABLE void setRangeSlider(int64_t duration);
    Q_INVOKABLE int64_t rangeSliderDuration();
    Q_INVOKABLE QString outputInfo();
    Q_INVOKABLE int result();
    Q_INVOKABLE QJsonArray jsonInfo();

signals:
    void folderChanged();
    void inputInfoChanged();
    void rangeSliderChanged();
    void outputInfoChanged();
    void errorDetected(int error);
private:
    QString m_inputInfo;
    int64_t m_rangeSliderDuration;
    QString m_outputInfo;
    QVector<videoInfo> m_fileList;
    QJsonArray m_qjsonArr;
    int m_result;

};

#endif // VIDEOEDITORVIEWMODEL_H
