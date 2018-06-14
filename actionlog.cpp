#include "actionlog.h"
#include <iostream>
#include <string>

using namespace cv;

HWND glHwnd;

ActionLog::ActionLog()
{
    startRec = 0;
    xyScale[0] = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    xyScale[1] = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);
    //MouseHook();
    //get pixel sample
    //get pixel coord
}

Mat ActionLog::Hwnd2mat(){
    HWND hwnd = glHwnd;
    SetForegroundWindow(glHwnd);

    HDC hwindowDC,hwindowCompatibleDC;

    int height,width,srcheight,srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER  bi;

    hwindowDC=GetDC(hwnd);
    hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);
    //GetWindowRect(hwnd, &windowsize);

    srcheight   = windowsize.bottom;
    srcwidth    = windowsize.right;
    height      = windowsize.bottom;  //change this to whatever size you want to resize to
    width       = windowsize.right;

    src.create(height,width,CV_8UC4);

    // create a bitmap
    hbwindow            = CreateCompatibleBitmap( hwindowDC, width, height);
    bi.biSize           = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth          = width;
    bi.biHeight         = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes         = 1;
    bi.biBitCount       = 32;
    bi.biCompression    = BI_RGB;
    bi.biSizeImage      = 0;
    bi.biXPelsPerMeter  = 0;
    bi.biYPelsPerMeter  = 0;
    bi.biClrUsed        = 0;
    bi.biClrImportant   = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC,hbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject (hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(hwnd, hwindowDC);
    //imshow("src", src);
    //waitKey();
    return src;
}

Point ActionLog::HwndRoi(){
    RECT rect;
    if(GetWindowRect(glHwnd, &rect)){
      return Point(rect.left, rect.top);
      int width     = rect.right - rect.left;
      int height    = rect.bottom - rect.top;
      mainRect       = cv::Rect(rect.left, rect.top, width, height);
      qInfo("x %d y  %d w %d h %d", rect.left, rect.top, width, height);
    }
}

void ActionLog::LeftButton(){

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * xyScale[0];
    double cy = cursorPos.y * xyScale[1];
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


void ActionLog::Click(int x, int y, int back)
{
    SetForegroundWindow(glHwnd);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * xyScale[0];
    double cy = cursorPos.y * xyScale[1];

    double nx = x * xyScale[0];
    double ny = y * xyScale[1];

    INPUT Input={0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
    Input.mi.dx = (LONG)nx;
    Input.mi.dy = (LONG)ny;
    SendInput(1,&Input,sizeof(INPUT));
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE |  MOUSEEVENTF_LEFTUP;
    cv::waitKey(100);
    SendInput(1,&Input,sizeof(INPUT));

    if (back){
        Input.mi.dx = (LONG)cx;
        Input.mi.dy = (LONG)cy;
        Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        SendInput(1,&Input,sizeof(INPUT));
    }
}

void ActionLog::Click2(int x, int y)
{
    Click(x, y, 0);
}

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

QString windowName;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
    char buff[255];


    if (IsWindowVisible(hWnd)) {
        GetWindowTextA(hWnd, (LPSTR) buff, 254);
        QString temp(buff);
        int diff = QString::compare(windowName, QString(buff) , Qt::CaseInsensitive);
        //qInfo("%s %d %d", buff, diff, (int)hWnd);
        if (temp.contains(windowName)){
            glHwnd = hWnd;
            qInfo("%s %d %d", buff, diff, (int)hWnd);
        }/**/
        //qInfo("visible");
        //return FALSE;
    }
    return TRUE;
}

void ActionLog::WindowsInfo(QString winName){
    windowName = winName;
    EnumWindows(EnumWindowsProc, 0);//(WNDENUMPROC)&
    //HwndRoi(glHwnd);
}
