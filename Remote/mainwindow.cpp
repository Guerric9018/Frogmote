#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "urlbar.h"
#include "settingsbutton.h"
#include "preset.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QSplashScreen>

#include "notifiable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , notifiable(this)
    , client(&notifiable)
    , selected(0)
    , presets(4)
{
    ui->setupUi(this);

    // Splash Screen
    QPixmap pixmap(":/res/splash_screen.png");
    pixmap = pixmap.scaled(QSize(300, 300), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QSplashScreen splash(pixmap);
    splash.show();

    setFixedSize(750, 550);
    setWindowTitle("Frogmote");
    setWindowIcon(QIcon(":/res/logo.png"));

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
    UrlBar *textEdit = new UrlBar(this, &notifiable, &client);
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

    // Cards
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setFixedWidth(650);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    bottomLayout->addWidget(scrollArea);

    QWidget *contentWidget = new QWidget;
    contentWidget->setFixedWidth(650);
    scrollArea->setWidget(contentWidget);
    auto gridLayout = new QGridLayout();
    gridLayout->setVerticalSpacing(15);
    contentWidget->setLayout(gridLayout);

    for (int i = 4-1; i >= 0; --i) {
        presets[i] = std::make_unique<Preset>(presetsContainer, contentWidget, gridLayout, i, load_presets.view(i));
        auto preset = presets[i].get();
        int yOffset = i * 90;
        if (i == 0) yOffset += 20;
        preset->setGeometry(0, yOffset, preset->width(), preset->height());
        connect(preset, &QPushButton::released, this, [=] () { selectPreset(i); });
    }
    presets[selected]->enable();

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectPreset(size_t i)
{
    presets[selected]->disable();
    selected = i;
    presets[selected]->enable();
}
