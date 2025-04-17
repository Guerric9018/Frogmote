#include "card.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

Card::Card(QWidget *parent, data *d)
    : QWidget{parent}, data_{d}
{
    backgroundPixmap = QPixmap(":/res/card_frame.png");
    if (backgroundPixmap.isNull()) {
        qWarning("PNG image failed to load");
    }

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    setLayout(main_layout);

    QHBoxLayout *dropdown_layout = new QHBoxLayout(this);
    main_layout->addLayout(dropdown_layout);

    QHBoxLayout *image_layout = new QHBoxLayout(this);
    main_layout->addLayout(image_layout);

    QString dropdown_stylesheet = R"(
    QComboBox {
        background-color: white;
        color: black;
    }

    QComboBox QAbstractItemView {
        background-color: white;
        color: black;
        selection-color: black;
    }
    )";

    QComboBox *gesture_dropdown = new QComboBox(this);
    gesture_dropdown->setStyleSheet(dropdown_stylesheet);
    gesture_dropdown->setPlaceholderText("Action");
    QComboBox *action_dropdown = new QComboBox(this);
    action_dropdown->setStyleSheet(dropdown_stylesheet);
    action_dropdown->setPlaceholderText("Gesture");

    QStringList gestures = {"Leftward swipe", "Rightward swipe", "Downward swipe", "Upward swipe"};
    QStringList actions = {"Play / Pause", "Mute / Unmute", "Go backward",
                           "Go forward", "Previous track", "Next track", "Screenshot"};
    gesture_dropdown->addItems(gestures);
    action_dropdown->addItems(actions);

    if (data_->gesture != NO_GESTURE) gesture_dropdown->setCurrentIndex(data_->gesture - 1);
    if (data_->action != NO_ACTION) action_dropdown->setCurrentIndex(data_->action - 1);

    connect(gesture_dropdown, &QComboBox::currentIndexChanged, this, &Card::gestureChanged);
    connect(action_dropdown, &QComboBox::currentIndexChanged, this, &Card::actionChanged);

    dropdown_layout->addWidget(gesture_dropdown);
    dropdown_layout->addWidget(action_dropdown);
    dropdown_layout->setSpacing(25);
    dropdown_layout->setContentsMargins(20, 3, 20, 3);

    main_layout->setStretch(0, 1);
    main_layout->setStretch(1, 4);

    float aspectRatio = float(backgroundPixmap.height()) / backgroundPixmap.width();

    int fixedWidth = 300;
    int calculatedHeight = int(fixedWidth * aspectRatio);

    setFixedSize(fixedWidth, calculatedHeight);
}

void Card::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QWidget::paintEvent(event);
}

Card::data Card::getData() const
{
    return *data_;
}

void Card::gestureChanged(int gesture) {
    data_->gesture = (Gesture) (gesture + 1);
}

void Card::actionChanged(int action) {
    data_->action = (Action) (action + 1);
}
