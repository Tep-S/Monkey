#include "stream.h"
#include "QApplication"
#include <QPixmap>
#include <QImage>
#include <QDesktopWidget>

#include <QScreen>

Stream::Stream()
{
    inputType = SCREEN_IN;
    step = 500;
}

cv::Mat Stream::GetCropped(cv::Rect rect){
    //qInfo("rows %d cols %d", imgMain.rows, imgMain.cols);
    if (imgMain.rows && imgMain.cols)
        return imgMain(rect);
    else
        return imgMain;
}

cv::Mat Stream::GetScreen(){
    QPixmap screenshot  = QPixmap::grabWindow(QApplication::desktop()->winId());
    //QScreen screen = QScreen::grabWindow(QApplication::desktop()->winId());
    QImage imgScreen    = screenshot.toImage();
    cv::Mat matScreen(imgScreen.height(), imgScreen.width(), CV_8UC4, const_cast<uchar*>(imgScreen.bits()), imgScreen.bytesPerLine());//imgScreen.scanLine());
    imgMain = matScreen.clone();
    //char* image_window = "Source Image";
    //cv::namedWindow( image_window, CV_WINDOW_AUTOSIZE );
    //cv::imshow(image_window, imgMain);
    return imgMain;
}

void Stream::GetFrame(){
   /* cv::VideoCapture cap(0);
    if (!cap.isOpened())
        return;
    cap.read(imgMain);
*/
}

void Stream::run(){
while(1){
    qInfo("stream");
    if (inputType == SCREEN_IN){
        GetScreen();
    }
    if (inputType == VIDEO_IN){
        GetFrame();
    }
    msleep(step);
}
}
