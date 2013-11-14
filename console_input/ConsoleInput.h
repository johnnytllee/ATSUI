#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H

#include <QObject>
#include <QKeyEvent>
#include <QThread>

class ConsoleInput : public QThread
{
    Q_OBJECT
public:
    void run();
signals:
    void key_clicked(QKeyEvent *e);
};

#endif // CONSOLEINPUT_H
