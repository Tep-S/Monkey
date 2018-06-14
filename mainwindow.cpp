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
#include <QToolTip>
#include "lua/luapusher.h"
#include "linefinder.h"
#include "reader.h"
#include <QDir>
#include "actionlog.h"

enum{ DESCR_GOOD, DESCR_BAD};

void TestFolder(QString mainPath, Sequence* seq);
void CreateFilesDescriptor(QString mainPath, QString destPath, int type);
void HaarTests(Sequence* seq);




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    seq(new Sequence()),
    stream(new Stream()),
    handler(new Handler(stream, ui))
{
    ui->setupUi(this);
    Plots();
    //seq->GetHP(Point(450, 750));
    //seq->FindTarget();
    //ActionLog actlog;
    //actlog.KeyPress(1, 2);
    //seq->ImgKmeans();
    //handler->MouseHookTest();
    //HaarTests(seq);
   // handler->CharacterAngle();
    //LuaPusher pusher;

    cv::Mat one, two;
    //seq->FlannMatching(one, two);
    /*seq->MotionMask(one, two); last in use*/
    //seq->KmeansTest();
    //Reader reader;
    //Tests();
    //actlog.WindowsInfo();
    //actlog.KeyPress(1, 2);
    //stream->start();
    handler->Duck();
    //seq->SobelDir();
    //handler->start();
    /*while(1){
        handler->Click(300,300);
        QThread::msleep(1000);
    }*/
    //for(int i = 0; i < 5; i++)
    //    handler->TestDiff();
    //seq->FindRect(temp);
   // seq->GetHP_MP();
    // cv::Mat test;
    //seq->FlannMatching(test, test);

    Connects();



}

void TestFolder(QString mainPath, Sequence* seq){
    using namespace std;
    using namespace cv;
    QDir folder(mainPath);
    folder.setNameFilters(QStringList()<<"*.jpeg");
    QStringList fileList = folder.entryList();

    int test = 0;
    Rect cropArea(531,164,1364 - 531,649 - 164);
    Size sizeOut(50, 50);
    Point delColor[2];
    delColor[0] = Point(454, 646);
    delColor[1] = Point(1438, 607);

    //find color by point
   /* QString tempPath = mainPath + (QString)fileList.at(0);
    Mat inTest = imread( tempPath.toStdString().c_str());
    Vec3b hsvDel[2];
    for(int i = 0; i < 2; i++){
        hsvDel[i] = seq->PixHsv(inTest, delColor[i]);
        //qInfo("%d %d %d", hsvDel[i].val[0], hsvDel[i].val[1], hsvDel[i].val[2]);
    }*/

    int listLen = test ? 1 : fileList.size();

    for(int i = 0; i < listLen; i++){
        QString tempPath = mainPath + (QString)fileList.at(i);
        Mat in = imread( tempPath.toStdString().c_str());
        if (in.empty()){
            qInfo("no image!");
            return;
        }
        Mat cropped = in(cropArea);
        //delete color
       /* Mat maskInv[2], out1, out2;
        for(int i = 0; i < 2; i++){
            Mat mask = seq->ColorMask2(in, hsvDel[i]);
            cv::bitwise_not(mask, maskInv[i]);
        }
        cv::bitwise_and(in, in, out1, maskInv[0]);
        cv::bitwise_and(out1, out1, out2, maskInv[1]);
        imshow("testy", out2);
        return;*/
        Mat gray;
        cvtColor(cropped, gray, COLOR_BGR2GRAY);

        //to grayscale

        Mat small;
        resize(gray, small, sizeOut);
        if (test){
            namedWindow("test_cropp");
            imshow("test_cropp", cropped);
            namedWindow("resize");
            imshow("resize", small);
            char c = (char)waitKey(500);
            if( c == 27 ) { break; } // escape
        }else
            imwrite(tempPath.toStdString().c_str(), small);

    }
}

void CreateFilesDescriptor(QString mainPath, QString destPath, int type){
    QDir folder(mainPath);
    folder.setNameFilters(QStringList()<<"*.jpeg");
    QStringList fileList = folder.entryList();
    QFile file(destPath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
    for(int i = 0; i < fileList.size(); i++){
        QString tempPath;
        if (type == DESCR_GOOD)
            tempPath = "good\\" + (QString)fileList.at(i) + " 1 0 0 50 50 \n";
        else
            tempPath = "bad\\" + (QString)fileList.at(i) + "\n";
        file.write(tempPath.toUtf8());
    }
    file.close();
}

void HaarTests(Sequence* seq){
    QString screenPath = "C:/Users/Sam/Desktop/autoscreens2/tank/good/";
    seq->Haar();
    //TestFolder(screenPath, seq);
    //QString badPath = "C:/Users/Sam/Desktop/autoscreens/bad/";
    QString destFile = "C:/Users/Sam/Desktop/autoscreens2/tank/good.txt";

    int type = DESCR_GOOD;
    //CreateFilesDescriptor(screenPath, destFile, type);
    //opencv_traincascade.exe -data haarcascade -vec samples.vec -bg bad.txt -numStages 16 -minhitrate
    //0.999 -maxFalseAlarmRate 0.4 -numPos 312 -numNeg 911 -w 20 -h 20 -mode ALL -precalcValBufSize 2048 -precalcIdxBufSize 2048
}


void MainWindow::Plots(){
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setRange(0.0, 360.0);
    ui->customPlot->yAxis->setRange(0.0, 1.0);
   // QPen dotPen(Qt::red, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
   // ui->customPlot->graph(0)->setPen(dotPen);


    //plot test
#if 0
    QCPCurve *fermatSpiral1 = new QCPCurve(ui->customPlot2->xAxis, ui->customPlot2->yAxis);
    // generate the curve data points:
    const int pointCount = 500;
    QVector<QCPCurveData> dataSpiral1(pointCount);
    QVector<double> vecI, vecY;
    for (int i=0; i<pointCount; ++i)
    {
      double phi = i/(double)(pointCount-1)*8*M_PI;
      //double theta = i/(double)(pointCount-1)*2*M_PI;
      vecI.append(qSqrt(phi)*qCos(phi));
      vecY.append(qSqrt(phi)*qSin(phi));
      //dataSpiral1[i] = QCPCurveData(i, qSqrt(phi)*qCos(phi), qSqrt(phi)*qSin(phi));
    }
    // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
    //fermatSpiral1->data()->set(dataSpiral1, true);
    fermatSpiral1->setData(vecI, vecY);
    // color the curves:
    fermatSpiral1->setPen(QPen(Qt::blue));
    fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));
    // set some basic customPlot config:
    ui->customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot2->axisRect()->setupFullAxesBox();
    ui->customPlot2->rescaleAxes();
#endif
}

void MainWindow::Tests(){
    QPoint pnt = QCursor::pos();
    qInfo("x %d y %d",pnt.x(), pnt.y());

    /*Canny( src_gray, canny_output, thresh, thresh*2, 3 );
      /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ ){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }*/
}

void MainWindow::ShowToolTip(){
    QToolTip::showText(ui->btLoadSequence->mapToGlobal(QPoint()), "A tool tip");
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
    ui->btLoadSequence->setToolTip("draw commands");
    connect(ui->btLoadSequence,     SIGNAL (clicked()), this, SLOT(ShowToolTip()));
    connect(ui->btTemplate,         SIGNAL (clicked()), this, SLOT(TestTemplate()));
}

void MainWindow::TestTemplate(){
   // seq->TemplateTest();

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
