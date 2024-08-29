#ifndef CAR_H
#define CAR_H

#include <QWidget>
#include <QLabel>
namespace Ui
{
class Car;
}

class Car : public QWidget
{
    Q_OBJECT

public:
    explicit Car(QWidget *parent = nullptr);
    ~Car();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();

private:

    Ui::Car *ui;
};

#endif // CAR_H
