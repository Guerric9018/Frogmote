#include "preset.h"

Preset::Preset(QWidget *parent, unsigned int index): QPushButton(parent) {
    QString filename = ":/res/preset_" + QString::number(index) + ".png";
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
