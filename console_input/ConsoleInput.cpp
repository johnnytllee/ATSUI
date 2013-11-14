#include "ConsoleInput.h"
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

static int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void ConsoleInput::run()
{
    char c;
    int k = 0;
    do {
        while (!kbhit())
            usleep(100000);
        c = getchar();
        printf("[0x%x]",c);
        switch(c) {
        case 0x41:
            k = Qt::Key_Up;
            break;
        case 0x42:
            k = Qt::Key_Down;
            break;
        case 0x43:
            k = Qt::Key_Right;
            break;
        case 0x44:
            k = Qt::Key_Left;
            break;
        case 0x8:
            k = Qt::Key_Backspace;
            break;
        case 0xa:
            k = Qt::Key_Enter;
            break;
        case 0x1b: {
            if (kbhit() && getchar() == 0x5b)
                continue;
            k = Qt::Key_Escape;
        }
            break;
        default:
            continue;
        }
        QKeyEvent e(QEvent::KeyPress, k, Qt::NoModifier);
        emit key_clicked(&e);
    } while(1);
}
