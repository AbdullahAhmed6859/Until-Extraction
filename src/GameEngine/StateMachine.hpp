#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include <stack>
#include "State.hpp"

typedef std::unique_ptr<State> StateRef;

class StateMachine {
    std::stack<StateRef> states;
    StateRef newState;
    bool isRemoving;
    bool isAdding;
    bool isReplacing;
public:
    StateMachine();
    ~StateMachine();

    void addState(StateRef newS, bool isRepl=true);
    void removeState();
    void processStateChanges();

    StateRef& getCurrentState();
};



#endif //STATEMACHINE_HPP
