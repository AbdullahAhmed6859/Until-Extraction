#include "StateMachine.hpp"

StateMachine::StateMachine() = default;
StateMachine::~StateMachine() = default;



void StateMachine::addState(StateRef newS, const bool isRepl) {
    isAdding = true;
    isReplacing = isRepl;
    newState = std::move(newS);
}

void StateMachine::removeState() {
    isRemoving = true;
}

void StateMachine::processStateChanges() {
    if (isRemoving && !states.empty()) {
        states.pop();
        if (!states.empty())
            states.top()->resume();

        isRemoving = false;
    }

    if (isAdding) {
        if (!states.empty()) {
            if (isReplacing)
                states.pop();
            else
                states.top()->pause();
        }
        // Use std::move here
        states.push(std::move(newState));
        states.top()->init();
        isAdding = false;
    }
}

StateRef& StateMachine::getCurrentState() {
    return states.top();
}

