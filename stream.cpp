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
    if (imgMain.rows && imgMain.cols)
        return imgMain(rect);
    else
        return imgMain;
}

cv::Mat Stream::GetAdditionalScreen(){
    QPixmap screenshot  = QPixmap::grabWindow(QApplication::desktop()->winId());
    //QScreen screen = QScreen::grabWindow(QApplication::desktop()->winId());
    QImage imgScreen    = screenshot.toImage();
    cv::Mat matScreen(imgScreen.height(), imgScreen.width(), CV_8UC4, const_cast<uchar*>(imgScreen.bits()), imgScreen.bytesPerLine());//imgScreen.scanLine());
    imgAdd = matScreen.clone();
    return imgAdd;
}

cv::Mat Stream::GetScreen(){
    QImage imgScreen  = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
    imgMain = cv::Mat(imgScreen.height(), imgScreen.width(), CV_8UC4, const_cast<uchar*>(imgScreen.bits()), imgScreen.bytesPerLine());//imgScreen.scanLine());
    return imgMain;

    /*QPixmap screenshot  = QPixmap::grabWindow(QApplication::desktop()->winId());
    //QScreen screen = QScreen::grabWindow(QApplication::desktop()->winId());
    QImage imgScreen    = screenshot.toImage();
    cv::Mat matScreen(imgScreen.height(), imgScreen.width(), CV_8UC4, const_cast<uchar*>(imgScreen.bits()), imgScreen.bytesPerLine());//imgScreen.scanLine());
    imgMain = matScreen.clone();
    return imgMain;
    */
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
    if (inputType == SCREEN_IN){
        GetScreen();
    }
    if (inputType == VIDEO_IN){
        GetFrame();
    }
    msleep(step);
}
}
