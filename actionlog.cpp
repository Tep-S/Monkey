#include "actionlog.h"
#include <iostream>

ActionLog::ActionLog()
{
    startRec = 0;
    //MouseHook();
    //get pixel sample
    //get pixel coord
}

void ActionLog::LeftButton(){
    const double xScale = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double yScale = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * xScale;
    double cy = cursorPos.y * yScale;
    cout << "Left Button Down" << endl;
    if(startRec){
        ActionParam act;
        act.xy[0] = cx;
        act.xy[1] = cy;
        //get hsv
        //get area screen
        action.push_back(act);
    }
}

LRESULT  ActionLog::MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam)/*there was __stdcall*/
{
    if (nCode >= 0)
    {
        switch(wParam){
        case WM_LBUTTONDOWN:{
            LeftButton();

        }break;
        case WM_LBUTTONUP:{
                cout << "Left Button Up" << endl;
        }break;
        }
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void ActionLog::ReleaseHook(){
    startRec = 0;
    UnhookWindowsHookEx(mouseHook);
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
void ActionLog::MouseHook(){

    if (!(mouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)&MouseHookCallback, NULL, 0)))
        cout << "Failed to install mouse hook!" << endl;
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


void ActionLog::Click(int x, int y)
{
    const double xScale = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double yScale = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * xScale;
    double cy = cursorPos.y * yScale;

    double nx = x * xScale;
    double ny = y * yScale;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    Input.mi.dx = (LONG)nx;
    Input.mi.dy = (LONG)ny;
    SendInput(1,&Input,sizeof(INPUT));

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1,&Input,sizeof(INPUT));
}
HWND glHwnd;
void ActionLog::KeyPress(int type, int msPress){
    SetForegroundWindow(glHwnd);
    INPUT ip;
    ip.type         = INPUT_KEYBOARD;
    ip.ki.wVk       = type;//VK_F1;
    ip.ki.wScan     = 0;
    ip.ki.dwFlags   = 0;
    ip.ki.time      = 0;
    ip.ki.dwExtraInfo = 0;

    // Send the keyboard event to the specified window
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(msPress);
    ip.ki.dwFlags =  KEYEVENTF_KEYUP;//KEYEVENTF_SCANCODE |
    SendInput(1, &ip, sizeof(INPUT));
}



BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
    char buff[255];
    QString windowName = "Lineage";

    if (IsWindowVisible(hWnd)) {
        GetWindowTextA(hWnd, (LPSTR) buff, 254);
        QString temp(buff);
        int diff = QString::compare(windowName, QString(buff) , Qt::CaseInsensitive);
        if (temp.contains(windowName)){
            glHwnd = hWnd;
            qInfo("%s %d %d", buff, diff, (int)hWnd);
        }/**/
        //qInfo("visible");
        //return FALSE;
    }
    return TRUE;
}

void ActionLog::WindowsInfo(){
    EnumWindows(EnumWindowsProc, 0);//(WNDENUMPROC)&
}
