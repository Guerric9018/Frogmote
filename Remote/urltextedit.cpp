#include "urltextedit.h"

#include <QPainter>
#include <QValidator>

#include <cstdlib>

struct urlValidator : public QValidator
{
    virtual QValidator::State validate(QString &input, int &) const
    {
        for (int i = 0; i < 4; ++i) {
            auto byte = QStringView(&input[5 + i * 4], 3);
            if (byte.toInt() >= 128) {
                return Invalid;
            }
        }
        auto port = QStringView(&input[5 + 4 * 4], 4);
        if (! (port.toInt() >= 8000 && port.toInt() < 9000)) {
            return Intermediate;
        }
        return Acceptable;
    }
};

UrlTextEdit::UrlTextEdit(QWidget *parent): QLineEdit(parent) {
    setStyleSheet(R"(
        QLineEdit {
            background: transparent;
            border: none;
            font-size: 15pt;
            color: black;
        }
    )");
    setInputMask("ws://ddd.ddd.ddd.ddd:dddd;0");

    setValidator(new urlValidator());
}



