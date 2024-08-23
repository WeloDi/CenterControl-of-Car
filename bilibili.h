#ifndef BILIBILI_H
#define BILIBILI_H

#include <QWidget>

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

    int width = 1024;
    int height = 600;

private:
    Ui::BiLiBiLi *ui;
};

#endif // BILIBILI_H
