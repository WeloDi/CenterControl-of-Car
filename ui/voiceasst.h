#ifndef VOICEASST_H
#define VOICEASST_H

#include <QWidget>
#include <QLabel>
namespace Ui
{
class VoiceAsst;
}

class VoiceAsst : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceAsst(QWidget *parent = nullptr);
    ~VoiceAsst();

    //background
    int width = 1024;
    int height = 600;
    QLabel *wallpaper;

    void initScreen();

private:
    Ui::VoiceAsst *ui;
};

#endif // VOICEASST_H
