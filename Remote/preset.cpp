#include "preset.h"

Preset::Preset(QWidget *parent, QWidget *content_widget, QGridLayout *layout, unsigned int index)
    : QPushButton(parent)
    , card_container(content_widget)
    , layout(layout)
{
    QString filename = ":/res/preset_" + QString::number(index + 1) + ".png";
    QIcon icon(filename);
    QPixmap pixmap = icon.pixmap(icon.availableSizes().first());
    float aspectRatio = float(pixmap.height()) / pixmap.width();

    int fixedWidth = 60;
    int calculatedHeight = int(fixedWidth * aspectRatio);
    // TODO: load from file
    for (int i = 0; i < 2+3*index; ++i) {
        cards.emplace_back(Card::data{i+int(index)*100+100});
    //         cards.emplace_back({i+index*100+100});
    }

    setFixedSize(fixedWidth, calculatedHeight);
    setIconSize(this->size());
    setStyleSheet("background-color: transparent; border: none;");
    setIcon(icon);
}

// TODO: save to file
Preset::~Preset()
{
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
