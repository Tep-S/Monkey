#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QPoint>
#include <QCursor>
#include <QSettings>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    seq(new Sequence())
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
    seq->ImgAct(command);
}

void MainWindow::Connects(){
    connect(ui->btOpenImage, SIGNAL (clicked()), this, SLOT (OpenImage()));
    connect(ui->btSaveCommand, SIGNAL (clicked()), this, SLOT (SaveCommand()));
    connect(ui->btRemoveCommand, SIGNAL (clicked()), this, SLOT (RemoveCommand()));
    connect(ui->btSaveSequence, SIGNAL (clicked()), this, SLOT (SaveSequence()));
}

void MainWindow::SaveCommand(){
    ui->lsMain->addItem(seq->SaveCommand());
}

void MainWindow::RemoveCommand(){
    seq->RemoveCommand();
}

void MainWindow::SaveSequence(){
    seq->SaveSequence(ui->lnSequence->text());
}

void MainWindow::OpenImage(){
    QString imageName = QFileDialog::getOpenFileName(this,
        tr("Open Image"),QDir::currentPath(),tr("Files (*.png *.jpg *.tiff *.bmp)"));
    seq->OpenImage(imageName);
}
MainWindow::~MainWindow()
{
    delete ui;
}
