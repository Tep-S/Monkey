#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QSettings>
#include <QFileDialog>
#include <QDir>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/flann.hpp"
#include "linefinder.h"

#define PI 3.1415926

using namespace cv::flann;
//using namespace cv;
//using namespace std;

enum{
    Do_Gray,
    Do_Thresh,
    Do_Canny,
    Do_Contours,
    Do_Bgr2Hsv,
    Do_Blur,
    Do_Hsv2Bgr
};

struct SaveCmd{
    int cmd;
    int len;
    float param[10];
};

class Sequence
{
public:
    Sequence();
    void    OpenImage(QString imageName);
    QString SaveCommand(SaveCmd cmdIn);
    void    RemoveCommand();
    void    SaveSequence(QString filename);
    void    LoadSequence(QString filename);
    void    ImgAct(int command, float *par, cv::Mat &outImg);
    void    Draw();
    cv::Point TemplateCoord(cv::Mat img, cv::Mat templ, double thresh);
    int     FlannMatching(cv::Mat input, cv::Mat templateIn);
    void    FindRoad(cv::Mat input);
    cv::Mat ColorMask(cv::Mat input, cv::Scalar low, cv::Scalar high);
    void    FindRect(cv::Mat input);
    void    MotionMask(cv::Mat input, cv::Mat outputMask);
    int     GetHP(cv::Point pix);
    void    GetHP_MP();
    void KmeansTest();
private:
    cv::Mat img;
    cv::Mat imgClean;
    SaveCmd cmdBuff[20];
    int cmdCnt;
};

#endif // SEQUENCE_H
