#ifndef CTRLCENTER_H
#define CTRLCENTER_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QProcess>
#include <QString>
#include <QDebug>
namespace Ui
{
class CtrlCenter;
}

class CtrlCenter : public QWidget
{
    Q_OBJECT

public:
    explicit CtrlCenter(QWidget *parent = nullptr);
    ~CtrlCenter();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();
    void initVoice();
    void initBrightness();
private:
    Ui::CtrlCenter *ui;
    QSlider *volume;
    QSlider *brightness;

private slots:
    void onvolumeValueChanged(int value);
    void onbrightnessChanged(int value);
};

#endif // CTRLCENTER_H
