#ifndef PRESET_H
#define PRESET_H

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include "card.h"

class Preset : public QPushButton
{
public:
    Preset(QWidget *parent, QWidget *content_widget, QGridLayout *layout, unsigned int index);
    ~Preset();
    void enable();
    void disable();

private:
    QWidget *card_container;
    QGridLayout *layout;
    std::vector<Card::data> cards;
};

#endif // PRESET_H
