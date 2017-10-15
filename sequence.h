#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QSettings>
#include <QFileDialog>
#include <QDir>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
    void OpenImage(QString imageName);
    QString SaveCommand(SaveCmd cmdIn);
    void RemoveCommand();
    void SaveSequence(QString filename);
    void LoadSequence(QString filename);
    void ImgAct(int command, float *par, cv::Mat &outImg);
    void Draw();
private:
    cv::Mat img;
    cv::Mat imgClean;
    SaveCmd cmdBuff[20];
    int cmdCnt;
};

#endif // SEQUENCE_H
