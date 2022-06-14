#include "shortform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShortForm w;
    w.show();
    return a.exec();
}
