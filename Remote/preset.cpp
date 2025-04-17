#include "preset.h"

Preset::Preset(QWidget *parent, QWidget *content_widget, QGridLayout *layout, unsigned int index)
    : QPushButton(parent)
    , index(index)
    , card_container(content_widget)
    , layout(layout)
    , animation(new QPropertyAnimation(this, "geometry", this))
    , geometry_initialized(false)
    , scale_factor(1.1)
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

    resize(fixedWidth, calculatedHeight);
    setMinimumSize(fixedWidth, calculatedHeight);
    setIconSize(this->size());
    setStyleSheet("background-color: transparent; border: none;");
    setIcon(icon);

    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutQuad);
}

// TODO: save to file
Preset::~Preset()
{
}

void Preset::enable()
{
    QIcon icon(":/res/preset_selected_" + QString::number(index + 1) + ".png");
    setIcon(icon);
    setIconSize(size());
    for (size_t i = 0; i < cards.size(); ++i) {
        auto card = new Card(card_container, cards[i]);
        layout->addWidget(card, i / 2, i % 2, Qt::AlignTop | Qt::AlignLeft);
    }
}

void Preset::disable()
{
    QIcon icon(":/res/preset_" + QString::number(index + 1) + ".png");
    setIcon(icon);
    setIconSize(size());
    for (QLayoutItem *item; (item = layout->takeAt(0)); ) {
        delete item->widget();
    }
}

void Preset::showEvent(QShowEvent *event)
{
    QPushButton::showEvent(event);
    if (!geometry_initialized) {
        original_geometry = geometry();
        geometry_initialized = true;

        int newW = (int) (original_geometry.width() * scale_factor);
        int newH = (int) (original_geometry.height() * scale_factor);
        int newX = original_geometry.x() - (newW - original_geometry.width()) / 2;
        int newY = original_geometry.y() - (newH - original_geometry.height()) / 2;
        hover_geometry = QRect(newX, newY, newW, newH);
    }
}

void Preset::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
    animateTo(hover_geometry);
}

void Preset::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    animateTo(original_geometry);
}

void Preset::animateTo(const QRect &target)
{
    animation->stop();
    animation->setStartValue(geometry());
    animation->setEndValue(target);
    animation->start();
}

void Preset::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
    setIconSize(event->size());
}
