#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "preset.h"
#include "loadpresets.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Notifiable notifiable;
    Client client;
    size_t selected;
    LoadPresets load_presets;
    std::vector<std::unique_ptr<Preset>> presets;

    void selectPreset(size_t i);
};
#endif // MAINWINDOW_H
