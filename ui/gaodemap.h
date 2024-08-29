#ifndef GAODEMAP_H
#define GAODEMAP_H

#include <QWidget>
#include <QLabel>
namespace Ui
{
class GaoDeMAP;
}

class GaoDeMAP : public QWidget
{
    Q_OBJECT

public:
    explicit GaoDeMAP(QWidget *parent = nullptr);
    ~GaoDeMAP();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();

private:
    Ui::GaoDeMAP *ui;
};

#endif // GAODEMAP_H
