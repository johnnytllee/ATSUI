#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console_input.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c_in = new console_input;
    connect(c_in, SIGNAL(key_clicked(QKeyEvent*)), this, SLOT(received_key(QKeyEvent*)));
    c_in->start();
}

void MainWindow::received_key(QKeyEvent *e)
{
    qDebug()<<e->key();
}

MainWindow::~MainWindow()
{
    delete c_in;
    delete ui;
}
