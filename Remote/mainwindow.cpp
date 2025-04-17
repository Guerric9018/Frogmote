#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "urlbar.h"
#include "settingsbutton.h"
#include "preset.h"
#include "card.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

#include "notifiable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Notifiable *notifiable = new Notifiable(this);
    client = new Client(notifiable);

    ui->setupUi(this);

    setFixedSize(750, 550);
    setWindowTitle("Remote Desktop");

    // Background color
    setStyleSheet("background-color: rgb(201, 247, 192);");

    // --- Main Layout ---
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(20);

    // Top margin
    QWidget *top_margin = new QWidget(this);
    top_margin->setFixedHeight(5);
    mainLayout->addWidget(top_margin);

    // --- Top Layout: Url and settings ---
    QHBoxLayout *topLayout = new QHBoxLayout;
    mainLayout->addLayout(topLayout);

    // Left margin
    QWidget *left_margin = new QWidget(this);
    left_margin->setFixedWidth(50);
    topLayout->addWidget(left_margin);

    // Url
    UrlBar *textEdit = new UrlBar(this, notifiable, client);
    topLayout->addWidget(textEdit);

    // Settings
    SettingsButton *settingsButton = new SettingsButton(this);
    topLayout->addWidget(settingsButton);


    // --- Bottom Layout: presets and cards ---
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    mainLayout->addLayout(bottomLayout);

    // Preset buttons
    QWidget *presetsContainer = new QWidget(this);
    presetsContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    bottomLayout->addWidget(presetsContainer);

    for (unsigned int i = 4; i > 0; i--) {
        Preset *preset = new Preset(presetsContainer, i);
        int yOffset = (i - 1) * 90;
        if (i == 1) yOffset += 20;
        preset->setGeometry(0, yOffset, preset->width(), preset->height());
    }

    // Cards
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setFixedWidth(650);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    bottomLayout->addWidget(scrollArea);

    QWidget *contentWidget = new QWidget;
    contentWidget->setFixedWidth(650);
    scrollArea->setWidget(contentWidget);

    QGridLayout *gridLayout = new QGridLayout(contentWidget);
    gridLayout->setVerticalSpacing(15);
    contentWidget->setLayout(gridLayout);

    for (unsigned int i = 0; i < 30; i++) {
        Card *card = new Card(contentWidget);
        gridLayout->addWidget(card, i / 2, i % 2);
    }


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
