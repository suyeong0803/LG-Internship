#ifndef SHORTFORM_H
#define SHORTFORM_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ShortForm; }
QT_END_NAMESPACE

class ShortForm : public QDialog
{
    Q_OBJECT

public:
    ShortForm(QWidget *parent = nullptr);
    ~ShortForm();

private slots:
    void on_open_clicked();

private:
    Ui::ShortForm *ui;
};
#endif // SHORTFORM_H
