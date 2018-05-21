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
    void Click(int x, int y);
    void KeyPress(int type, int msPress);
    void WindowsInfo();
private:
    int startRec;
    vector<ActionParam> action;
    HHOOK mouseHook;
    LRESULT MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
    //BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam);
    void LeftButton();
};

#endif // ACTIONLOG_H
