#include "stream.h"
#include "QApplication"
Stream::Stream()
{
    step = 1000;
}

cv::Mat Stream::GetCropped(cv::Rect rect){
    return imgMain(rect);
}

cv::Mat Stream::GetScreen(){
    //QPixmap window = QPixmap::grabWindow(QApplication::desktop()->grab());
    QPixmap window = QApplication::desktop()->grab();
    cv::Mat res(window.height(),window.width(),CV_8UC3,(uchar*)window.bits(),window.bytesPerLine());
    cvtColor(res, res,CV_BGR2RGB);
    return res;
}

cv::Mat Stream::GetFrame(){
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
        return -1;
    cap.read(imgMain);

}

void Stream::run(){
    if (inputType == SCREEN_IN){
        imgMain = GetScreen();
    }
    if (inputType == VIDEO_IN){
        imgMain = GetFrame();
    }
    sleepms(step);
}
