#include "widget.h"

#include <QApplication>
#include <QFont>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置默认字体
    QFont defaultFont("Microsoft YaHei");
    a.setFont(defaultFont);

    Widget w;
    w.show();
    return a.exec();
}
