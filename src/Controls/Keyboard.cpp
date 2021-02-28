#include "Keyboard.h"
#include <cassert>

Keyboard::Keyboard()
{
    for (size_t i = 0; i < cMAXKEYS; i++)
    {
        cKeysState[i] = false;
    }
}

Keyboard::~Keyboard()
{
}

bool Keyboard::IsKeyPressed(int key) const
{
    assert(key >= 0 && key < cMAXKEYS);

    return cKeysState[key];
}

void Keyboard::KeyDownEvent(int key)
{
    assert(key >= 0 && key < cMAXKEYS);

    cKeysState[key] = true;

    KeyEvent ke = {KEY_DOWN, key};

    cEvents.push(ke);
}

void Keyboard::KeyUpEvent(int key)
{
    assert(key >= 0 && key < cMAXKEYS);

    cKeysState[key] = false;

    KeyEvent ke = {KEY_UP, key};

    cEvents.push(ke);
}

Keyboard::KeyEvent Keyboard::PeekEvent() const
{
    return cEvents.front();
}

Keyboard::KeyEvent Keyboard::PeekAndPopEvent() 
{
    KeyEvent res;
    if(!cEvents.empty())
    {
        res = cEvents.front();

        cEvents.pop();
    }
    

    return res;
}
