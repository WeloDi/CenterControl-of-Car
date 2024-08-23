#ifndef GAODEMAP_H
#define GAODEMAP_H

#include <QWidget>

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

    int width = 1024;
    int height = 600;

private:
    Ui::GaoDeMAP *ui;
};

#endif // GAODEMAP_H
