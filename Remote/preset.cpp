#include "preset.h"

Preset::Preset(QWidget *parent, QWidget *content_widget, QGridLayout *layout, unsigned int index, const std::vector<Card::data> &cards)
    : QPushButton(parent)
    , card_container(content_widget)
    , layout(layout)
    , cards(cards)
{
    QString filename = ":/res/preset_" + QString::number(index + 1) + ".png";
    QIcon icon(filename);
    QPixmap pixmap = icon.pixmap(icon.availableSizes().first());
    float aspectRatio = float(pixmap.height()) / pixmap.width();

    int fixedWidth = 60;
    int calculatedHeight = int(fixedWidth * aspectRatio);

    setFixedSize(fixedWidth, calculatedHeight);
    setIconSize(this->size());
    setStyleSheet("background-color: transparent; border: none;");
    setIcon(icon);
}

void Preset::enable()
{
    for (size_t i = 0; i < cards.size(); ++i) {
        auto card = new Card(card_container, cards[i]);
        layout->addWidget(card, i / 2, i % 2);
    }
}

void Preset::disable()
{
    for (QLayoutItem *item; (item = layout->takeAt(0)); ) {
        delete item->widget();
    }
}
