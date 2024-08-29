#ifndef QQMUSIC_H
#define QQMUSIC_H

#include <QWidget>
#include <QLabel>
namespace Ui
{
class QQMusic;
}

class QQMusic : public QWidget
{
    Q_OBJECT

public:
    explicit QQMusic(QWidget *parent = nullptr);
    ~QQMusic();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();

private:
    Ui::QQMusic *ui;
};

#endif // QQMUSIC_H
