#include "preset.h"

Preset::Preset(QWidget *parent, QWidget *content_widget, QGridLayout *layout, unsigned int index, std::vector<Card::data> &cards, ActionController *actionController)
    : QPushButton(parent)
    , index(index)
    , card_container(content_widget)
    , layout(layout)
    , cards(cards)
    , actionController(actionController)
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

    resize(fixedWidth, calculatedHeight);
    setMinimumSize(fixedWidth, calculatedHeight);
    setIconSize(this->size());
    setStyleSheet("background-color: transparent; border: none;");
    setIcon(icon);

    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    addCardButton = new QPushButton(card_container);
    addCardButton->setIcon(QIcon(":/res/plus_button.png"));
    addCardButton->setIconSize(QSize( 64, 64 ));
    addCardButton->setStyleSheet("background-color: transparent; border: none;");
    connect(addCardButton, &QPushButton::clicked, this, &Preset::onAddCardClicked);

    addCardButton->hide();
    addCardButton->setParent(card_container);
}

void Preset::enable()
{
    QIcon icon(":/res/preset_selected_" + QString::number(index + 1) + ".png");
    setIcon(icon);
    setIconSize(size());
    for (size_t i = 0; i < cards.size(); ++i) {
        auto card = new Card(card_container, &cards[i]);
        layout->addWidget(card, i / 2, i % 2, Qt::AlignTop | Qt::AlignLeft);
    }

    int row = (cards.size() + 1) / 2;

    layout->addWidget(
        addCardButton,
        row,      // grid row
        0,        // start at column 0
        1,        // rowSpan = 1
        2,        // colSpan = 2
        Qt::AlignCenter
        );
    addCardButton->show();

    actionController->updateData(&cards);
}

void Preset::disable()
{
    setIcon(QIcon(":/res/preset_" + QString::number(index + 1) + ".png"));
    setIconSize(size());

    QLayoutItem *item = nullptr;
    while ((item = layout->takeAt(0))) {
        QWidget *w = item->widget();
        delete item;
        if (w && w != addCardButton)
            delete w;
    }

    addCardButton->hide();
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

void Preset::onAddCardClicked()
{
    cards.emplace_back(Card::data{ NO_GESTURE, NO_ACTION });
    auto newCard = new Card(card_container, &cards.back());
    int idx = cards.size() - 1;
    int row = idx / 2, col = idx % 2;
    layout->addWidget(newCard,
                      row, col,
                      Qt::AlignTop | Qt::AlignLeft);

    int buttonRow = (cards.size() + 1) / 2;
    layout->addWidget(addCardButton,
                      buttonRow,
                      0,
                      1,
                      2,
                      Qt::AlignCenter);
    addCardButton->show();

    actionController->updateData(&cards);
}
