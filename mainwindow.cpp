#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::currentPath(),
                                                    tr("Files (*.png *.jpg *.tiff *.bmp)"));

    if (filename.isEmpty()) // Do nothing if filename is empty
        return;*/
    cv::Mat img = cv::imread("gta.png", 1);
    if (img.empty())
        return;

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, CV_BGR2GRAY);
    cv::Mat imgThresh;

    threshold( imgGray, imgThresh, 20, 150, CV_THRESH_BINARY );
    cv::namedWindow("My Image");
        // show the image on window
    cv::imshow("My Image", imgThresh);
//cv::String imageName("C:/code/Monkey-master/Monkey-master/pen.png");
    // read an image
  // IplImage* pImg =  cvLoadImage("pen.png", 1);

    // create image window named "My Image"
//    cv::namedWindow("My Image");
    // show the image on window
  //  CvShowImage("My Image", pImg);
}

MainWindow::~MainWindow()
{
    delete ui;
}
