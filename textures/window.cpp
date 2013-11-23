/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QWidget>
#include <QLayout>
#include <QTimer>
#include "glwidget.h"
#include "window.h"

Window::Window():
    stepsPerItem(0),
    rotate_clockwise(false)
{
#if 1
    QGridLayout *mainLayout = new QGridLayout;
    glWidgets[0][0] = new GLWidget(0, 0);
    glWidgets[0][0]->setClearColor(QColor(0,0,0,0));
//    glWidgets[0][0]->rotateBy(0 * 16, 0 * 16, 0 * 16);
    glWidgets[0][0]->rotateBy(-32 * 16, 0 * 16, 0 * 16);
    mainLayout->addWidget(glWidgets[0][0],0,0);
    connect(glWidgets[0][0], SIGNAL(clicked()),
            this, SLOT(setCurrentGlWidget()));
#else
    QGridLayout *mainLayout = new QGridLayout;

    for (int i = 0; i < NumRows; ++i) {
        for (int j = 0; j < NumColumns; ++j) {
            QColor clearColor;
            clearColor.setHsv(((i * NumColumns) + j) * 255
                              / (NumRows * NumColumns - 1),
                              255, 63);

            glWidgets[i][j] = new GLWidget(0, 0);
            glWidgets[i][j]->setClearColor(clearColor);
            glWidgets[i][j]->rotateBy(-32 * 16, 0 * 16, 0 * 16);
            mainLayout->addWidget(glWidgets[i][j], i, j);

            connect(glWidgets[i][j], SIGNAL(clicked()),
                    this, SLOT(setCurrentGlWidget()));
        }
    }
#endif
    setLayout(mainLayout);

    currentGlWidget = glWidgets[0][0];

    QTimer *timerItem = new QTimer(this);
    connect(timerItem, SIGNAL(timeout()), this, SLOT(rotateOneItem()));
    timerItem->start(3000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
    timer->start(20);

    setWindowTitle(tr("ATSUI - Asdt Tpv Superior User Interface"));
}

void Window::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Left:
        rotate_clockwise = false;
        break;
    case Qt::Key_Right:
        rotate_clockwise = true;
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}

void Window::setCurrentGlWidget()
{
    currentGlWidget = qobject_cast<GLWidget *>(sender());
}

void Window::rotateOneItem()
{
    stepsPerItem = STEPS_PER_ITEM;
}

void Window::rotateOneStep()
{
    if (stepsPerItem) {
        stepsPerItem--;
        if (currentGlWidget)
            currentGlWidget->rotateBy(0 * 16, (rotate_clockwise?1:-1) * 16, 0 * 16);
    }
}
