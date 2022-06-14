#include "shortform.h"
#include "ui_shortform.h"
#include <QFileDialog>
#include <QDebug>

ShortForm::ShortForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShortForm)
{
    ui->setupUi(this);
}

ShortForm::~ShortForm()
{
    delete ui;
}


void ShortForm::on_open_clicked()
{
    QString dir1=QFileDialog::getExistingDirectory(this,"파일 선택",QDir::currentPath(),QFileDialog::ShowDirsOnly);
//    std::string str=dir1.toStdString();
    ui->InputValue->setPlainText(dir1);
}

