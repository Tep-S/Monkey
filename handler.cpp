#include "handler.h"

//#include <QList>
Handler::Handler(Stream* streamIn, Ui::MainWindow *uiIn)
{
    ui = uiIn;
    stream = streamIn;
    seq = new(Sequence);
    //curve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
   //ui->customPlot->addPlottable(curve);
}

QString type2str(int type) {
  QString r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void Handler::TestDiff(){
    cv::Mat inputTest[3];
    qInfo("go");
    msleep(3000);
    for(int i = 0; i < 3; i++){
        inputTest[i] = stream->GetAdditionalScreen().clone();
        if (i < 2)
            msleep(500);
    }
    cv::Mat diff[2];
    cv::Mat threshOut[2];
    cv::Mat out;
    for(int i = 0; i < 2; i++){
        cv::absdiff(inputTest[i], inputTest[i + 1], diff[i]);
        cv::threshold(diff[i],threshOut[i],40,255,cv::THRESH_BINARY);
    }
    cv::bitwise_and(diff[0], diff[1], out);

    /*cv::namedWindow( "Display window", cv::WINDOW_KEEPRATIO );// Create a window for display.
    cv::imshow( "Display window", out);                   // Show our image inside it.
    cv::namedWindow( "Display window1", cv::WINDOW_KEEPRATIO );// Create a window for display.
    cv::imshow( "Display window1", diff[0]);                   // Show our image inside it.
    cv::namedWindow( "Display window2", cv::WINDOW_KEEPRATIO );// Create a window for display.
    cv::imshow( "Display window2", diff[1]);                   // Show our image inside it.
    cv::waitKey(0);*/
}

//xPlot.append(point.x);
//yPlot.append(point.y);
//ui->customPlot->graph(0)->setData(xPlot , yPlot);
//ui->customPlot->replot();
//curve->setData(xPlot , yPlot);

void Handler::run(){
    using namespace cv;
    int cntFrame = 0;
    msleep(2000);

while(1){
   // Rect rect(0, 0, 1080, 1080);
    //stream->GetCropped(rect);
    //Mat window = stream->GetCropped(rect);
    Mat window;
    cvtColor(stream->imgMain, window, CV_BGRA2BGR);
   // TestDiff();

    //Mat window = imread( "img1.jpg", 1 );

   // seq->FindRoad(templ);
    //msleep(2000);
   // continue;
    Mat templ = imread( "log/duck/0.png", 1 );
    Mat templRes;
    resize(templ, templRes, Size(templ.cols*1.45, templ.rows*1.45));
    //Point point(0,0);
    Point point = seq->TemplateCoord(window,templRes, 0.4);
    if ( (point.x == 0) && (point.y == 0) ){
        continue;
    }
    /*for(int i = 0; i < 10; i++){
        double scale = 1.0 + ((double)i)/20;
        resize(templ, templRes, Size(templ.cols*scale, templ.rows*scale));
        Point point = seq->TemplateCoord(window,templRes, 0.7);
    }*/
    point.x += templRes.cols/2;
    point.y += templRes.rows/2;
    qInfo("point x %d y %d ", point.x, point.y);

    circle(window, point, 50, Qt::green);
    //Mat windowOut;
    //addWeighted(window,0.5,templRes,0.5,0.0,windowOut);
    char nameBuff[128];
    sprintf(nameBuff,"log/%d.jpg",cntFrame++);
    qInfo("%s",nameBuff);
    imwrite( nameBuff, window );

    //Click(point.x, point.y);
    Result();

    msleep(300);
}
}

void Handler::Result(){

}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
    char buff[255];

    if (IsWindowVisible(hWnd)) {
        GetWindowTextA(hWnd, (LPSTR) buff, 254);
        qInfo("%s", buff);
        qInfo("visible");
        //return FALSE;
    }
    return TRUE;
}

void Handler::WindowsInfo(){
    EnumWindows(EnumWindowsProc, 0);
   /*  // Получаем handle окна для последующего использования в функциях Win32 API
     HWND hwndWin = GetActiveWindow();
     char * caption = (char*)malloc(32 * sizeof(char));
     // Получаем название окна в переменную caption
     GetWindowTextA(hwndWin, caption, 32);
     qInfo("%s", caption);*/
     qInfo("end");
}

void Handler::Click(int x, int y)
{
    const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * XSCALEFACTOR;
    double cy = cursorPos.y * YSCALEFACTOR;

    double nx = x * XSCALEFACTOR;
    double ny = y * YSCALEFACTOR;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)nx;
    Input.mi.dy = (LONG)ny;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

    SendInput(1,&Input,sizeof(INPUT));
    //SendInput(1,&Input,sizeof(INPUT));

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1,&Input,sizeof(INPUT));
}
