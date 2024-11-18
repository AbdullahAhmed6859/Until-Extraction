//
// Created by Abdullah Ahmed on 11/19/2024.
//

#ifndef STATE_HPP
#define STATE_HPP



class State {
public:
    virtual ~State() = default;
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
    virtual void pause() {}
    virtual void resume() {}
};



#endif //STATE_HPP
