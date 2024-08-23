#ifndef QQMUSIC_H
#define QQMUSIC_H

#include <QWidget>

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
    int width = 1024;
    int height = 600;

private:
    Ui::QQMusic *ui;
};

#endif // QQMUSIC_H
