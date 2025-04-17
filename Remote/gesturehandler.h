#ifndef GESTUREHANDLER_H
#define GESTUREHANDLER_H

#include <QWidget>
#include <QObject>
#include <QJsonObject>
#include <QVector3D>
#include <QElapsedTimer>

class GestureHandler : public QObject
{
    Q_OBJECT
public:
    GestureHandler(QObject *parent = nullptr);
    void processData(const QJsonObject &data);
private:
    enum State {
        STANDBY,
        WAITING,
        GESTURING,
        END
    };

    enum Code {
        RIGHTWARD_SWIPE,
        LEFTWARD_SWIPE,
        UPWARD_SWIPE,
        DOWNWARD_SWIPE
    };

    void handleCompletion(QVector3D diff);

    State state = STANDBY;
    QVector3D last_value = {0, 0, 0};
    QVector3D first_value = {0, 0, 0};

    QElapsedTimer timer;
    double last_timestamp = 0;

    int rotation_periods = 0;
    int no_rotation_periods = 0;

    const int ROTATION_THRESHOLD = 2;
    const int NO_ROTATION_THRESHOLD = 10;

signals:
    void gestureDetected(int code);
};

#endif // GESTUREHANDLER_H
