#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
    Settings();
private:
    void Move();
    QSettings conf;
    void Load();
    void LoadLogic();
};

#endif // SETTINGS_H
