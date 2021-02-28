#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <queue>

#include <SDL/SDL.h>

class Keyboard
{
public:
    enum EventType
    {
        KEY_DOWN,
        KEY_UP,
        INVALID
    };
    struct KeyEvent
    {
        EventType eventType = INVALID;
        int key = -1;

        operator bool() const
        {
            return eventType != INVALID;
        }
    };
public:
    Keyboard();
    ~Keyboard();

    bool IsKeyPressed(int key) const;

    KeyEvent PeekEvent() const;

    KeyEvent PeekAndPopEvent();

    void KeyDownEvent(int key);
    void KeyUpEvent(int key);

private:
    static constexpr int cMAXKEYS = SDLK_LAST+1;
    std::queue<KeyEvent> cEvents;
    bool cKeysState[cMAXKEYS];
};

#endif