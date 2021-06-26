#ifndef InputKeyboard_H
#define InputKeyboard_H

#include <QVector>
#include <QMap>
#include <QKeyEvent>

class InputKeyboard
{
private:
    QMap<Qt::Key, bool> keyMap;

public:
    InputKeyboard();

    void keyPressed(Qt::Key key);
    void keyReleased(Qt::Key key);

    bool isKeyPressed(Qt::Key key);

};

#endif
