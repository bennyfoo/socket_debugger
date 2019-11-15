#include "sokit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sokit w;
    w.show();

    return a.exec();
}
