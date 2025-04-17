#include "gesturehandler.h"
#include <QtMath>
#include <QJsonArray>
#include <QDebug>

GestureHandler::GestureHandler(QObject *parent)
    : QObject(parent)
{
    timer.start();
}

void GestureHandler::processData(const QJsonObject &data)
{
    if (!data.contains("values") || !data["values"].isArray())
        return;

    QJsonArray values = data["values"].toArray();
    if (values.size() < 3)
        return;

    QVector3D new_value(values[0].toDouble(), values[1].toDouble(), values[2].toDouble());

    double current_time = timer.elapsed() / 1000.0; // seconds
    double period = qMax(0.001, current_time - last_timestamp);
    last_timestamp = current_time;

    double detection = (new_value - last_value).length();

    switch (state) {
    case STANDBY:
        if (detection > 0.002 / period) {
            rotation_periods++;
        } else {
            rotation_periods = 0;
        }

        if (rotation_periods >= ROTATION_THRESHOLD) {
            first_value = new_value;
            state = GESTURING;
            rotation_periods = 0;
        }
        break;

    case GESTURING:
        if (detection < 0.01 / period) {
            no_rotation_periods++;
        } else {
            no_rotation_periods = 0;
        }

        if (no_rotation_periods >= NO_ROTATION_THRESHOLD) {
            state = STANDBY;
            no_rotation_periods = 0;

            handleCompletion(new_value - first_value);

            qDebug() << current_time << "Gesture detected";
        }
        break;

    default:
        break;
    }

    last_value = new_value;

    if (state == BOOTING) state = STANDBY;
}

void GestureHandler::handleCompletion(QVector3D diff){
    float abs_x = std::abs(diff.x());
    float abs_y = std::abs(diff.y());
    float abs_z = std::abs(diff.z());

    if (abs_x >= abs_y && abs_x >= abs_z) {
        if(diff.x() >= 0) emit gestureDetected(RIGHTWARD_SWIPE);
        else emit gestureDetected(LEFTWARD_SWIPE);
    }
    else if (abs_y >= abs_x && abs_y >= abs_z) {
        if(diff.y() >= 0) emit gestureDetected(DOWNWARD_SWIPE);
        else emit gestureDetected(UPWARD_SWIPE);
    }
}
