#include "actioncontroller.h"

void ActionController::actionDispatch(Gesture gesture) {
    switch (gesture) {
    case DOWNWARD_SWIPE:
        play();
        break;
    case UPWARD_SWIPE:
        mute();
        break;
    case LEFTWARD_SWIPE:
        backward();
        break;
    case RIGHTWARD_SWIPE:
        forward();
    }
}
