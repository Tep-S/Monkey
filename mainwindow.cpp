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
    float param[3];
    param[0] = ui->lnParam1->text().toFloat();
    param[1] = ui->lnParam2->text().toFloat();
    param[2] = ui->lnParam2->text().toFloat();
    cv::Mat imgOut;
    seq->ImgAct(command, param, imgOut);
}

void MainWindow::Connects(){
    connect(ui->btOpenImage,        SIGNAL (clicked()), this, SLOT (OpenImage()));
    connect(ui->btSaveCommand,      SIGNAL (clicked()), this, SLOT (SaveCommand()));
    connect(ui->btRemoveCommand,    SIGNAL (clicked()), this, SLOT (RemoveCommand()));
    connect(ui->btSaveSequence,     SIGNAL (clicked()), this, SLOT (SaveSequence()));
    connect(ui->btSaveSequence,     SIGNAL (clicked()), this, SLOT (LoadSequence()));
    connect(ui->btDraw,             SIGNAL (clicked()), this, SLOT (Draw()));
}

void MainWindow::Draw(){
    seq->Draw();
}

void MainWindow::SaveCommand(){
    SaveCmd cmd;
    ui->lsMain->addItem(seq->SaveCommand(cmd));
}

void MainWindow::RemoveCommand(){
    seq->RemoveCommand();
    //ui->lsMain->clear();
}

void MainWindow::SaveSequence(){
    seq->SaveSequence(ui->lnSequence->text());
}

void MainWindow::LoadSequence(){
    QString imageName = QFileDialog::getOpenFileName(this,
        tr("Open Image"),QDir::currentPath(),tr("Files (*.png *.jpg *.tiff *.bmp)"));
    seq->LoadSequence(imageName);
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
