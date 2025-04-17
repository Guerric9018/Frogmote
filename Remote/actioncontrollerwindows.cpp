#include "actioncontrollerwindows.h"
#include <windows.h>

ActionControllerWindows::ActionControllerWindows(QWidget *parent) {
    notifiable = new NotifiableWindows(parent);
}

void ActionControllerWindows::play() {
    keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);               // Key down
    keybd_event(VK_MEDIA_PLAY_PAUSE, 0, KEYEVENTF_KEYUP, 0); // Key up
}
