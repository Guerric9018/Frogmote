#ifndef PRESET_H
#define PRESET_H

#include <QPushButton>
#include <QWidget>

class Preset : public QPushButton
{
public:
    Preset(QWidget *parent, unsigned int index);
};

#endif // PRESET_H
