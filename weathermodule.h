#ifndef WEATHERMODULE_H
#define WEATHERMODULE_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui
{
class WeatherModule;
}

class WeatherModule : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherModule(QWidget *parent = nullptr);
    ~WeatherModule();

    void initLayout();
    void setSize(int w,int h);
    void setName(const QString name);
    void setValue(const QString value);
    void setIcon(const QPixmap pix);

private:
    Ui::WeatherModule *ui;
    int width;
    int height;
    QWidget *leftWidget;
    QLabel *moduleName;
    QLabel *modulevalue;
    QLabel *moduleicon;

};

#endif // WEATHERMODULE_H
