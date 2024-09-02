#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QLabel>
#include <QWebEngineView>
#include <QUrl>
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

    void initScreen();

private:
    Ui::GaoDeMAP *ui;
    QLabel *wallPaper;

private slots:
};

#endif // MAP_H
