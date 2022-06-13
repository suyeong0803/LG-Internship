#ifndef VIDEOEDITORVIEWMODEL_H
#define VIDEOEDITORVIEWMODEL_H

#include <QObject>

class VideoEditorViewModel : public QObject
{
    Q_OBJECT
public:
    explicit VideoEditorViewModel(QObject* parent = nullptr);
    virtual ~VideoEditorViewModel();
        //void setInputInfo(QString str);
        Q_INVOKABLE void setInputInfo(QString str);
        Q_INVOKABLE QString inputInfo();
        Q_INVOKABLE void setRangeSlider(double from,double to);
        Q_INVOKABLE double fromRangeSlider();
        Q_INVOKABLE double toRangeSlider();
signals:
    void folderChanged();
    void inputInfoChanged();
    void rangeSliderChanged();
//    void playing();
private:
    QString m_inputInfo;
    double m_rangeSliderFrom;
    double m_rangeSliderTo;
};

#endif // VIDEOEDITORVIEWMODEL_H
