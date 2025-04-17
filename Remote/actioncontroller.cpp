#include "actioncontroller.h"

void ActionController::actionDispatch(GestureHandler::Code code) {
    switch (code) {
    case GestureHandler::DOWNWARD_SWIPE:
        play();
        break;
    default:
        break;
    }
}
