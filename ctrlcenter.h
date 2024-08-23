#ifndef CTRLCENTER_H
#define CTRLCENTER_H

#include <QWidget>
#include <QSlider>

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

    int width = 1024;
    int height = 600;


private:
    Ui::CtrlCenter *ui;
    QSlider *volume;

private slots:
    void onvolumeValueChanged();
};

#endif // CTRLCENTER_H
