#ifndef WIDGET_H
#define WIDGET_H
#include <iostream>
#include <QWidget>
#include <QScreen>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QDateTime>
#include <QGridLayout>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;
    QLabel *timeLabel;
    QLabel *dateLabel;
    QLabel *menuBar;

    void initScreen();
    void initTime();
    void initMenuBar();

private slots:
    void updateTime();
};
#endif // WIDGET_H
