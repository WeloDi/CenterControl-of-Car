#ifndef VOICEASST_H
#define VOICEASST_H

#include <QWidget>

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

    int width = 1024;
    int height = 600;

private:
    Ui::VoiceAsst *ui;
};

#endif // VOICEASST_H
