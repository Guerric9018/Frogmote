#include "settingsbutton.h"

SettingsButton::SettingsButton(QWidget *parent) : QPushButton(parent){
    setFixedSize(50, 50);
    setIconSize(this->size());
    setStyleSheet("background-color: transparent; border: none;");
    setIcon(QIcon(":/res/settings_button.png"));
}
