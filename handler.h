#ifndef HANDLER_H
#define HANDLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Handler: public Qthread
{
public:
    Handler();
    void run();
    void Result();
private:
    cv::Mat imgIn;
    cv::Rect rect;
};

#endif // HANDLER_H
