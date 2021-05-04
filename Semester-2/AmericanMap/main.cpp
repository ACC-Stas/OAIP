#include "View/Map.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Map map;
    map.show();
    return QApplication::exec();
}