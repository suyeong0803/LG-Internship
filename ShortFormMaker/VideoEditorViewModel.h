#ifndef VIDEOEDITORVIEWMODEL_H
#define VIDEOEDITORVIEWMODEL_H

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
        Q_INVOKABLE void setInputInfo(QString str);
        Q_INVOKABLE QString inputInfo();
        Q_INVOKABLE void setRangeSlider(double duration);
        Q_INVOKABLE double rangeSliderDuration();
//        Q_INVOKABLE double fromRangeSlider();
//        Q_INVOKABLE double toRangeSlider();
//        Q_INVOKABLE int getListSize();
//        Q_INVOKABLE QString getListName(int index);
//        Q_INVOKABLE QString getListPath(int index);
//        Q_INVOKABLE double getListDuration(int index);
        Q_INVOKABLE QString fileInfo();
//        Q_INVOKABLE void setFileList();

signals:
    void folderChanged();
    void inputInfoChanged();
    void rangeSliderChanged();
private:
    QString m_inputInfo;
    double m_rangeSliderDuration;
    std::vector<videoInfo> m_fileList;
    QString m_fileInfo;
};

#endif // VIDEOEDITORVIEWMODEL_H
