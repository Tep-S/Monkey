#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QPoint>
#include <QCursor>

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

    QPoint pnt = QCursor::pos();
    qInfo("x %d y %d",pnt.x(), pnt.y());
    cv::Mat img = cv::imread("gta.png", 1);
    if (img.empty())
        return;

    cv::Mat imgGray;
    if (ui->cbGrayscale->isChecked())
        cv::cvtColor(img, imgGray, CV_BGR2GRAY);
    cv::Mat imgThresh;
    if (ui->cbThresh->isChecked())
        threshold( imgGray, imgThresh, 20, 150, CV_THRESH_BINARY );

    /*Canny( src_gray, canny_output, thresh, thresh*2, 3 );
      /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ ){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }*/

    //cv::namedWindow("My Image");
        // show the image on window
   // cv::imshow("My Image", imgThresh);
//cv::String imageName("C:/code/Monkey-master/Monkey-master/pen.png");
    // read an image
  // IplImage* pImg =  cvLoadImage("pen.png", 1);

    // create image window named "My Image"
//    cv::namedWindow("My Image");
    // show the image on window
  //  CvShowImage("My Image", pImg);
  Connects();
}

void MainWindow::ImgAct(int command){
    cv::Mat img;
    int param1, param2;
    enum{
        Do_Gray,
        Do_Thresh,
        Do_Canny,
        Do_Contours,
        Do_Bgr2Hsv,
        Do_Blur
    };

    switch(command){
    case Do_Gray:{
        cv::cvtColor(img, img, CV_BGR2GRAY);
    }
        break;
    case Do_Thresh:{
        //need gray in
        threshold( img, img, param1, param2, CV_THRESH_BINARY );//p1 20 p2 150
    }
        break;
    case Do_Canny:{
        Canny( img, img, param1, param2, 3 );//check param!
    }
        break;
    case Do_Contours:{
       // vector<vector<Point> > contours;
       // vector<Vec4i> hierarchy;
        //need canny before
       // findContours( img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    }
        break;
    case Do_Bgr2Hsv:{
        cv::cvtColor(img, img, CV_BGR2HSV);
    }
        break;
    case Do_Blur:{
        //src gray?
   //     cv::blur( img, img, Size(3,3));
    }
        break;
    }

}

void MainWindow::Connects(){
    connect(ui->btOpenImage, SIGNAL (clicked()), this, SLOT (OpenImage()));
    connect(ui->btSaveCommand, SIGNAL (clicked()), this, SLOT (SaveCommand()));
    connect(ui->btRemoveCommand, SIGNAL (clicked()), this, SLOT (RemoveCommand()));
    connect(ui->btSaveSequence, SIGNAL (clicked()), this, SLOT (SaveSequence()));
}

void MainWindow::SaveCommand(){
//which command
//params
//add to table
}

void MainWindow::RemoveCommand(){
//remove last row
}

void MainWindow::SaveSequence(){
//save all rows to file
}

void MainWindow::OpenImage(){

        imageName = QFileDialog::getOpenFileName(this,
            tr("Open Image"),QDir::currentPath(),tr("Files (*.png *.jpg *.tiff *.bmp)"));

        if (imageName.isEmpty()) // Do nothing if filename is empty
            return;
        cv::Mat img = cv::imread(imageName.toStdString().c_str(), 1);
        if (img.empty())
            return;
        cv::namedWindow("My Image");
            // show the image on window
        cv::imshow("My Image", img);

}
MainWindow::~MainWindow()
{
    delete ui;
}
