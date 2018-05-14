#ifndef ACTIONLOG_H
#define ACTIONLOG_H

#include <windows.h>
#include <vector>
#include <QMainWindow>

using namespace std;

struct ActionParam
{
    //ActionParam();
    int xy[2];
    int hsv[3];
    QString picName;
};

class ActionLog
{
public:
    ActionLog();
    void MouseHook();
    void ReleaseHook();
private:
    int startRec;
    vector<ActionParam> action;
    HHOOK mouseHook;
    LRESULT MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
    void LeftButton();
};

#endif // ACTIONLOG_H
