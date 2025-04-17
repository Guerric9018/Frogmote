#include "actioncontrollerwindows.h"
#include <windows.h>
#include <QDebug>

ActionControllerWindows::ActionControllerWindows(Notifiable *output):
    output(output) {}

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
