#include "actioncontroller.h"

void ActionController::actionDispatch(GestureHandler::Code code) {
    switch (code) {
    case GestureHandler::DOWNWARD_SWIPE:
        play();
        break;
    case GestureHandler::UPWARD_SWIPE:
        mute();
        break;
    case GestureHandler::LEFTWARD_SWIPE:
        backward();
        break;
    case GestureHandler::RIGHTWARD_SWIPE:
        forward();
    }
}
