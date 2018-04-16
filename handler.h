#ifndef HANDLER_H
#define HANDLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QThread>
#include "stream.h"
#include "sequence.h"
#include <windows.h>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "qcustomplot.h"

class Handler: public QThread{
public:
    Handler(Stream *streamIn, Ui::MainWindow *uiIn);
    void run();
    void Result();
    void Click(int x, int y);
    void WindowsInfo();
    void TestDiff();
    void KeyPress(int type, int msPress);
private:
    QCPCurve* curve;
    QVector<double> xPlot, yPlot;
    Ui::MainWindow *ui;
    Sequence* seq;
    Stream* stream;
    cv::Mat imgIn;
    cv::Rect rect;
};

#endif // HANDLER_H
