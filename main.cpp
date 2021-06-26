#include "Widget/Widget.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget widget;
    widget.setWindowTitle("Prototype 1");
    widget.show();
    //simu.showFullScreen();

    return a.exec();
}
