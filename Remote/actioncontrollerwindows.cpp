#include "actioncontrollerwindows.h"
#include <windows.h>
#include <QDebug>

#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QDateTime>

ActionControllerWindows::ActionControllerWindows(Notifiable *output, std::vector<Card::data> *cards):
    output(output)
    ,cards(cards)
{}

void ActionControllerWindows::play() {
    qDebug() << "PLAY";
    output->notify("", "Play", "Play / Pause gesture detected");
    keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);               // Key down
    keybd_event(VK_MEDIA_PLAY_PAUSE, 0, KEYEVENTF_KEYUP, 0); // Key up
}

void ActionControllerWindows::mute() {
    qDebug() << "MUTE";
    output->notify("", "Mute", "Mute gesture detected");
    keybd_event(VK_VOLUME_MUTE, 0, 0, 0);               // Key down
    keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0); // Key up
}

void ActionControllerWindows::backward() {
    qDebug() << "BACKWARD";
    output->notify("", "Backward", "Backward gesture detected");
    keybd_event(VK_LEFT, 0, 0, 0);               // Key down
    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0); // Key up

}

void ActionControllerWindows::forward() {
    qDebug() << "FORWARD";
    output->notify("", "Forward", "Backward gesture detected");
    keybd_event(VK_RIGHT, 0, 0, 0);               // Key down
    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0); // Key up
}

void ActionControllerWindows::previous() {
    output->notify("", "Previous", "Previous track gesture detected");
    keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0);
    keybd_event(VK_MEDIA_PREV_TRACK, 0, KEYEVENTF_KEYUP, 0);
}

void ActionControllerWindows::next() {
    output->notify("", "Next", "Next track gesture detected");
    keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0);
    keybd_event(VK_MEDIA_NEXT_TRACK, 0, KEYEVENTF_KEYUP, 0);
}

void ActionControllerWindows::screenshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        return;

    QPixmap screenshot = screen->grabWindow(0);
    QString filename = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".png";
    screenshot.save(filename, "PNG");

    qDebug() << "Screenshot saved to" << filename;

    output->notify("", "Screenshot", "Screenshot saved to " + filename);
}

void ActionControllerWindows::actionDispatch(Gesture gesture) {
    Action action = NO_ACTION;
    for (Card::data temp_gesture : *cards){
        if (temp_gesture.gesture == gesture) action = temp_gesture.action;
    }

    switch (action) {
        case PLAY:
            play();
            break;
        case MUTE:
            mute();
            break;
        case BACKWARD:
            backward();
            break;
        case FORWARD:
            forward();
            break;
        case PREVIOUS:
            previous();
            break;
        case NEXT:
            next();
            break;
        case SCREENSHOT:
            screenshot();
        default:
            break;
        }
}

void ActionControllerWindows::updateData(std::vector<Card::data> *cards) {
    this->cards = cards;
}
