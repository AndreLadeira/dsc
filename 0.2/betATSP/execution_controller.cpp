#include "execution_controller.h"

using namespace core;

bool ExecutionController::restart(){
    for( auto trigger : restartTriggers )
        if (*trigger) return true;
    return false;
}
bool ExecutionController::stop(){
    for( auto trigger : stopTriggers )
        if (*trigger) return true;
    return false;
}

void ExecutionController::addRestartTrigger( trigger_ptr_t t){
    restartTriggers.push_back(t);
}
void ExecutionController::addStopTrigger( trigger_ptr_t t){
    stopTriggers.push_back(t);
}
