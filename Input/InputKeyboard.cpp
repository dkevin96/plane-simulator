#include "InputKeyboard.h"


InputKeyboard::InputKeyboard()
{
    keyMap.insert(Qt::Key_W, false);
    keyMap.insert(Qt::Key_A, false);
    keyMap.insert(Qt::Key_S, false);
    keyMap.insert(Qt::Key_D, false);
    keyMap.insert(Qt::Key_F2, false);
    keyMap.insert(Qt::Key_Space, false);
    keyMap.insert(Qt::Key_F3, false);
    keyMap.insert(Qt::Key_F4, false);

}

void InputKeyboard::keyPressed(Qt::Key key)
{
    if(keyMap.find(key) != keyMap.end())
    {
        keyMap.insert(key,true);
    }
}

void InputKeyboard::keyReleased(Qt::Key key)
{
    if(keyMap.find(key) != keyMap.end())
    {
        keyMap.insert(key,false);
    }
}

bool InputKeyboard::isKeyPressed(Qt::Key key)
{
    return keyMap.value(key);
}

