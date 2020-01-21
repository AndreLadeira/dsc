#include "execution_controller.h"

using namespace core;

__Trigger::__Trigger(std::string id):Identified<std::string>(id){}


ExecutionController::ExecutionController():_stoppingTrigger("Error: no stop trigger set."){}

bool ExecutionController::restart(){

    if ( restartTriggers.empty() ) return false;

    for( auto trigger : restartTriggers )
        if (*trigger) return true;
    return false;
}
bool ExecutionController::stop(){

    if ( stopTriggers.empty() ) return true;

    for( auto trigger : stopTriggers )
        if (*trigger) { _stoppingTrigger = trigger->getId(); return true; }
    return false;
}

void ExecutionController::addRestartTrigger( trigger_ptr_t t){
    restartTriggers.push_back(t);
}
void ExecutionController::addStopTrigger( trigger_ptr_t t){
    stopTriggers.push_back(t);
}

std::string ExecutionController::getStoppingTrigger()
{
    return this->_stoppingTrigger;
}

