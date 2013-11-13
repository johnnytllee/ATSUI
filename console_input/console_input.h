#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <QObject>
#include <QKeyEvent>
#include <QThread>

class console_input : public QThread
{
    Q_OBJECT
public:
    void run();
signals:
    void key_clicked(QKeyEvent *e);
};

#endif // CONSOLE_INPUT_H
