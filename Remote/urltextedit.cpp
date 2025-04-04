#include "urltextedit.h"

#include <QPainter>

UrlTextEdit::UrlTextEdit(QWidget *parent): QLineEdit(parent) {
    setStyleSheet(R"(
        QLineEdit {
            background: transparent;
            border: none;
            font-size: 15pt;
            color: black;
            padding-left: 0px;
            padding-top: 0px;
        }
    )");
}



