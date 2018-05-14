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

bool compareContourAreas2 ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 ) {
    double i = fabs( cv::contourArea(cv::Mat(contour1)) );
    double j = fabs( cv::contourArea(cv::Mat(contour2)) );
    return ( i < j );
}

void Handler::CharacterAngle(){
    using namespace cv;
    using namespace std;
    Mat hsv;
    Mat in      = imread( "log/map_tank.jpg");
    Mat templ   = imread("log/point2.jpg", IMREAD_GRAYSCALE);
    cvtColor(in, hsv, COLOR_BGR2HSV);
    Vec3b pix;
    pix.val[0] = pix.val[1] = pix.val[2] = 240;
    Mat whiteMask = seq->ColorMask2(hsv, pix, 15);
    vector<vector<Point>> contours;
    findContours(whiteMask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    Mat drawing = Mat::zeros( whiteMask.size(), CV_8UC3 );
    sort(contours.begin(), contours.end(), compareContourAreas2);//25 x 21
   /* RotatedRect rRect = minAreaRect(contours[contours.size()-1]);
    Point2f points[4];
    rRect.points(points);
    int minX = 10000;
    int maxX = 0;
    for(int i = 0; i < 4; ++i){
        if (points[i].x > maxX)
            maxX = points[i].x;
        if (points[i].x < minX)
            minX = points[i].x;
    }*/

    Rect recRoi(272, 188, 50, 50);
    Mat pointRaw = whiteMask(recRoi);

    namedWindow("whitemask");
    imshow("whitemask", pointRaw);

    //seq->FlannMatching(input, templateIn);
    Mat dst;
    Point2f pc(whiteMask.cols/2., whiteMask.rows/2.);
    double maxLock = 0.0;
    for(int i = 0; i < 360; i+=3){
        Mat r = getRotationMatrix2D(pc, i, 1.0);
        warpAffine(whiteMask, dst, r, whiteMask.size());
        seq->TemplateCoord(dst, templ, 0.7, maxLock);
        xPlot.append(i);
        yPlot.append(maxLock);
    }

    ui->customPlot->graph(0)->setData(xPlot , yPlot);
    ui->customPlot->replot();
    //get white color
    //find object coord
    //get roi
    //rotate pattern and find best overlap

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
    Mat templ = imread( "log/duck/0.png", 1 );
    Mat templRes;
    resize(templ, templRes, Size(templ.cols*1.45, templ.rows*1.45));
    double maxLock;
    Point point = seq->TemplateCoord(window,templRes, 0.4, maxLock);
    if ( (point.x == 0) && (point.y == 0) ){
        continue;
    }
    point.x += templRes.cols/2;
    point.y += templRes.rows/2;
    qInfo("point x %d y %d ", point.x, point.y);

    circle(window, point, 50, Qt::green);
    //Mat windowOut;
    //addWeighted(window,0.5,templRes,0.5,0.0,windowOut);
    char nameBuff[128];
    sprintf(nameBuff,"log/%d.jpg",cntFrame++);
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

void Handler::KeyPress(int type, int msPress){
/*#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
    */
    int type2 = VK_DOWN;
    keybd_event(type, 0, 0, 0);
    Sleep(msPress);
    if (msPress)
        keybd_event(type, 0, KEYEVENTF_KEYUP, 0);
}

void Handler::Click(int x, int y)
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


