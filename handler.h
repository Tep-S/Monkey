#ifndef HANDLER_H
#define HANDLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QThread>

class Handler: public QThread{
public:
    Handler();
    void run();
    void Result();
private:
    cv::Mat imgIn;
    cv::Rect rect;
};

#endif // HANDLER_H
