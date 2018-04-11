#ifndef READER_H
#define READER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::ml;
class Reader
{
public:
    Reader();
private:
    void Labeling();
    void Testing();
};

#endif // READER_H
