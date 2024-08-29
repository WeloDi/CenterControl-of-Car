#ifndef BILIBILI_H
#define BILIBILI_H

#include <QWidget>
#include <QLabel>
namespace Ui
{
class BiLiBiLi;
}

class BiLiBiLi : public QWidget
{
    Q_OBJECT

public:
    explicit BiLiBiLi(QWidget *parent = nullptr);
    ~BiLiBiLi();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();

private:
    Ui::BiLiBiLi *ui;
};

#endif // BILIBILI_H
