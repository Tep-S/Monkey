#include "handler.h"

//#include <QList>
Handler::Handler(Stream* streamIn, Ui::MainWindow *uiIn)
{
    ui = uiIn;
    stream = streamIn;
    seq = new(Sequence);
    act = new(ActionLog);
    glShift = cv::Point(0, 0);
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
        seq->MatchPixel(dst, templ, 0.7, maxLock);
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

void Handler::Duck(){
    //stream->imgMain
    act->WindowsInfo(QString("FCEUX"));
    cv::Mat hwndMat = act->Hwnd2mat();
    glShift += act->HwndRoi();
    qInfo("gl shift %d %d ", glShift.x, glShift.y);
    double maxLock;
    //cv::Mat templ = cv::imread("log/duck2/start.png", cv::IMREAD_GRAYSCALE);
    cv::Point pnt = seq->MatchPixel(hwndMat, "log/duck2/start.png", 0.7, maxLock);
    pnt += glShift;
    qInfo("%d %d", pnt.x, pnt.y);
    act->Click2(pnt.x, pnt.y);

}

void Handler::La2(){
    //cv::waitKey(3000);
    act->WindowsInfo(QString("Google Chrome"));
    while(1){
        qInfo("loop");
        act->KeyPress(VK_LEFT, 50);
        cv::waitKey(1500);
        cv::Mat hwndMat = act->Hwnd2mat();
        glShift += act->HwndRoi();
        qInfo("gl shift %d %d ", glShift.x, glShift.y);
        cv::Point pnt = seq->FindTarget(hwndMat);
        pnt += glShift;
        qInfo("%d %d", pnt.x, pnt.y);
        act->Click2(pnt.x, pnt.y);
        cv::waitKey(50);
        act->Click2(pnt.x, pnt.y + 50);
        cv::waitKey(50);
        act->Click2(pnt.x, pnt.y);
        cv::waitKey(50);
        act->Click2(pnt.x, pnt.y + 50);
        int hp = 0;
        if (hp){
            act->KeyPress(VK_F1,100);
        }
        cv::waitKey(1000);
        act->KeyPress(VK_F1,100);
        cv::waitKey(15000);
    }
    //rotate
    //check for enemy
    //click
    //check for hp
    //if not loop
    //fight and loot
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
    Point point = seq->MatchPixel(window,templRes, 0.4, maxLock);
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

