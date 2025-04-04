#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "urlbar.h"

#include <QLabel>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QLabel *label = new QLabel("Hello world");
    mainLayout->addWidget(label);

    UrlBar *textEdit = new UrlBar(this);
    mainLayout->addWidget(textEdit);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
