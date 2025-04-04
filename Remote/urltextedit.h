#ifndef URLTEXTEDIT_H
#define URLTEXTEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QSvgRenderer>

class UrlTextEdit: public QLineEdit
{
    Q_OBJECT
public:
    UrlTextEdit(QWidget *parent);
private:
    QPixmap backgroundPixmap;
};

#endif // URLTEXTEDIT_H
