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
            if (byte.toInt() >= 256) {
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
    setInputMask("ws://999.999.999.999:9999;0");

    setValidator(new urlValidator());
}



