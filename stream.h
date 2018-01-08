#ifndef STREAM_H
#define STREAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QPixmap>
#include <QThread>

enum{
    NONE_IN,
    SCREEN_IN,
    VIDEO_IN
};

class Stream: public QThread{
    Q_OBJECT
public:
    Stream();
    cv::Mat GetCropped(cv::Rect rect);
    cv::Mat imgMain;
private:
    int step;
    void run();
    cv::Mat GetScreen();
    void GetFrame();
    int inputType;
};

#endif // STREAM_H
