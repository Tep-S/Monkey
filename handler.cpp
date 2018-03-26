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

void Handler::run(){
    using namespace cv;
    msleep(2000);
    int cntFrame = 0;
while(1){
   // Rect rect(0, 0, 1080, 1080);
    //stream->GetCropped(rect);
    //Mat window = stream->GetCropped(rect);
    Mat window;
    cv::cvtColor(stream->imgMain, window, CV_BGRA2BGR);

    Mat templ = imread( "log/flat.jpg", 1 );
    //Mat window = imread( "img1.jpg", 1 );

   // seq->FindRoad(templ);
    //msleep(2000);
   // continue;

    Point point = seq->TemplateCoord(window,templ, 0.7);
    if ( (point.x == 0) && (point.y == 0) )
        continue;
    point.x += templ.cols/2;
    point.y += templ.rows/2;
    qInfo("point x %d y %d ", point.x, point.y);
    //xPlot.append(point.x);
    //yPlot.append(point.y);
    //ui->customPlot->graph(0)->setData(xPlot , yPlot);
    ui->customPlot->replot();
    //curve->setData(xPlot , yPlot);
    cv::circle(window, point, 50, Qt::green);
    char nameBuff[128];
    sprintf(nameBuff,"log/%d.jpg",cntFrame++);
    qInfo("%s",nameBuff);

    //imwrite( nameBuff, window );

    //namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //imshow( "Display window", window);                   // Show our image inside it.
    //waitKey(0);
   // Click(point.x, point.y);
    Result();

    msleep(300);
}
}

void Handler::Result(){

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
