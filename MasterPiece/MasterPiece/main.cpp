#include "masterpiece.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterPiece w;
    w.show();

    return a.exec();
}
