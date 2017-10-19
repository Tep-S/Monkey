#ifndef STREAM_H
#define STREAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "QPixmap"

enum{
    NONE_IN,
    SCREEN_IN,
    VIDEO_IN
};

class Stream: public QThread{
public:
    Stream();
    cv::Mat GetCropped(cv::Rect rect);
private:
    int step;
    void run();
    cv::Mat GetScreen();
    cv::Mat GetFrame();
    int inputType;
    cv::Mat imgMain;
};

#endif // STREAM_H
