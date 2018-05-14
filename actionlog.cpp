#include "actionlog.h"
#include <iostream>

ActionLog::ActionLog()
{
    startRec = 0;
    MouseHook();
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
