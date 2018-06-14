#ifndef ACTIONLOG_H
#define ACTIONLOG_H
#include <windowsx.h>
#include <windows.h>
#include <vector>
#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
    void Click(int x, int y, int back);
    void Click2(int x, int y);
    void KeyPress(int type, int msPress);
    void WindowsInfo(QString winName);
    cv::Point HwndRoi();
    cv::Rect mainRect;
    cv::Mat Hwnd2mat();
private:
    double xyScale[2];
    int startRec;
    vector<ActionParam> action;
    HHOOK mouseHook;
    LRESULT MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
    //BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam);
    void LeftButton();
};

#endif // ACTIONLOG_H
