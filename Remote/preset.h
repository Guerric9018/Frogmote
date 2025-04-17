#ifndef PRESET_H
#define PRESET_H

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include "card.h"

class Preset : public QPushButton
{
public:
    Preset(QWidget *parent, QWidget *content_widget, QGridLayout *layout, unsigned int index);
    ~Preset();
    void enable();
    void disable();

private:
    unsigned int index;
    QWidget *card_container;
    QGridLayout *layout;
    std::vector<Card::data> cards;

    void showEvent(QShowEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    QPropertyAnimation *animation;
    QRect original_geometry;
    QRect hover_geometry;
    bool geometry_initialized;
    double scale_factor;

    void animateTo(const QRect &target);
};

#endif // PRESET_H
